#include <stdio.h>
#include <string.h>

int main()
{
	char word1[256], word2[256], word3[256];
	FILE* file = fopen("/proc/version", "r");
	fscanf(file, "%s %s %s", word1, word2, word3);
	fclose(file);

	printf("%s %s %s\n", word1, word2, word3);
}