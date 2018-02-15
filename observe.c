#include <stdio.h>

// read /proc/cpuinfo and output
int main(void) {
  // char st[] ="Where there is will, there is a way.";
  // char *ch;
  // ch = strtok(st, " ");
  // while (ch != NULL) {
  // printf("%s\n", ch);
  // ch = strtok(NULL, " ,");
  // }
  // return 0;

	char *string = "qwe : rty";
	char *e;
	int index;

	e = strchr(string, ':');
	e++;
	while(isspace((unsigned char)*e)) e++;
	index = (int)(e - string);

	printf("%s\n", string);
	printf(e);
}