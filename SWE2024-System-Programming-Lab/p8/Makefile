TARGET=ex8
CXX=gcc
OBJECTS=ex8.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

ex8.o: ex8.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
