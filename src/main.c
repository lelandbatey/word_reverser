#include <stdio.h>
#include <string.h> /* strdup() */
#include <stdlib.h> /* realpath(), free() */
#include <getopt.h> /* getopt */
#include <limits.h> /* PATH_MAX */
#include <errno.h>  /* errno */

#include "../include/word_reverse.h"
#include "../include/word_reverse_lines.h"

void print_usage(){
	printf("%s", "TODO: implement usage");
}


int main(int argc, char *const *argv){
	char buf[PATH_MAX+1];
	char *simcount = 0;
	int simul_count = 10;
	char *original_path = 0;
	int path_passed = 0;

	int opt= 0;
	//Specifying the expected options
	// TODO: set simcount as an optional parameter
	static struct option long_options[] = {
		{"simcount",  required_argument, 0,  's' },
		{"path",      required_argument, 0,  'p' },
		{"help",      no_argument,       0,  'h' },
		{0,           0,                 0,   0  }
	};

	int long_index =0;
	while ((opt = getopt_long(argc, argv, "s:p:",
				long_options, &long_index )) != -1) {
		switch (opt) {
			// `optarg` is a global variable from getopt.h
			case 's' : simcount = strdup(optarg);
				break;
			case 'p' : path_passed = 1; original_path = realpath(optarg, buf);
				break;
			case 'h' : print_usage(); exit(0);
			default: print_usage();
				exit(EXIT_FAILURE);
		}
	}

	// Check that a path was specified and that it is a valid path
	if (path_passed && !original_path) {
		printf("Path was given, but was invalid.\n");
		print_usage();
		exit(EXIT_FAILURE);
	} else if (!path_passed) {
		printf("Path was not specified.\n");
		print_usage();
		exit(EXIT_FAILURE);
	}

	// Convert the given "simcount" to a number, store in `simul_count`
	if (simcount){
		errno = 0;
		long tmp = strtol(simcount, 0, 10);
		// TODO: implement converter
		if (errno != 0){
			printf("Could not convert specified simcount into a valid number.\n");
			print_usage();
			exit(EXIT_FAILURE);
		}
		simul_count = tmp;
	}

	printf("original_path: %s, simul_count: %d\n", original_path, simul_count);

	reverse_file(original_path, simul_count);

	//char* test[] = {
	//	"spinelessness prayed doppelgangers notabilities syllabification unflinching",
	//	"coccyx Msgr environments subjecting Duroc ibis  fetus whack wile",
	//	"nippy demoed pretax voltmeters bougainvillea garish weedkillers",
	//};
	//int i = 0;
	//for (i = 0; i < 3; ++i){
	//	char* rv = in_place_reverse_words(strdup(test[i]));
	//	free(rv);
	//}
	return 0;
}


