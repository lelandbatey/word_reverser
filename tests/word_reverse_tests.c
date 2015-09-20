#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/minunit.h"
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

char* test_tick_file_many(){
	int i = 0;
	// Number of lines to be reversing at once
	int sim_count = 20;

	FILE *fp = fopen("./lines.txt", "r");
	int count = 0;
	char* line = 0;
	StrWordRev* lines[sim_count];

	size_t len = 0;
	ssize_t read;

	// printf("Begin visualization.\n");
	while (1){
		// Get `sim_count` strings from files, turning them into SWR structs.
		for (i = 0; i < sim_count; ++i){
			read = getline(&line, &len, fp);
			if (read == -1){
				fclose(fp);
				return;
			}
			remove_newline(line);
			lines[i] = new_swr(line);
			free(line);
			line = 0;
		}
		while (!all_complete(lines, sim_count)){
			for (i = 0; i < sim_count; ++i){
				printf("\033[1A");
				printf("\033[1A");
				printf("\r");
			}
			for (i = 0; i < sim_count; ++i){
				if (lines[i]->state != COMPLETE){
					tick_reverse_word(lines[i]);
				}
				rev_debug_print(lines[i]->raw_str, lines[i]->a, lines[i]->b);
			}
			usleep(50000);
		}
		for (i = 0; i < sim_count; ++i){
			rev_debug_print(lines[i]->raw_str, lines[i]->a, lines[i]->b);
		}
	}
	fclose(fp);
	return NULL;
}


char* test_tick_many(){
	int i = 0;
	int len = 3;
	char* test[] = {
		"spinelessness prayed doppelgangers notabilities syllabification unflinching",
		"coccyx Msgr environments subjecting Duroc ibis  fetus whack wile",
		"nippy demoed pretax voltmeters bougainvillea garish weedkillers",
	};
	StrWordRev* w_list[len];

	for (i = 0; i < len; ++i){
		w_list[i] = new_swr(test[i]);
	}

	while (!all_complete(w_list, len)){
		for (i = 0; i < len; ++i){
			printf("\033[1A");
			printf("\033[1A");
			printf("\r");
		}
		for (i = 0; i < len; ++i){
			if (w_list[i]->state != COMPLETE){
				tick_reverse_word(w_list[i]);
			}
			rev_debug_print(w_list[i]->raw_str, w_list[i]->a, w_list[i]->b);
		}
		usleep(50000);
	}
	return NULL;

}

char* test_tick_reverse_word(){
	char* test_sentence = "this is a test of some kind.";
	StrWordRev* swr = new_swr(test_sentence);

	printf("Attempting to print new swr.\n");
	rev_debug_print(swr->raw_str, swr->a, swr->b);
	// return NULL;

	while (swr->state != COMPLETE){
		tick_reverse_word(swr);
		rev_debug_print(swr->raw_str, swr->a, swr->b);
	}
	return swr->raw_str;
}


RUN_TESTS(test_tick_file_many);
