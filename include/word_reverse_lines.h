
#include "../include/word_reverse.h"


/**
 * @brief Checks if a list of StrWordRev are all completed
 * @details Checks if a list of StrWordRev are all in the state COMPLETE 
 * 
 * @param list Array of pointers to instances of StrWordRev
 * @param len Length of the `list` parameter
 * @return 1 if all StrWordRevs are in the state COMPLETE, else return 0
 */
int all_complete(StrWordRev** list, int len);

/**
 * @brief Removes carriage returns and newlines from the given string
 * @details Replaces carriage returns and newlines with spaces
 * 
 * @param line String to have newlines removed from
 * @return Returns the `line` parameter, but now without newlines
 */
char* remove_newline(char* line);


/**
 * @brief Visualy reverses n strings at a time from source file `file_path`
 * @details Given a path to a file to read lines from `file_path` and a number of lines to run reversals on from `simul_count`, print a conduct in-place reversal of the words in the line with colorful visualization of the process written to stdout
 * 
 * @param file_path Path to the file to read lines from
 * @param simul_count Number of lines at a time to do in-place reversal on
 * @return Returns 0 if successful, 1 if something bad happens when reading the file
 */
int reverse_file(char* file_path, int simul_count);


