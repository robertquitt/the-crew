solve: main.cpp Card.h
	# g++ $< -o $@ -I. -std=c++11 -Wall -Wno-switch -Wno-return-type -O3 -fsanitize=address
	g++ $< -o $@ -I. -std=c++11 -Wall -Wno-switch -Wno-return-type -O3

.PHONY: test
test: solve
	./solve

.PHONY: format
format: main.cpp
	clang-format -i $<

