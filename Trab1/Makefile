CC = gcc
CFLAGS =
PROG = projeto1
SRCS = projeto1.c
LIBS = -lGLU -lGL -lglut -lSOIL -lm -pthread

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(SRCS) $(LIBS) $(CFLAGS) -o $(PROG)

clean:
	rm -f $(PROG)

run:
	./$(PROG)