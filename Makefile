CC = g++
CFLAGS = -std=c++2a -Wall -O2

# List of source files
SRCS = game_of_life.cpp

# List of object files, automatically generated from sources
OBJS = $(SRCS:.cpp=.o)

# Name of the executable
EXE = game_of_life

# Rule to clean up object files and the executable
clean:
	rm -rf build

# Rule to build and run the program
run: $(EXE)
	@./build/$(EXE)

# Add a build directory for object files and executable
$(OBJS): | build
build:
	@mkdir -p build

# Put object files in the build directory
%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o build/$@

# Put the executable in the build directory
$(EXE): $(OBJS)
	@$(CC) $(CFLAGS) -o build/$@ build/$^
