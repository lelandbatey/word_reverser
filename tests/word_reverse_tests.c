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



char* test_tick_reverse_word(){
	char* test_sentence = "this is a test of some kind.";
	char* reversed = "kind. some of test a is this";
	StrWordRev* swr = new_swr(test_sentence);

	while (swr->state != COMPLETE){
		tick_reverse_word(swr);
	}
	if (strcmp(swr->raw_str, reversed)){
		log_err("Strings not equal. Raw: '%s', reversed: '%s'", swr->raw_str, reversed);
	}
	mu_assert(!strcmp(swr->raw_str, reversed), "The reversed string and the result are not equal.");
	return NULL;
}

char* test_space_or_null(){
	int i = 0;
	for (i = 0; i < 128; i++){
		if (i == ' ' || i == '\0'){
			mu_assert(space_or_null(i) == 1, "space_or_null didn't recognize a space or a null");
		} else {
			mu_assert(space_or_null(i) == 0, "space_or_null incorrectly recognized a space or a null");
		}
	}
	return NULL;
}

char* test_check_bounds(){
	char* example_str = "this is a test sentence composed of words.";
	char* a = (char*)example_str+5;
	char* b = (char*)example_str+33;
	mu_assert(check_bounds(example_str, a, b), "check_bounds incorrectly classified the given string as invalid.");
	a = (char*)example_str+15;
	b = (char*)example_str+10;
	mu_assert(!check_bounds(example_str, a, b), "check_bounds incorrectly classified the given string as valid.");
	return NULL;
}

char* test_get_word_pos(){
	int i = 0;
	char* test_sentence = "this is a test sentence composed of words.";
	int word_indices[8] = {0, 5, 8, 10, 15, 24, 33, 36};
	for (i = 0; i < 8; i++){
		char *tmp = get_word_pos(test_sentence, i);
		if (tmp-test_sentence != word_indices[i]){
			log_err("tmp: %ld, test_sentence: %ld, Returned %ld, should be %d", (long)tmp, (long)test_sentence, tmp-test_sentence, word_indices[i]);
		};
		mu_assert((tmp-test_sentence == word_indices[i]), "Returned incorrect position.");
	}
	return NULL;
}


char* all_tests(){
	mu_suite_start();

	mu_run_test(test_space_or_null);
	mu_run_test(test_check_bounds);
	mu_run_test(test_get_word_pos);
	mu_run_test(test_tick_reverse_word);
	return NULL;
}

RUN_TESTS(all_tests);
