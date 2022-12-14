SLIDEDECKS = \
    FIXME

all: $(patsubst %,dist/%.pdf,$(SLIDEDECKS))

clean:
	rm -r dist

dist:
	mkdir dist

dist/%.pdf: % dist
	cd $< && make && cp talk-slides.pdf ../dist/$<.pdf

.PHONY: all
