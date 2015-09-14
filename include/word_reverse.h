#ifndef WORD_REVERSE
#define WORD_REVERSE

#include <string.h>

typedef enum {
	SWAP,
	COMPLETE
} rev_state;

typedef struct {
	char* raw_str;
	char* a;
	char* b;
	int prior;
	int post;
	rev_state state;
} StrWordRev;

StrWordRev* new_swr(char* in_string);
void delete_swr(StrWordRev* swr);

void tick_reverse_word(StrWordRev* swr);

/**
 * @brief Checks if a char is a space or a null character.
 * @details Checks if a char is a space or a null character.
 * 
 * @param x The character to check.
 * @return 1 if character is a space or null, 0 if character is not those things.
 */
int space_or_null(char x);

/**
 * @brief Checks that variables are properly withing bounds.
 * @details Checks that a and b are both within in_string, and that a comes before b
 * 
 * @param in_string The full string being checked
 * @param a Pointer to a position within in_string
 * @param b Pointer to a position within in_string
 * @return 1 if strings meet checks, 0 if they do not.
 */
int check_bounds(char* in_string, char* a, char* b);

/**
 * @brief Counts the words in the string.
 * @details Counts the number of non-space (ASCII 32) clusters of characters there are in in_string
 * 
 * @param in_string The string being counted
 * @return Integer representing number of words in the string.
 */
unsigned int count_words(char* in_string);

/**
 * @brief Prints the first word found in the string.
 * @details Begins looking for the first non-space (ASCII 32) character. When found, begin printing successive characters until either a space (ASCII 32) or null character are found. If no words where found in the string, nothing is printed.
 * 
 * @param in_string Start of string to begin searching for word to print.
 */
void print_word(char* in_string);

/**
 * @brief Returns a pointer to the start of the nth word into the string.
 * @details Returns a pointer to the start of the nth word into the string, or returns 0 if the string does not contain enough words. For example, given "walk down the road" and n=1, return a pointer to the 'd' in "down". Given "some words" and n=2, return 0 because there are not enough words in the string (n is zero based index). A word is any grouping of characters that are non-space (space being ASCII 32) or null.
 * 
 * @param in_string The string to search for a word
 * @param n The 0 based index of the word to retrieve, as if the string where a list of words
 * 
 * @return Returns a pointer to the beginning of the nth word in the string, or 0 if the string doesn't have an nth word.
 */
char* get_word_pos(char* in_string, int n);

/**
 * @brief Prints a highlighted debug version of the given string and the position of a and b
 * 
 * @details Prints a representation of the string and the position of a and b.
 * This representation has colors for better highlighting and markers for a
 * and b. Excellent for debugging and for inspecting how operations on a string
 * are working. Parameters are run through the check_bounds function to ensure
 * that a and b are within in_string and a comes before b.
 * 
 * @param in_string The entire string
 * @param a Pointer to a within in_string
 * @param b Pointer to b within in_string
 */
void rev_debug_print(char* in_string, char* a, char* b);

/**
 * @brief Moves all characters between a and b to the right by one, with the character that was at b being moved to the beginning at position a. All parameters are bounds checked before hand.
 * 
 * @param in_string The string a and b are operating within.
 * @param a The start position
 * @param b Ending position
 */
void scoot_right(char* in_string, char* a, char* b);

/**
 * @brief Moves all characters between a and b to the left by one, with the character that was at a being moved to the end at position b. All parameters are bounds checked at the start of this program.
 * 
 * @param in_string The string a and b are within
 * @param a Start position
 * @param b End position
 */
void scoot_left(char* in_string, char* a, char* b);

/**
 * @brief Swaps the position of the words the beginning of a and b in place
 * @details Assuming a and b each mark the beginning of words within the string in_string, this swaps the words at a and b using a combination of direct swapping then by shifting characters around in the string till both the words have been swapped. This does not touch the spacing, so the spacing will remain the same relative to it's position between words, though their absolute positions within the string may change. This function will swap words in place, allocating no extra memory.
 * 
 * @param in_string The string a and b are within.
 * @param a The beginning of the first word
 * @param b The beginning of the second word
 */
void word_swap(char* in_string, char* a, char* b);

/**
 * @brief Does an in-place reversal of the order of the words in the string.
 * @details Using direct swapping and scooting, this will reverse the order of the words in the string. For example, "what's up doc" becomes "doc up what's". Additionally, the order of spacing is preserved, so "  how do    you do" becomes "  do you    do how". This reverses the words in the string in-place, making no additional memory allocations on the heap.
 * 
 * @param in_string The string with the words to be reversed.
 * @return Returns in_string, but now the words within it have been reversed.
 */
char* in_place_reverse_words(char* in_string);




#endif