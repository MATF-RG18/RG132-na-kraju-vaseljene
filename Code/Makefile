PROGRAM   = vaseljena
CC        = gcc
CFLAGS    =  -g -Wall 
LDFLAGS   = -lGL -lGLU -lglut -lm
OBJFILES  = functions.o scene.o player.o obstacles.o textures.o main.o image.o

all: $(PROGRAM)

$(PROGRAM): $(OBJFILES)
	$(CC) -o $(PROGRAM) $(OBJFILES) $(LDFLAGS)


.PHONY: clean dist

clean: 
	-rm -f $(OBJFILES) $(PROGRAM) *~


