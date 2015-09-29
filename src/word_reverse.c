#include <string.h> /* strlen(), strdup() */
#include <unistd.h> /* usleep() */
#include <stdlib.h> /* malloc() */

#include "../include/dbg.h"
#include "../include/word_reverse.h"

StrWordRev* new_swr(char* in_string){
	StrWordRev* new_swr = malloc(sizeof(StrWordRev));
	new_swr->raw_str = strdup(in_string);
	new_swr->prior = 0;
	new_swr->post = count_words(new_swr->raw_str)-1;
	new_swr->a = get_word_pos(new_swr->raw_str, new_swr->prior);
	new_swr->b = get_word_pos(new_swr->raw_str, new_swr->post);
	new_swr->state = SWAP;


	return new_swr;
}

void delete_swr(StrWordRev* swr){
	free(swr->raw_str);
	free(swr);
}

void tick_reverse_word(StrWordRev* swr){
	char t;
	if (swr->a == swr->b || (swr->prior >= swr->post)){
		swr->state = COMPLETE;
		return;
	}
	if (space_or_null(*(swr->a)) && space_or_null(*(swr->b))){
		swr->prior++;
		swr->post = count_words(swr->raw_str)-1 - swr->prior;
		swr->a = get_word_pos(swr->raw_str, swr->prior);
		swr->b = get_word_pos(swr->raw_str, swr->post);
		// swr->state = COMPLETE;
		return;
	} else if (*(swr->a) == ' '){
		scoot_right(swr->raw_str, (swr->a), (swr->b));
	} else if (space_or_null(*(swr->b))){
		scoot_left(swr->raw_str, (swr->a), (swr->b));
		(swr->a)--;
	} else {
		t = *(swr->a);
		*(swr->a) = *(swr->b);
		*(swr->b) = t;
	}
	// rev_debug_print(in_string, swr->a, swr->b);
	// usleep(50000);
	if (!space_or_null(*(swr->a))) (swr->a)++;
	if (!space_or_null(*(swr->b))) (swr->b)++;
}

int space_or_null(char x){
	if (x == ' ' || x == '\0'){
		return 1;
	}
	return 0;
}

int check_bounds(char* in_string, char* a, char* b){
	int len = strlen(in_string);
	if (a >= in_string &&
		a <= in_string+len &&
		a < b){
		if (b >= in_string &&
			b <= in_string+len &&
			b > a){
			return 1;
		}
	}
	return 0;
}

unsigned int count_words(char* in_string){
	unsigned int count = 0;
	int inword = 0;
	while (*in_string != '\0'){
		if (*in_string == ' ' && inword) {
			inword = 0;
			count++;
		} else if (*in_string != ' ' && !inword) {
			inword = 1;
		}
		in_string++;
	}
	if (inword){
		count++;
	}
	return count;
}

void print_word(char* in_string){
	int entered_word = 0;
	printf("'");
	while (1) {
		if (entered_word){
			if (*in_string == ' ' || *in_string == '\0'){
				break;
			}
			printf("%c", *in_string);
		} else if (!entered_word){
			if (*in_string == '\0'){
				break;
			}
			if (*in_string != ' '){
				entered_word = 1;
				printf("%c", *in_string);
			}
		}
		in_string++;
	}
	printf("'\n");
}

char* get_word_pos(char* in_string, int n){
	char* original_in_str = in_string;
	int within_word = 0,
	    count = 0;
    while (*in_string != '\0'){
    	if (!within_word){
    		if (*in_string != ' '){
    			within_word = 1;
    			if (count == n){
    				return in_string;
    			}
    			count++;
    		}
    	} else if (within_word){
    		if (*in_string == ' '){
    			within_word = 0;
    		}
    	}
    	in_string++;
    }
	log_err("Couldn't find nth word of string where n is %d and string is '%s'", n, original_in_str);
    return 0;
}

void rev_debug_print(char* in_string, char* a, char* b){
	// Special control characters to move the cursor up one row. This and the
	// carriage return allow us to over-write our text so it looks pretty fluid.
	// printf("\033[1A");
	// printf("\033[1A");
	// printf("\r");

	char* RED = "\033[48;5;125m";
	char* MAGENTA = "\033[48;5;25m";
	char* RESET = "\033[0m";

	char* chr_position = in_string;
	while (*chr_position != '\0'){
		// if (*chr_position == ' '){
		// 	printf(" ");
		if (chr_position == a){
			// Prints the char at a, but red
			printf("%s%c%s", RED, *chr_position, RESET);
		} else if (chr_position == b){
			// Prints the char at b, but magenta
			printf("%s%c%s", MAGENTA, *chr_position, RESET);
		} else {
			printf("%c", *chr_position);
		}
		chr_position++;
	}
	printf("\n");
	chr_position = in_string;

	while (*chr_position != '\0'){
		if (chr_position == a){
			// Prints the red pointer for a
			printf("%s%c%s", RED, '^', RESET);
		} else if (chr_position == b){
			// Prints the magenta pointer for b
			printf("%s%c%s", MAGENTA, '^', RESET);
		} else {
			printf(" ");
		}
		chr_position++;
	}
	printf("\n");
}

void scoot_right(char* in_string, char* a, char* b){
	if (!check_bounds(in_string, a, b)){
		log_err("During scoot_right, the pointers a and b are not within in_string.");
	}
	char t = *b;
	while (a != b){
		// rev_debug_print(in_string, a, b);
		// usleep(5000);
		b--;
		*(b+1) = *b;
	}
	*a = t;
}

void scoot_left(char* in_string, char* a, char* b){
	if (!check_bounds(in_string, a, b)){
		log_err("During scoot_right, the pointers a and b are not within in_string.");
	}
	char t = *a;
	while (a != b){
		// rev_debug_print(in_string, a, b);
		// usleep(5000);
		a++;
		*(a-1) = *a;
	}
	*(b-1) = t;
}

void word_swap(char* in_string, char* a, char* b){
	if (!check_bounds(in_string, a, b)){
		log_err("During word_swap, the pointers a and b are not within in_string.");
	}
	char t;
	rev_debug_print(in_string, a, b);
	usleep(50000);
	while (1) {
		if (space_or_null(*a) && space_or_null(*b)){
			return;
		} else if (*a == ' '){
			scoot_right(in_string, a, b);
		} else if (space_or_null(*b)){
			scoot_left(in_string, a, b);
			a--;
		} else {
			t = *a;
			(*a) = (*b);
			(*b) = t;
		}
		rev_debug_print(in_string, a, b);
		usleep(50000);
		if (!space_or_null(*a)) a++;
		if (!space_or_null(*b)) b++;
	}
}

char* in_place_reverse_words(char* in_string){
	char* phrase = in_string;
	int wc = count_words(phrase)-1;
	int prior = 0;

	printf("%s\n", in_string);
	printf("\n\n");
	sleep(2);
	while (1) {
		int post = wc - prior;
		char* priorpos = get_word_pos(phrase, prior);
		char* postpos = get_word_pos(phrase, post);
		if (priorpos == postpos || (prior >= post)){
			break;
		}
		word_swap(phrase, priorpos, postpos);
		prior++;
	}
	usleep(100000);
	return in_string;
}
