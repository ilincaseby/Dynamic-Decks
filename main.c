#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bible.h"

int main(){
	//declare a decks_dlist and initialise it
	//b_list strands for beginning list
	decks_dlist *b_list;
	b_list = allocate_1st_list_and_init(b_list);

	//declare two char pointers to work
	//with on command
	char *command, *buffer;

	//allocate size to those pointers
	char *(*command_allocate_size)(char *) = &allocate_for_strings;
	command = (*command_allocate_size)(command);
	buffer = (*command_allocate_size)(buffer);

	int index;
	
	//begin the program using while when the
	//condition is always true and break it
	//when it needs to

	while (1 != 0) {
		/*Read the command and check it*/
		scanf("%s", command);
		remove_basic_newline(command);

		/*Depends on the command I will 
		execute different things*/
		if (strcmp(command, "ADD_DECK") == 0) {
			//printf("okay\n");
			scanf("%s", command);
			int no_cards = atoi(command);
			//printf("%d\n", no_cards);
			adding_last_to_list(b_list, no_cards, command);
		} else if (strcmp(command, "DEL_DECK") == 0) {
			go_delete_deck(b_list);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			int deck_index, card_index;
			scanf("%d", &deck_index);
			scanf("%d", &card_index);
			go_delete_card(b_list, deck_index, card_index);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			int deck_index, no_cards;
			scanf("%d %d", &deck_index, &no_cards);
			AddCardsToDeck(b_list, deck_index, no_cards);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			display_how_many(b_list);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			disp_no_cards(b_list);
		} else if (strcmp(command, "SHUFFLE_DECK") == 0) {
			shuffle_cards(b_list);
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			merge_it(b_list);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			split_it(b_list);
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			get_rev_deck(b_list);
		}
	}

}