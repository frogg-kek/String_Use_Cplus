CXX = g++
CXXFLAGS = -std=c++20 -Wall

TARGET = find
SRC = main.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)