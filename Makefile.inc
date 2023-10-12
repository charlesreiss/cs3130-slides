LATEXRUN=latexrun

all: talk-slides.pdf

%.pdf: %.tex .FORCE
	$(LATEXRUN) -W no-overfull --latex-cmd=$(LATEX) --latex-args=-shell-escape $<

clean:
	$(LATEXRUN) --clean-all

.FORCE:

.PHONY: all clean .FORCE

# vim: ft=make
