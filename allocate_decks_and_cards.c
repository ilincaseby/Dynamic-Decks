#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Return a pointer to a 1st list
which is initialised with head NULL
and the size is 0*/
decks_dlist *
allocate_1st_list_and_init(decks_dlist *st_list)
{
	//allocate memory and return the pointer
	st_list = malloc(sizeof(*st_list));
	if(!st_list) {
		fprintf(stderr, "Malloc failed\n");
		return NULL;
	}

	st_list->head = NULL;
	st_list->size = 0;

	return st_list;
}

/*Init a deck list*/
dll_node_t *
allocate_deck(dll_node_t *deck)
{
	deck = malloc(sizeof(*deck));
	if (!deck) {
		fprintf(stderr, "Malloc failed\n");
		return NULL;
	}

	deck->next = NULL;
	deck->prev = NULL;

	deck->head_or_v = NULL;

	deck->size_or_sy = malloc(sizeof(int));
	if (!deck->size_or_sy) {
		fprintf(stderr, "Malloc failed");
		return NULL;
	}
	int *int_ptr = (int *) deck->size_or_sy;
	(*int_ptr) = 0;

	return deck;
}

/*Put a deck at the beginning of a list when
the list is not empty
WARNING: It's ur job to increase list's size*/
void
add_to_inited_l(dll_node_t *deck, decks_dlist *b_list)
{
	dll_node_t *aux = b_list->head;
	while ((aux->next)) 
		aux = aux->next;
	aux->next = deck;
	deck->prev = aux;
}

/*This function practically put a card to the
beginning of a deck*/
void
add_to_start_card(dll_node_t *deck, const void *value, const void *symbol)
{
	dll_node_t *card = malloc(sizeof(*card));
	if (!card) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}

	card->next = NULL;
	card->prev = NULL;

	card->head_or_v = malloc(sizeof(int));
	if (!(card->head_or_v)) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}
	card->size_or_sy = malloc(command_size);
	if (!(card->size_or_sy)) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}

	memset(card->size_or_sy, 0, command_size);
	memcpy(card->head_or_v, value, sizeof(int));
	memcpy(card->size_or_sy, symbol, command_size);

	deck->head_or_v = (void *) card;
}

/*If the deck has at least one card in it
I add the next one to the last*/
void
add_to_last_card(dll_node_t *deck, const void *value, const void *symbol)
{
	dll_node_t *card = malloc(sizeof(*card));
	if (!card) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}
	card->next = NULL;

	card->head_or_v = malloc(sizeof(int));
	if (!(card->head_or_v)) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}
	card->size_or_sy = malloc(command_size);
	if (!(card->size_or_sy)) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}

	memset(card->size_or_sy, 0, command_size);
	memcpy(card->head_or_v, value, sizeof(int));
	memcpy(card->size_or_sy, symbol, command_size);

	dll_node_t *aux = (dll_node_t *) deck->head_or_v;
	while ((aux->next)) {
		aux = aux->next;
	}
	aux->next = card;
	card->prev = aux;
}

/*This function has the role to add cards to
the current deck*/
void
init_the_deck(dll_node_t *deck, int no_c, char *command)
{
	//printf("OKAY\n");
	int *size;
	int value;
	char *symbol = malloc(command_size);
	if (!symbol) {
		fprintf(stderr, "Malloc failed\n");
		return ;
	}
	for (int i = 0; i < no_c; ++i) {
		size = (int *) deck->size_or_sy;
		scanf("%s", command);
		remove_basic_newline(command);
		value = atoi(command);
		scanf("%s", command);
		remove_basic_newline(command);
		strcpy(symbol, command);

		if ((*size) >= 1) {
			add_to_last_card(deck, (void *) &value, (void *) symbol);
			(*size)++;
		}
		
		if ((*size) == 0) {
			add_to_start_card(deck, (void *) &value, (void *) symbol);
			(*size)++;
			continue;
		}
		
	}
	free(symbol);
}

/*The principal purpose of this function
is to go to the last deck and add another one*/
void
adding_last_to_list(decks_dlist *b_list, int no_c, char *command)
{
	//printf("okay\n");
	dll_node_t *deck = allocate_deck(deck);
	
	if (b_list->size >= 1) {
		add_to_inited_l(deck, b_list);
		b_list->size++;
	}
	
	if (b_list->size == 0) {
		b_list->head = deck;
		b_list->size++;
	}
	
	init_the_deck(deck, no_c, command);

	printf("The deck was successfully created with %d cards.\n", no_c);
}