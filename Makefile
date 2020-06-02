all:
	gcc main.c image.c -lglut -lGLU -lGL -lm
clean:
	rm -rf *.o *~ a.out
