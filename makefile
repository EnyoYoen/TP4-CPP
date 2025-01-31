CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
LDFLAGS =
SRCS = main.cpp Reader.cpp Graph.cpp Request.cpp DateTime.cpp
HEADERS = Reader.h Graph.h Request.h
OBJS = $(addprefix bin/, $(notdir $(SRCS:.cpp=.o)))
TARGET = bin/analog

# Create the bin directory if it doesn't exist
# On Windows, remove the -p option for mkdir
ifeq ($(OS),Windows_NT)
	MKDIR = mkdir bin
else
	MKDIR = mkdir -p bin
endif

$(shell $(MKDIR))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

bin/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean