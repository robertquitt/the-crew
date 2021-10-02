.PHONY: test
test: solve
	./solve

.PHONY: format
format: main.cpp
	clang-format -i $<

solve: main.cpp Card.h
	g++ $< -o $@ -I. -std=c++11
