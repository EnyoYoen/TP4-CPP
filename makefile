CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
LDFLAGS =

SRCS = main.cpp Reader.cpp Graph.cpp Request.cpp
HEADERS = Reader.h Graph.h Request.h
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean