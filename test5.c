// #include <stdio.h>
// #include <pwd.h>

// int main(int argc, char* argv[])
// {
// 	char const* const user = argv[1];
// 	struct passwd *p;
// 	int uid;

// 	if ((p = getpwnam(user)) == NULL) {
// 		printf("Invalid username: %s\n", user);
// 	}
// 	else {
// 		uid = (int) p->pw_uid;
		
// 		// printf("  pw_uid   : %d\n", uid);


// 	}
// }



#include <stdio.h>
#include <pwd.h>
#include <dirent.h>

// https://stackoverflow.com/questions/29991182/programmatically-read-all-the-processes-status-from-proc

void print_status(long tgid, int uid) {
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
        // Ignore "State:" and whitespace
        // 	return name_of_process;

        if(uid1 == uid) 
        	printf("%s: %d\n", name, tgid);
        break;
    }

    fclose(statusf);
}

int main(int argc, char* argv[]) {
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

	if (user == NULL) {
		printf("Error: no username provided\n");
	}
	else if ((p = getpwnam(user)) == NULL) {
		printf("Invalid username: %s\n", user);
	}
	else {
		uid = (int) p->pw_uid;

	// printf("  pw_uid   : %d\n", uid);

		while(ent = readdir(proc)) {
		    if(!isdigit(*ent->d_name))
		        continue;

		    tgid = strtol(ent->d_name, NULL, 10);

		    print_status(tgid, uid);
		}

		closedir(proc);

	}


}