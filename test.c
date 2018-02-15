// #include <stdio.h>

// // read /proc/cpuinfo and output

// int main() {
// 	char text[10000] = "asd";


// }

// #include<stdio.h>
// int main()
// {
// 	/*declare and initialise variable*/
// 	char message[1000];
// 	int i=2;
// 	FILE *file_in;
// 	file_in=fopen("/proc/cpuinfo", "r");
// 	/*stores and prints the data from the string*/
// 	fscanf(file_in,"%s : %d", message, &i);
// 	printf("%s %d\n", message, i);
//     return 0;
// }

// #include <stdio.h>

// int main(int argc, char* argv[])
// {
//     char const* const fileName = argv[1]; /* should check that argc > 1 */
//     FILE* file = fopen(fileName, "r"); /* should check the result */
//     char line[256];
//     char model_name[256];
// 	char *e;


//     int counter = 1;

//     while (fgets(line, sizeof(line), file)) {
//         // if(strcmp(line, "model name") == 0)
//         if(strstr(line, "model name") != NULL) {
//         	// sscanf(line, "%s %s : %s", model_name, model_name, model_name);
//         	// printf("%s", model_name); 
// 			e = strchr(line, ':');
// 			e++;
// 			while(isspace((unsigned char)*e)) e++;
// 			printf(e);
//         }
//         if(counter++ >= 10)
//         	break;
//     }
//     fclose(file);

//     return 0;
// }

#include <stdio.h>
#include <string.h>

int main()
{
	FILE* file = fopen("/proc/cpuinfo", "r");
	char line[256];
	char *e;

	while(fgets(line, sizeof(line), file)) {
		if(strstr(line, "model name") != NULL) {
			e = strchr(line, ':');
			e++;
			while(isspace((unsigned char)*e)) e++;
			printf(e);
		}
	}
	fclose(file);
}