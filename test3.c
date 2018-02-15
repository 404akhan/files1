#include <stdio.h>
#include <string.h>

int main()
{
	FILE* file = fopen("/proc/meminfo", "r");
	char line[256];
	char *e;

	while(fgets(line, sizeof(line), file)) {
		if(strstr(line, "MemTotal") != NULL) {
			e = strchr(line, ':');
			e++;
			while(isspace((unsigned char)*e)) e++;
			printf("Installed Memory: %s", e);
		}
	}
	fclose(file);
}