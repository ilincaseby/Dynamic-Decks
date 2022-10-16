#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Function to return a pointer to the node which is the
desired deck to remove and at the same time the nodes will
be the same without that deck
WARNING! It's your job to free the deck*/
dll_node_t *
ret_the_deck_and_extr_from_list(decks_dlist *b_list, int deck_index, dll_node_t *curr_deck)
{
    curr_deck = b_list->head;

    for (int i = 0; i < deck_index; ++i)
        curr_deck = curr_deck->next;
    
    int verify_for_cond = (int) b_list->size;
    if (deck_index > 0 && deck_index < (verify_for_cond - 1)) {
        dll_node_t *nxt, *prv;
        prv = curr_deck->prev;
        nxt = curr_deck->next;
        prv->next = curr_deck->next;
        nxt->prev = curr_deck->prev;
    }

    if (deck_index == (verify_for_cond - 1) && deck_index > 0) {
        dll_node_t *prv;
        prv = curr_deck->prev;
        prv->next = NULL;
    }

    if (deck_index == 0) {
        dll_node_t *nxt;
        nxt = curr_deck->next;
        if (nxt)
            nxt->prev = NULL;
        b_list->head = nxt;
    }

    b_list->size--;

    return curr_deck;
}

/*Free all the cards contained by deck*/
void
free_that_cards(dll_node_t *deck)
{
    int *size = (int *) deck->size_or_sy;
	// printf("%d\n", *size);
    if (*size == 0)
        return ;
    dll_node_t *card = (dll_node_t *) deck->head_or_v;
    //discovered a special case (is no card there)
    //and that's why I need that if
    
    while (card->next != NULL)
		card = card->next;

	dll_node_t *aux = NULL;

	while (card != NULL) {
        aux = card->prev;

        free(card->head_or_v);
        free(card->size_or_sy);
        free(card);

        card = aux;
    }
    
}

/*Return NULL after the deck is freed*/
dll_node_t *
free_the_actual_deck(dll_node_t *deck)
{
    free(deck->size_or_sy);
    free(deck);

    return NULL;
}

/*Scan an index and remove the deck with the specific
index from the list*/
void
go_delete_deck(decks_dlist *b_list)
{
    int deck_index;
    scanf("%d", &deck_index);

    dll_node_t *curr_deck = NULL;
    curr_deck = ret_the_deck_and_extr_from_list(b_list, deck_index, curr_deck);

    free_that_cards(curr_deck);
    curr_deck = free_the_actual_deck(curr_deck);

    printf("The deck %d was successfully deleted.\n", deck_index);
}

/*Return a pointer to the deck which is indexed
with deck_index*/
dll_node_t *
desired_deck(decks_dlist *b_list ,dll_node_t *deck, int deck_index)
{
	deck = b_list->head;
	//printf("%p\n", deck);
	if (deck_index > 0) {
		for (int i = 0; i < deck_index; ++i) {
			deck = deck->next;
		}
	}
	//printf("%p\n", deck);
	return deck;
}

/*Return a pointer to the card indexed and
extracting it from the list of cards
WARNING! It's your job to free the card*/
dll_node_t *
card_to_be_removed_and_extract(dll_node_t *deck, int card_index)
{
	dll_node_t *card = (dll_node_t *) deck->head_or_v;
	if (card_index > 0) {
		for (int i = 0; i < card_index; ++i)
			card = card->next;
	}
	
	int verify_for_cond = *((int *) deck->size_or_sy);
	if (card_index > 0 && card_index < (verify_for_cond - 1)) {
		dll_node_t *nxt, *prv;
		prv = card->prev;
		nxt = card->next;
		prv->next = card->next;
		nxt->prev = card->prev;
	}

	if (card_index == (verify_for_cond - 1) && card_index > 0) {
		dll_node_t *prv;
		prv = card->prev;
		prv->next = NULL;
	}

	if (card_index == 0) {
		dll_node_t *nxt;
		nxt = card->next;
		if (nxt)
			nxt->prev = NULL;
		deck->head_or_v = (void *) nxt;
	}

	(*((int *) deck->size_or_sy))--;
	return card;
}

/*Return NULL pointer after card is freed*/
dll_node_t *
bye_bye_card(dll_node_t *card)
{
	free(card->head_or_v);
	free(card->size_or_sy);
	free(card);
	
	return NULL;
}

/*"Mother" function which do the magic thing to delete
card with index card_index from deck indexed at deck_index*/
void
go_delete_card(decks_dlist *b_list, int deck_index, int card_index)
{
	//printf("%d\n%d\n", deck_index, card_index);
	dll_node_t *deck = NULL;
	deck = desired_deck(b_list, deck, deck_index);
	dll_node_t *card = card_to_be_removed_and_extract(deck, card_index);
	card = bye_bye_card(card);

	int condition_to_delete_entire_deck = *((int *) deck->size_or_sy);
	//printf("%d\n", condition_to_delete_entire_deck);
	if (condition_to_delete_entire_deck == 0) {
		dll_node_t *rmy_deck = NULL;
		rmy_deck = ret_the_deck_and_extr_from_list(b_list, deck_index, rmy_deck);
		rmy_deck = free_the_actual_deck(rmy_deck);
	}

	printf("The card was successfully deleted from deck %d.\n", deck_index);
}
