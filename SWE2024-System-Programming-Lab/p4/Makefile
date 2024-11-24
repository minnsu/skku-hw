TARGET=ex4
CXX=gcc
OBJECTS=main.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

main.o: main.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET) Aladdin_num.txt
