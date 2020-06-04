# compiler
CXX = g++

# compiler flags
CXXFLAGS = -Wall

# files to be linked
FILES = main.cc pixel.cc colors.cc file.cc

# normal
main:
	${CXX} ${CXXFLAGS} ${FILES} -o imgtr

# for debugging
debug:
	${CXX} ${CXXFLAGS} -g ${FILES} -o imgtr-d

# These are for when the output file is named "out.bmp"
# delete executables
clean:
	rm -r imgtr out.bmp

# delete executable for debug
clean-debug:
	rm -r imgtr-d imgtr-d.dSYM out.bmp
