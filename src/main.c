#include <stdio.h>
#include <string.h> /* strdup() */
#include <stdlib.h> /* free() */

#include "../include/word_reverse.h"


int main(int argc, char const *argv[]){
	char* test[] = {
		"spinelessness prayed doppelgangers notabilities syllabification unflinching",
		"coccyx Msgr environments subjecting Duroc ibis  fetus whack wile",
		"nippy demoed pretax voltmeters bougainvillea garish weedkillers",
	};
	int i = 0;
	for (i = 0; i < 3; ++i){
		char* rv = in_place_reverse_words(strdup(test[i]));
		free(rv);
	}
	return 0;
}


