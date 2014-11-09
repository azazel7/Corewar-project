#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "mars.h"
#include "mars_initialisation.h"

void init_view(struct mars* mars);
void print_instrction(struct instruction instruction);
void print_memory(struct mars* mars, struct instruction* tampon);
void choose_color_letter(unsigned short idx_warrior, int* color, char* letter);
