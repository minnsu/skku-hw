TARGET=p7
CXX=gcc
OBJECTS=p7.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

p7.o: p7.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
