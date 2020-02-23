#http://makefiletutorial.com/ P1G126 875287 875537
objects = project_main.o parser.o print_exec.o project.o
eseguibile = progetto
cflags = -g3 -std=gnu89 -pedantic-errors -Wall -Wextra -fsanitize=undefined -fsanitize=address 
libs = -lm

$(eseguibile): $(objects)
	gcc $(cflags) -o $(eseguibile) $(objects) $(libs)

clean:
	rm $(eseguibile)  $(objects)

#regole implicite
.c.o :
	gcc -c $(cflags) $< 
.h.c :
	touch $<