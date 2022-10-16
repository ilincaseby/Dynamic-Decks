#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Return a pointer to the deck
whose index is given*/
dll_node_t *
get_the_deck(decks_dlist *b_list, dll_node_t *deck, int deck_index)
{
	deck = b_list->head;
	for (int i = 0; i < deck_index; ++i)
		deck = deck->next;
	return deck;
}

/*Scan no_cards playing cards valid and
append them to the deck*/
void
AddToLast(dll_node_t *deck, int no_cards)
{
	dll_node_t *card = (dll_node_t *) deck->head_or_v;
	if (card) {
		while (card->next)
			card = card->next;
	}
	char *symbol = malloc(command_size);
	if (!symbol) {
		fprintf(stderr, "Malloc failed\n");
	}
	int value;
	int *size;
	for (int i = 0; i < no_cards; ++i) {
		size = (int *) deck->size_or_sy;
		scanf("%d %s", &value, symbol);

		if ((*size) >= 1) {
			add_to_last_card(deck, &value, symbol);
		} else {
			add_to_start_card(deck, &value, symbol);
		}
		(*((int *) deck->size_or_sy))++;
	}
	free(symbol);
}
/*Add no_cards playing cards at the final of a deck
which is indexed in a list at deck_index*/
void
AddCardsToDeck(decks_dlist *b_list, int deck_index, int no_cards)
{
	dll_node_t *deck = NULL;
	deck = get_the_deck(b_list, deck, deck_index);
	AddToLast(deck, no_cards);
	printf("The cards were successfully added to deck %d.\n", deck_index);
}