all: rosenbroke

clear:
	rm -f rosenbroke
	rm $(OBJS)

OBJS = main.o error.o config.o matrix.o rhfns.o rsnbrk.o

CPPFLAGS = -O2
rosenbroke: $(OBJS)
	c++ -o rosenbroke $(OBJS) -lm

