CXX = g++
CXXFLAGS = -g -Wall --std=c++11
TARGET = main

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: clean run

all: clean $(TARGET) run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.h:
	@:

clean:
	rm -rf $(OBJS) $(TARGET)

run:
	./$(TARGET)