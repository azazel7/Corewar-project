#ifndef  mars_initialisation_INC
#define  mars_initialisation_INC
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct mars *create_mars(unsigned short size_memory, unsigned int max_cycle, struct instruction *initial_instruction);

void destroy_mars(struct mars *mars);

void empty_mars(struct mars *mars);

void empty_warrior(struct warrior *warrior);

void fill_memory(struct instruction *memory, unsigned short size_memory, struct instruction *initial_instruction);

void randomize_memory(struct mars *mars);

struct instruction randomize_instruction();
#endif
