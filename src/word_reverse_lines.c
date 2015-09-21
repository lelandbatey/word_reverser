#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/dbg.h"

#include "../include/word_reverse.h"


int all_complete(StrWordRev** list, int len){
	int i = 0;
	for (i = 0; i < len; ++i){
		if (list[i]->state != COMPLETE){
			return 0;
		}
	}
	return 1;
}

char* remove_newline(char* line){
	while(*line != '\0'){
		if (*line == '\n' || *line == '\r'){
			*line = ' ';
		}
		line++;
	}
	return line;
}

int reverse_file(char* file_path, int simul_count){

	int i = 0;

	FILE *fp = fopen(file_path, "r");
	int count = 0;
	char* line = 0;
	StrWordRev* lines[simul_count];

	size_t len = 0;
	ssize_t read;

	while(1){
		// Get `simul_count` number of strings from files, turning them into SWR structs.
		for (i = 0; i < simul_count; ++i){
			read = getline(&line, &len, fp);
			if (read == -1){
				fclose(fp);
				return 1;
			}
			remove_newline(line);
			lines[i] = new_swr(line);
			free(line);
			line = 0;
		}
		while (!all_complete(lines, simul_count)){
			for (i = 0; i < simul_count; ++i){
				printf("\033[1A");
				printf("\033[1A");
				printf("\r");
			}
			for (i = 0; i < simul_count; ++i){
				if (lines[i]->state != COMPLETE){
					tick_reverse_word(lines[i]);
				}
				rev_debug_print(lines[i]->raw_str, lines[i]->a, lines[i]->b);
			}
			usleep(50000);
		}
		for (i = 0; i < simul_count; ++i){
			rev_debug_print(lines[i]->raw_str, lines[i]->a, lines[i]->b);
		}
	}
	fclose(fp);
	return 0;
}


