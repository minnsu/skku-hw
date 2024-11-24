TARGET=pa2
CXX=gcc
OBJECTS=main.o

CLEANING=head tail cat cp mv rm pwd

all:pa2 head tail cat cp mv rm pwd

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $<

main.o: main.c
	$(CXX) -c $<

head: head.c
	$(CXX) -o $@ $<
tail: tail.c
	$(CXX) -o $@ $<
cat: cat.c
	$(CXX) -o $@ $<
cp: cp.c
	$(CXX) -o $@ $<
mv: mv.c
	$(CXX) -o $@ $<
rm: rm.c
	$(CXX) -o $@ $<
pwd: pwd.c
	$(CXX) -o $@ $<

clean:
	rm $(OBJECTS) $(TARGET) $(CLEANING)