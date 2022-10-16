#pragma once

#define bytesno sizeof(int)
#define command_size 32

typedef unsigned int u_i;

/*Define a structures which will be used
as a node for decks and cards too.
P.S. : head_or_v is a pointer which is used
for a head or a value (deck or card) &&
size_or_sy means size or a symbol*/

typedef struct dll_node_t{
	void *head_or_v;
	void *size_or_sy;
	struct dll_node_t *prev, *next;
} dll_node_t;

/*The structure decks_dlist is the
structure that everything begins with.
Using that we can go through decks*/

typedef struct decks_dlist{
	u_i size;
	dll_node_t *head;
} decks_dlist;


char *allocate_for_strings(char *s);
decks_dlist *allocate_1st_list_and_init(decks_dlist *st_list);
void remove_basic_newline(char *s);
void adding_last_to_list(decks_dlist *b_list, int no_cards, char *buffer);
void init_the_deck(dll_node_t *deck, int no_c, char *buffer);
dll_node_t *allocate_deck(dll_node_t *deck);
void add_to_inited_l(dll_node_t *deck, decks_dlist *b_list);
void add_to_last_card(dll_node_t *deck, const void *value, const void *symbol);
void go_delete_deck(decks_dlist *b_list);
dll_node_t *ret_the_deck_and_extr_from_list(decks_dlist *b_list, int deck_index, dll_node_t *curr_deck);
void add_to_start_card(dll_node_t *deck, const void *value, const void *symbol);
void free_that_cards(dll_node_t *deck);
dll_node_t *free_the_actual_deck(dll_node_t *deck);
void go_delete_card(decks_dlist *b_list, int deck_index, int card_index);
dll_node_t *desired_deck(decks_dlist *b_list,dll_node_t *deck, int deck_index);
dll_node_t *card_to_be_removed_and_extract(dll_node_t *deck, int card_index);
dll_node_t *bye_bye_card(dll_node_t *card);
void AddCardsToDeck(decks_dlist *b_list, int deck_index, int no_cards);
dll_node_t *get_the_deck(decks_dlist *b_list, dll_node_t *deck, int deck_index);
void AddToLast(dll_node_t *deck, int no_cards);
void display_how_many(decks_dlist *b_list);
void disp_no_cards(decks_dlist *b_list);
void shuffle_cards(decks_dlist *b_list);
void print_the_magic(int deck_index);
int can_I_shuffle(dll_node_t *deck);
void actual_shuffle(dll_node_t *deck, int where_half);
int get_half(dll_node_t *deck);
void merge_it(decks_dlist *b_list);
dll_node_t *actual_merging_proccess(dll_node_t *merged_deck, dll_node_t *deck1, dll_node_t *deck2);
const int what_is_the_size_combined(dll_node_t *deck1, dll_node_t *deck2);
dll_node_t *is_anyone_empty_inside(dll_node_t *deck1, dll_node_t *deck2);
void split_it(decks_dlist *b_list);
void address_cards_into_new(dll_node_t *new_deck, dll_node_t *deck, int split_index);
dll_node_t *get_last_card(dll_node_t *deck, dll_node_t *card);
void init_new_w_rev_cards(dll_node_t *new_deck, dll_node_t *card, int contor);
void get_rev_deck(decks_dlist *b_list);