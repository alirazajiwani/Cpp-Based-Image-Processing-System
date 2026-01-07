CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -DDEBUG
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
INCLUDE = -Iinclude
TARGET = IPrun

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
