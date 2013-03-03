BIN := binary

OPTIM := -O3

COUNT := 22460

COMPILE := $(CC) $(OPTIM)

vpath s.% $(BIN)

build:
	mkdir -p $(BIN)
	$(COMPILE) -o $(BIN)/s.c c/*.c 
	$(COMPILE) -o $(BIN)/s.cpp cpp/*.cpp -lstdc++
	$(COMPILE) -o $(BIN)/s.objc objc/*.m -framework Foundation

time:
	$(foreach v, $(wildcard $(BIN)/*), time $(v) $(COUNT);) 

size:
	$(foreach v, c cpp objc, echo $(v); cat $(v)/* | wc;) 

clean:
	rm -r $(BIN)

./PHONY: build time size clean