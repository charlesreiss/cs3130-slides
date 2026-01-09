#!/usr/bin/python3
import argparse
import logging
import shutil
import subprocess

from pathlib import Path
from typing import List

logger = logging.getLogger(__name__)

def run_logged(command: List[str | Path]):
    logger.info('running %s', command)
    subprocess.check_call(command)

def convert_tex(base_file: Path, output_directory: Path):
    if r'\documentclass[tikz]{standalone}' in base_file.read_text()[:500]:
        shutil.copyfile(base_file, output_directory / base_file.name)
    else:
        run_logged([
            'python3', 'convert_lark.py',
            '--input', base_file,
            '--output', output_directory / ('_' + base_file.stem + '.qmd')
        ])

def convert_directory(base_directory: Path, output_directory: Path):
    for item in base_directory.iterdir():
        if (item.suffix == '.pdf' or item.suffix == '.png') and \
           item.stem not in ('slides', 'talk', 'talk-slides', 'talk-slides-heldback', 'test', 'talk-slides2'):
            shutil.copyfile(item, output_directory / item.name)
        elif item.is_dir() and item.name == 'figures':
            shutil.copytree(item, output_directory / item.name)
        elif item.suffix == '.tex' and \
           item.stem not in ('slides', 'talk', 'talk-slides', 'talk-slides-heldback', 'test', 'slides', 'talk-slides2'):
           convert_tex(item, output_directory)

    run_logged([
        'python3', 'build.py',
        '--create-top-qmd', output_directory / 'talk.qmd',
        '--include', output_directory / '_talk-inner.qmd',
    ])

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    parser = argparse.ArgumentParser()
    parser.add_argument('directory', type=Path, nargs='+', default=[])

    args = parser.parse_args()
    for directory in args.directory:
        convert_directory(directory, Path.cwd() / directory.name)

    
