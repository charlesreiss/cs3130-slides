SLIDEDECKS = \
    accounts \
    bpred \
    building \
    buses \
    caching \
    deadlock \
    intro \
    kernel \
    logistics \
    network \
    ooo \
    pipeline \
    processors \
    secure \
    signals \
    spectre \
    sync \
    threads \
    unix-api \
    unwind \
    vm 

all: $(patsubst %,_dist/%.pdf,$(SLIDEDECKS))

clean:
	rm -r _dist

_dist:
	mkdir _dist

_dist/%.pdf: % _dist
	cd $< && make && cp talk-slides.pdf ../_dist/$<.pdf

.PHONY: all
