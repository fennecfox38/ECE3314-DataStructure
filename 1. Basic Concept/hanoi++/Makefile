CXX = g++
ifeq ($(RELEASE),1)
CXXFLAGS = -O2 -DNDEBUG -c
LDFLAGS = -O2 -DNDEBUG -o
else
CXXFLAGS = -c -g -O0 -DDEBUG -W -Wall
LDFLAGS = -O0 -DDEBUG -W -Wall -o
endif
SRCS = $(notdir $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out
 
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(TARGET) $(OBJS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $<

run:
	./$(TARGET)

clean:
	rm *.o $(TARGET)