PROGRAM   = vaseljena
CC        = gcc
CFLAGS    =  -g -Wall 
LDFLAGS   = -lGL -lGLU -lglut -lm
OBJFILES  = draw.o functions.o main.o

all: $(PROGRAM)

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES) $(LDFLAGS)


.PHONY: clean dist

clean: 
	-rm -f $(OBJFILES) $(PROGRAM) *~


