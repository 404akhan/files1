#include <stdio.h>
#include <pwd.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void f1() {
	FILE* file = fopen("/proc/cpuinfo", "r");
	char line[256];
	char *e;

	int counter = 0;

	while(fgets(line, sizeof(line), file)) {
		if(strstr(line, "model name") != NULL) {
			e = strchr(line, ':');
			e++;
			while(isspace((unsigned char)*e)) e++;
			printf("Processor-%d: %s", counter++, e);
		}
	}
	fclose(file);
}

void f2() {
	char word1[256], word2[256], word3[256];
	FILE* file = fopen("/proc/version", "r");
	fscanf(file, "%s %s %s", word1, word2, word3);
	fclose(file);

	printf("%s %s %s\n", word1, word2, word3);
}

void f3() {
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

void f4() {
	double n_sec, dummy;
	FILE* file = fopen("/proc/uptime", "r");
	fscanf(file, "%lf %lf", &n_sec, &dummy);
	fclose(file);

	int dd = n_sec / 60 / 60 / 24;
	int hh = (n_sec - dd*24*60*60) / 60 / 60;
	int mm = (n_sec - dd*24*60*60 - hh*60*60) / 60;
	int ss = (n_sec - dd*24*60*60 - hh*60*60 - mm*60);

	printf("%02dD:%02dH:%02dM:%02dS\n", dd, hh, mm, ss);
}

void print_status(long tgid, int uid) {
	/**
		function "print_status" and beginning of "main" based on:
		https://stackoverflow.com/questions/29991182/programmatically-read-all-the-processes-status-from-proc
	*/
    char path[40], line[100], *p;
    FILE* statusf;

    snprintf(path, 40, "/proc/%ld/status", tgid);

    statusf = fopen(path, "r");
    if(!statusf)
        return;

    char dummy[100];
    char name[100];

    while(fgets(line, 100, statusf)) {
        if(strncmp(line, "Name:", 5) == 0) {
        	sscanf(line, "%s %s", dummy, name);
        }

        if(strncmp(line, "Uid:", 4) != 0)
            continue;
        p = line + 4;
        int uid1, uid2, uid3, uid4;

        sscanf(p, "%d %d %d %d", &uid1, &uid2, &uid3, &uid4);
        if(uid1 == uid) 
        	printf("%s: %ld\n", name, tgid);
        break;
    }

    fclose(statusf);
}


int main(int argc, char* argv[]) 
{
	DIR* proc = opendir("/proc");
	struct dirent* ent;
	long tgid;

	if(proc == NULL) {
	    perror("opendir(/proc)");
	    return 1;
	}

	char const* const user = argv[1];
	struct passwd *p;
	int uid;

	if (argc == 1) {
		printf("-------------------------Processer Type-------------------------\n");
		f1();
		printf("-------------------------Kernel Version-------------------------\n");
		f2();
		printf("------------------------Amount of Memory------------------------\n");
		f3();
		printf("----------------------Up Time Since Booted----------------------\n");
		f4();
	}
	else if ((p = getpwnam(user)) == NULL) {
		printf("Invalid username: %s\n\n", user);
	}
	else {
		uid = (int) p->pw_uid;

		while(ent = readdir(proc)) {
		    if(!isdigit(*ent->d_name))
		        continue;

		    tgid = strtol(ent->d_name, NULL, 10);

		    print_status(tgid, uid);
		}

		printf("\n");
		closedir(proc);
	}
}
