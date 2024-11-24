CC=gcc
CCFLAGS=

SRCS=main.c

TARGET=riscv-sim

OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(TARGET)

%.o:%.c
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@


.PHONY=clean

clean:
	rm -f $(OBJS) $(TARGET)
