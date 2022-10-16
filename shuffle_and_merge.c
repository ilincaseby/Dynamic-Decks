#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

/*Return the middle of a deck's size*/
int
get_half(dll_node_t *deck)
{
    int *sizey = (int *) deck->size_or_sy;
    int half = (*sizey) / 2;
    return half;
}

/*Being given a deck and a value, invert the cards,
all of cards until where_half go to last places and the cards
after become the first ones*/
void
actual_shuffle(dll_node_t *deck, int where_half)
{
    dll_node_t *middle_card = NULL;
    middle_card = (dll_node_t *) deck->head_or_v;
    for (int i = 0; i < where_half - 1; ++i)
        middle_card = middle_card->next;
    
    dll_node_t *node_to_tie_the_head_of_deck = middle_card->next;
    dll_node_t *last_card = middle_card->next;
    while (last_card->next)
        last_card = last_card->next;
    
    middle_card->next = NULL;
    dll_node_t *firsty = (dll_node_t *) deck->head_or_v;
    last_card->next = firsty;
    firsty->prev = last_card;

    middle_card->next = NULL;
    deck->head_or_v = (void *) node_to_tie_the_head_of_deck;

    /*int *ptr;
    dll_node_t *for_print = (dll_node_t *) deck->head_or_v;
    int *size  = (int *) deck->size_or_sy;
    for (int i = 0; i < (*size); i++) {
        ptr = (int *) for_print->head_or_v;
        printf("%d\n", *ptr);
        for_print = for_print->next;
    } */
}
/*Being given a deck, returns 2 values:
0 - you cannot shuffle the deck
1 - you can shuffle the deck*/
int
can_I_shuffle(dll_node_t *deck)
{
    int *sizey = (int *) deck->size_or_sy;
    if ((*sizey) <= 1)
        return 0;
    return 1;
}

/*Function to announce the success*/
void
print_the_magic(int deck_index)
{
    printf("The deck %d was successfully shuffled.\n", deck_index);
}

/*Give me the list, I will ask for an index and I will
shuffle the cards for u master!*/
void
shuffle_cards(decks_dlist *b_list)
{
    int deck_index;
    scanf("%d", &deck_index);
    dll_node_t *deck = NULL;
    deck = get_the_deck(b_list, deck, deck_index);

    int verify = can_I_shuffle(deck);
    if (!verify) {
        print_the_magic(deck_index);
        return ;
    }

    int where_half = get_half(deck);
    actual_shuffle(deck, where_half);
    print_the_magic(deck_index);
}

/*Returns the pointer of the empty deck, if
both are initied with cards it returns NULL*/
dll_node_t *
is_anyone_empty_inside(dll_node_t *deck1, dll_node_t *deck2)
{
    int *size1 = (int *) deck1->size_or_sy;
    int *size2 = (int *) deck2->size_or_sy;
    if (*size1 == 0)
        return deck1;
    if (*size2 == 0)
        return deck2;
    return NULL;
}

/*Returns a const value which represents
the sum of decks sizes*/
const int
what_is_the_size_combined(dll_node_t *deck1, dll_node_t *deck2)
{
    int *d1 = (int *) deck1->size_or_sy;
    int *d2 = (int *) deck2->size_or_sy;
    return (*d1 + *d2);
}

/*Merge deck1 and deck2 into merged_deck*/
dll_node_t *
actual_merging_proccess(dll_node_t *merged_deck, dll_node_t *deck1, dll_node_t *deck2)
{
    const int total_size_to_be = what_is_the_size_combined(deck1, deck2);
    int contor = 0;
    merged_deck = allocate_deck(merged_deck);
    dll_node_t *card_from1 = (dll_node_t *) deck1->head_or_v;
    dll_node_t *card_from2 = (dll_node_t *) deck2->head_or_v;

    while (contor != total_size_to_be) {
        if (card_from1 != NULL && card_from2 != NULL) {
            if (contor == 0) {
                add_to_start_card(merged_deck, card_from1->head_or_v, card_from1->size_or_sy);
                card_from1 = card_from1->next;
            } else if (contor % 2 == 0 && contor != 0) {
                add_to_last_card(merged_deck, card_from1->head_or_v, card_from1->size_or_sy);
                card_from1 = card_from1->next;
            } else if (contor % 2 != 0) {
                add_to_last_card(merged_deck, card_from2->head_or_v, card_from2->size_or_sy);
                card_from2 = card_from2->next;
            }
        } else if (!card_from1) {
            add_to_last_card(merged_deck, card_from2->head_or_v, card_from2->size_or_sy);
            card_from2 = card_from2->next;
        } else if (!card_from2) {
            add_to_last_card(merged_deck, card_from1->head_or_v, card_from1->size_or_sy);
            card_from1 = card_from1->next;
        }

        contor++;
    }

    const void *src_number = (void *) (&total_size_to_be);
    memcpy(merged_deck->size_or_sy, src_number, sizeof(int));

    return merged_deck;
}

/*Being given a list of decks, it will
require two index, then the decks will be merged*/
void 
merge_it(decks_dlist *b_list)
{
	int deck_index1, deck_index2;
	scanf("%d %d", &deck_index1, &deck_index2);
    dll_node_t *deck1 = NULL;
    dll_node_t *deck2 = NULL;
    deck1 = ret_the_deck_and_extr_from_list(b_list, deck_index1, deck1);
    if (deck_index1 > deck_index2)
        deck2 = ret_the_deck_and_extr_from_list(b_list, deck_index2, deck2);
    if (deck_index1 < deck_index2)
        deck2 = ret_the_deck_and_extr_from_list(b_list, (deck_index2 - 1), deck2);
    dll_node_t *merged_deck = is_anyone_empty_inside(deck1, deck2);
    if (merged_deck) {
        if (b_list->size >= 1) {
            add_to_inited_l(merged_deck, b_list);
            b_list->size++;
        }

        if (b_list->size == 0) {
            b_list->head =  merged_deck;
            b_list->size++;
        }
        
        printf("The deck %d and the deck %d were successfully merged.\n", deck_index1, deck_index2);
        return ;
    }
    merged_deck = actual_merging_proccess(merged_deck, deck1, deck2);
    //to insert the deck
    //to free
    if (b_list->size >= 1) {
        add_to_inited_l(merged_deck, b_list);
        b_list->size++;
    }

    if (b_list->size == 0) {
        b_list->head =  merged_deck;
        b_list->size++;
    }

    free_that_cards(deck1);
    free_that_cards(deck2);
    deck1 = free_the_actual_deck(deck1);
    deck2 = free_the_actual_deck(deck2);
    
    printf("The deck %d and the deck %d were successfully merged.\n", deck_index1, deck_index2);
}