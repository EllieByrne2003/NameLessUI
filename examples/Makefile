# Compiler and flags
CXX      := g++
CXXFLAGS := -fPIE -std=c++20 -g -O3 -Wunused
LDLIBS   := -DJSON_USE_IMPLICIT_CONVERSIONS=0 -lNLUT -lNLUI -lglfw -lGLEW -lEGL -lGL 

# Directories
SRCDIR   = .
BINDIR   = bin

# Automatically find all .cpp files in SRCDIR
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
# Convert each source file name into a target executable name in BINDIR
TARGETS  = $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%, $(SOURCES))

# Default target: build all executables
all: $(TARGETS)

# Rule to build each executable from its corresponding .cpp file
$(BINDIR)/%: $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

# Clean up the bin directory
clean:
	rm -rf $(BINDIR)

# Declare phony targets (not real files)
.PHONY: all clean