CC = gcc
TARGET = hw1
OBJECTS = sfp.o hw1.o

$(TARGET) : hw1.o sfp.o
	$(CC) -o $(TARGET) $(OBJECTS)

hw1.o : hw1.c
	$(CC) -c -o hw1.o hw1.c

sfp.o : sfp.c
	$(CC) -c -o sfp.o sfp.c

clean :
	rm *.o $(TARGET)
