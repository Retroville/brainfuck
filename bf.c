#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 1024

int brainfuck(char *src) 
{
	char tape[1000] = {0};
	char *ptr = tape;
	char c;
	int lvl; //current loop level
	int i;

	while (c = *src++) {
		switch (c) {
			case '>':  ++ptr; break;
			case '<':  --ptr; break;
			case '+': ++*ptr; break;
			case '-': --*ptr; break;
			case '.':  putchar(*ptr); break;
			case ',': *ptr=getchar(); break;
			case '[': 
				if (!(*ptr)) {
					while ((c = *src++) != ']');
				}
				break;
			case ']': 
				lvl = 1;
				src -= 2;
				while (lvl > 0) {
					c = *--src;
					if (c == '[')
						lvl--;
					else if (c == ']') 
						lvl++;
				}	
				break;
		}
	}
	putchar('\n');
	return 0;
}

int main()
{
	char *source;		/* Buffer to contain brainfuck source */
	int size, max;	/* Size of the source buffer */
	int c;					/* Current (char) int read from stdin */
	int i, j;

	//why
	source = malloc(BUFSIZE * sizeof(char));

	max = BUFSIZE;
	size = 0;
	source[size] = '\n';

	while ((c = getchar()) != EOF) {

		source[size++] = (char) c;
		source[size] = '\n';

		//why
		if (size >= max - 1) {
			max *= 2;
			source = realloc(source, max);
		}
	}

	brainfuck(source);

	return 0;
}
