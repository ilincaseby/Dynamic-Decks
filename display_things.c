#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Scan an index and based on that, display
the number of cards contained by the
scanned index deck*/
void
disp_no_cards(decks_dlist *b_list)
{
	int deck_index;
	scanf("%d", &deck_index);

	dll_node_t *deck = NULL;
	deck = get_the_deck(b_list, deck, deck_index);

	int *sizey = (int *) deck->size_or_sy;
	printf("The length of deck %d is %d.\n", deck_index, *sizey);
}

/*Display the number of decks*/
void
display_how_many(decks_dlist *b_list)
{
	u_i how_many = b_list->size;
	printf("The number of decks is %u.\n", how_many);
}