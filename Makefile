# Makefile

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include -I/opt/homebrew/opt/boost/include

# Boost Library Path
BOOST_PATH = /opt/homebrew/opt/boost
BOOST_LIBS = -L$(BOOST_PATH)/lib -lboost_system -lboost_filesystem

# Source Files
SRC = src/main.cpp \
      src/AdminLogSplayTree.cpp \
      src/Driver.cpp \
      src/FareCalculator.cpp \
      src/Passenger.cpp \
      src/PassengerLogSplayTree.cpp \
      src/RTree.cpp \
      src/RideRequest.cpp

# Object Files
OBJ = $(SRC:.cpp=.o)

# Executable Name
TARGET = ride-sharing-system

# Default Target
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOST_LIBS)

# Compile Source Files into Object Files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Up Build Files
clean:
	rm -f src/*.o $(TARGET)

# Phony Targets
.PHONY: all clean

