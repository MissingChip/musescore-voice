# TODO: Use another build system like Ninja
LIB_DIRS = -Lportaudio/lib/.libs

main: main.cpp
	$(CXX) $< -o $@

portaudio_test: portaudio_test.cpp
	$(CXX) $< -o $@ -lportaudio