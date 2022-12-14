all: talk-slides.pdf

%.pdf: %.tex .FORCE
	latexrun -W no-overfull --latex-cmd=$(LATEX) --latex-args=-shell-escape $<

clean:
	latexrun --clean-all

.FORCE:

.PHONY: all clean .FORCE

# vim: ft=make
