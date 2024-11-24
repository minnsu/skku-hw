TARGET=p13
LDFLAGS=-pthread
CXX=gcc
OBJECTS=p13.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

p13.o: p13.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
