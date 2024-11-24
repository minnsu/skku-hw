TARGET=p9
CXX=gcc
OBJECTS=p9.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

p9.o: p9.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
