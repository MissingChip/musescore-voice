# TODO: Use another build system like Ninja

main: main.cpp
	$(CXX) $< -o $@
