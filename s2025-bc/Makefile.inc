all: talk-slides.pdf

PUBLIC=../../../cs3130-website/slides/

%.pdf: %.tex .FORCE
	latexrun -W no-overfull --latex-cmd=$(LATEX) --latex-args=-shell-escape $<

clean:
	latexrun --clean-all

copy-public-final: talk-slides.pdf 
	cp talk-slides.pdf $(PUBLIC)/$(BASENAME)-cr.pdf

copy-public-heldback: talk-slides-heldback.pdf 
	cp talk-slides-heldback.pdf $(PUBLIC)/$(BASENAME)-cr.pdf

.FORCE:

.PHONY: all clean .FORCE 

# vim: ft=make
