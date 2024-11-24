TARGET=p5
CXX=gcc
OBJECTS=p5.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

p5.o: p5.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
