#include <stdio.h>
#include <string.h>

int main()
{
	double n_sec, dummy;
	FILE* file = fopen("/proc/uptime", "r");
	fscanf(file, "%lf %lf", &n_sec, &dummy);
	fclose(file);

	// printf("%lf %lf\n\n", n_sec, dummy);

	int dd = n_sec / 60 / 60 / 24;
	int hh = (n_sec - dd*24*60*60) / 60 / 60;
	int mm = (n_sec - dd*24*60*60 - hh*60*60) / 60;
	int ss = (n_sec - dd*24*60*60 - hh*60*60 - mm*60);

	printf("%dD:%dH:%dM:%dS\n", dd, hh, mm, ss);
}