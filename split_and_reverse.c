#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Being given an index and a new empty deck,
this function takes the pointer to the card with the
given index and tie it to the new deck, this way, the deck
is divided into two new decks.*/
void
address_cards_into_new(dll_node_t *new_deck, dll_node_t *deck, int split_index)
{
	dll_node_t *card = (dll_node_t *) deck->head_or_v;
	for (int i = 0; i < split_index; ++i)
		card = card->next;
	dll_node_t *last_card_old_deck = card->prev;
	last_card_old_deck->next = NULL;
	card->prev = NULL;
	new_deck->head_or_v = (void *) card;
}

/*Function requires two indexs, one for deck and
one for the card whose index is used to split the
deck in two parts. The new deck is added in the list
immediately after the one chosen.*/
void
split_it(decks_dlist *b_list)
{
	int deck_index, split_index;
	scanf("%d %d", &deck_index, &split_index);
	dll_node_t *deck = NULL;
	deck  = get_the_deck(b_list, deck, deck_index);

	int *size = (int *) deck->size_or_sy;
	if (*size == 0) {
		printf("The deck %d was successfully split by %d.\n", deck_index, split_index);
		return ;
	}
	if (split_index == 0 || split_index == (*size)) {
		printf("The deck %d was successfully split by %d.\n", deck_index, split_index);
		return ;
	}
	dll_node_t *new_deck = allocate_deck(new_deck);
	address_cards_into_new(new_deck, deck, split_index);
	if (deck->next) {
		dll_node_t *next_deck = deck->next;
		deck->next = new_deck;
		new_deck->next = next_deck;
		new_deck->prev = deck;
		next_deck->prev = new_deck;
		b_list->size++;
	} else if (!deck->next) {
		add_to_inited_l(new_deck, b_list);
		b_list->size++;
	}

	int dif = (*size) - split_index;
	memcpy(new_deck->size_or_sy, &dif, sizeof(int));
	dif = (*size) - dif;
	memcpy(deck->size_or_sy, &dif, sizeof(int));
	printf("The deck %d was successfully split by %d.\n", deck_index, split_index);
}

/*Returns a pointer to the last card of a deck*/
dll_node_t *
get_last_card(dll_node_t *deck, dll_node_t *card)
{
	card = (dll_node_t *) deck->head_or_v;
	while (card->next)
		card = card->next;
	return card;
}

/*The new deck will have the cards in reverse order*/
void
init_new_w_rev_cards(dll_node_t *new_deck, dll_node_t *card, int contor)
{
	while (card) {
		if (contor != 0) {
			add_to_last_card(new_deck, card->head_or_v, card->size_or_sy);
			card = card->prev;
			continue;
		}
		add_to_start_card(new_deck, card->head_or_v, card->size_or_sy);
		card = card->prev;
		contor++;
	}
}

/*Reverse the order of cards inside the deck
whose index is scanned*/
void
get_rev_deck(decks_dlist *b_list)
{
	int deck_index;
	scanf("%d", &deck_index);
	dll_node_t *deck = NULL;
	deck = get_the_deck(b_list, deck, deck_index);

	int *verify = (int *) deck->size_or_sy;
	if (*verify == 0) {
		printf("The deck %d was successfully reversed.\n", deck_index);
		return ;
	}

	dll_node_t *card = NULL;
	card = get_last_card(deck, card);
	dll_node_t *new_deck = NULL;
	new_deck = allocate_deck(new_deck);

	int contor = 0;
	init_new_w_rev_cards(new_deck, card, contor);
	free_that_cards(deck);
	deck->head_or_v = new_deck->head_or_v;
	new_deck = free_the_actual_deck(new_deck);
	printf("The deck %d was successfully reversed.\n", deck_index);
}