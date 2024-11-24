TARGET=p11
LDFLAGS=-lpthread
CXX=gcc
OBJECTS=p11.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)

p11.o: p11.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
