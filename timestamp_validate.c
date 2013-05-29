#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Usage: gcc -o validate timestamp_validate.c
// ./validate -f [transcript you want to validate]
// 
// EXAMPLE OUTPUT:
// ./validate -f transcript1.txt
// ? != 0:00:00.000  			//Ignore output, comparing garbage before first two timestamps are read in.
// 0:15:23:00 != 0:15:22:00     //Error - check timestamp at 0:15:23
// 0:00:00:00 != 0:22:16:00		//Error - possibly due to reloading console and previous time marker being erased


FILE *fp = NULL;
#define DEBUG 1

void parseFile (char *file) {
	char line[2048];
	// doesn't handle extremely large datasets buffer is at 2048 currently
	// for larger datasets use manual testing
	char *token = NULL;
	int a;
	char tmp;
	char *line2;
	char prevend[12];
	char start[12];
	char end[12];
	char seps[] = ",";
	int i = 0, var = 0, ret=0;

	fp = fopen(file, "rt");
	if( fp != NULL ) {
		while( fgets(line, sizeof(line), fp) != NULL ) {
			i = 0;
			tmp = line[0];
			line2 = line;
			 a = (int) tmp;
			if (a == '0') {
				memcpy(&start, &line[0], 11);
				start[11] = '\0';
				memcpy(&end, &line[12], 11);
				end[11] = '\0';
		   		if(strcmp(prevend, start) != 0)
		   				printf("%s != %s\n",prevend, start );

		   		memcpy(&prevend, &end, 11);
			}
		}
		fclose(fp);
	} else {
		perror(file);
	}
}


int main (int argc, char *argv[]) {

	if( argc < 2 ) {
		printf("ERROR:Invalid Usage\n");
	} else {
		if(strncmp(argv[1], "-f", 2) == 0 ) {
			parseFile(argv[2]);
		}
	}
  return 0;
}
