#!/usr/bin/python3
import argparse
import copy
import logging
import os
import subprocess

from pathlib import Path

LATEXRUN = [
    'latexrun', '--latex-cmd', 'lualatex',
]

QUARTO = [
    'quarto', 'render'
]

def run_logged(*args, **xargs):
    logging.debug('running %s', args)
    subprocess.check_call(*args, **xargs)

def build_figures(base_directory, incremental):
    env = copy.copy(os.environ)
    tex_inputs = []
    if env.get('TEXINPUTS'):
        tex_inputs = env.get('TEXINPUTS').split(':')
    tex_inputs.append(str(base_directory.absolute()))
    tex_inputs.append(str(Path('common').absolute()))
    tex_inputs.append(str(Path('.').absolute()))
    env['TEXINPUTS'] = ':'.join(tex_inputs) + ':'
    for item in base_directory.iterdir():
        if item.name.endswith('.figure.tex'):
            fls_file = base_directory / 'latex.out' / item.with_suffix('.fls').name
            pdf_file = base_directory / 'latex.out' / item.with_suffix('.pdf').name
            svg_file = item.with_suffix('.svg')
            pdf_is_outdated = True
            if incremental and fls_file.exists() and pdf_file.exists():
                pdf_is_outdated = False
                for line in fls_file.read_text().split('\n'):
                    if line.startswith('INPUT '):
                        input_raw_path = line[len('INPUT '):]
                        if input_raw_path.startswith('/'):
                            input_path = Path(input_raw_path)
                        else:
                            input_path = base_directory / input_raw_path
                        if not input_path.exists():
                            logging.debug('building %s because %s does not exist',
                                pdf_file, input_path)
                            pdf_is_outdated = True
                            break
                        elif input_path.stat().st_mtime > pdf_file.stat().st_mtime:
                            logging.debug('building %s because %s is new (%s v %s)',
                                pdf_file, input_path,
                                input_path.stat().st_mtime,
                                pdf_file.stat().st_mtime)
                            pdf_is_outdated = True
                            break
            if pdf_is_outdated:
                run_logged(
                    LATEXRUN + [item.stem, '-o', pdf_file.relative_to(base_directory)],
                    env=env,
                    cwd=base_directory,
                )
                assert pdf_file.exists()
                pdf_file.touch(exist_ok=True)
            svg_is_outdated = True
            if incremental and not pdf_is_outdated and svg_file.exists() and svg_file.stat().st_mtime > pdf_file.stat().st_mtime:
                svg_is_outdated = False
            if svg_is_outdated:
                run_logged(['pdf2svg', pdf_file, svg_file])

def render_qmd(path):
    run_logged(QUARTO + [path])

def create_top_qmd(path, include_path):
    path.write_text('''---
format:
  revealjs:
    theme: [simple, ../custom.scss]
    slide-level: 3
    scrollable: true
    chalkboard: true
    progress: false
    margin: 0.02
    width: 1050
    height: 600
---
''' + '{{< include ../' + str(include_path.relative_to(path.parent.parent)) + ' >}}\n')

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--create-top-qmd', type=Path)
    parser.add_argument('--render-qmd', type=Path)
    parser.add_argument('--figures', type=Path)
    parser.add_argument('--include', type=Path)
    parser.add_argument('--directory', type=Path)
    parser.add_argument('--incremental', action='store_true', default=True)
    parser.add_argument('--force', action='store_false', dest='incremental')
    args = parser.parse_args()
    if args.directory:
        args.figures = args.directory / 'texfig'
        args.render_qmd = args.directory / 'talk.qmd'
    if args.create_top_qmd:
        create_top_qmd(args.create_top_qmd, args.include)
    if args.figures:
        build_figures(args.figures, incremental=args.incremental)
    if args.render_qmd:
        render_qmd(args.render_qmd)

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    main()
