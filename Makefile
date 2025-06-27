CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++20 $(MODE_FLAGS) -MMD -MP

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
INCDIR = include
BUILDDIR = build

TARGET = game.out

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.d,$(SRCS))

.PHONY: all debug release clean run

# Default target: builds debug version
all: debug

# Build for debugging (default)
debug: MODE_FLAGS = -g # Add debug symbols
debug: $(BUILDDIR) $(TARGET)
	@echo "--- Build complete (Debug) ---"

# Build for release (optimized)
release: MODE_FLAGS = -O2 # Optimize for speed
release: $(BUILDDIR) $(TARGET)
	@echo "--- Build complete (Release) ---"

# Rule to create the build directory if it doesn't exist
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)
	@echo "Created build directory: $(BUILDDIR)"

# Rule to link object files into the final executable
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Executable created: $@"

# Generic rule to compile a .cpp file into a .o file
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Include the auto-generated dependency files.
-include $(DEPS)

# Clean rule: remove all build artifacts
clean:
	@echo "Cleaning build directory and executable..."
	@rm -rf $(BUILDDIR) $(TARGET)
	@echo "Cleanup complete."

# Run rule: execute the game after building
run: $(TARGET)
	@echo "--- Running $(TARGET) ---"
	./$(TARGET)