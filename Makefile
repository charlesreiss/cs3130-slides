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
    side-channel \
    signals \
    spectre \
    sync \
    threads \
    unix-api \
    unwind \
    vm 

all: $(patsubst %,dist/%.pdf,$(SLIDEDECKS))

clean:
	rm -r dist

dist:
	mkdir dist

dist/%.pdf: % dist
	cd $< && make && cp talk-slides.pdf ../dist/$<.pdf

.PHONY: all
