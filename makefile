CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRCS = src/Property.cpp src/PropertyManager.cpp src/UserInterface.cpp src/PropertyValidator.cpp src/main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = real_estate_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)