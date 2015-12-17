.PHONY: all test clean

all: test


command_line: command_line.cpp perfecthash.h command_options.h
	$(CXX) $< -std=c++11 -lstdc++ -o $@

perfecthash.h: command_line_options.gperf
	gperf -CGD -N IsValidCommandLineOption -K Option -L C++ -t $< > $@

clean:
	rm -f perfecthash.h

test: command_line
	./command_line +helpverbose -xyz +nolog
