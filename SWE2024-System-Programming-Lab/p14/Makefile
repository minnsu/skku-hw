TARGET=p14
LDFLAGS=-pthread
CXX=gcc
OBJECTS=p14.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

p14.o: p14.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
