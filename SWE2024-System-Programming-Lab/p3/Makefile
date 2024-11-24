TARGET=p2.out
CXX=gcc
OBJECTS=main.o plus.o minus.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $^

main.o: main.c
	$(CXX) -c $^
plus.o: plus.c
	$(CXX) -c $^
minus.o: minus.c
	$(CXX) -c $^

clean:
	rm $(OBJECTS) $(TARGET)
