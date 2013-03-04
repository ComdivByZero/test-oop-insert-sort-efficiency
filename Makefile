BIN := binary

OPTIM := -O3

COUNT := 22460

COMPILE := $(CC) $(OPTIM) -o $(BIN)/s
COBJC=$(COMPILE).objc objc/*.m
LMAC=-framework Foundation
LLIN=`gnustep-config --objc-flags` -lgnustep-base

vpath s.% $(BIN)

build:
	mkdir -p $(BIN)
	$(COMPILE).c c/*.c
	$(COMPILE).cpp cpp/*.cpp -lstdc++
	if test `uname` = Darwin; then $(COBJC) $(LMAC); else $(COBJC) $(LLIN); fi

time:
	$(foreach v, $(wildcard $(BIN)/*), time $(v) $(COUNT);)

size:
	$(foreach v, c cpp objc, echo $(v); cat $(v)/* | wc;)

clean:
	rm -r $(BIN)

./PHONY: build time size clean
