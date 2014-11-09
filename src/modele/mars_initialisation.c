#include "mars_initialisation.h"

struct mars* create_mars(unsigned short size_memory, unsigned int max_cycle, struct instruction* initial_instruction)
{
	struct mars* mars = NULL;
	mars = malloc(sizeof(struct mars));
	if(mars == NULL)
	{
		return NULL;
	}
	mars->memory = malloc(sizeof(struct instruction) * size_memory);	
	if(mars->memory == NULL)
	{
		free(mars);
		return NULL;
	}
	mars->max_cycle = max_cycle;
	mars->current_cycle = 0;		
	mars->size_memory = size_memory;
	mars->size_a_warrior = 0;
	mars->a_warrior = NULL;
	if(initial_instruction != NULL)
	{
		fill_memory(mars->memory, mars->size_memory, initial_instruction);
	}
	else
	{
		randomize_memory(mars);
	}
	return mars;
}

void destroy_mars(struct mars* mars)
{
	empty_mars(mars);
	free(mars);
}

void empty_mars(struct mars* mars)
{
	if(mars->size_memory > 0)
	{
		free(mars->memory);
		mars->memory = NULL;
		mars->size_memory = 0;
	}
	if(mars->size_a_warrior > 0)
	{
		struct warrior* warrior = NULL;
		for(int i = 0; i < mars->size_a_warrior; i++)
		{
			warrior = &(mars->a_warrior[i]); 
			empty_warrior(warrior);
		}
		free(mars->a_warrior);
		mars->a_warrior = NULL;
		mars->size_a_warrior = 0;
	}
}

void empty_warrior(struct warrior* warrior)
{
	if(warrior->size_position_thread > 0)
	{
		free(warrior->position_thread);
		warrior->position_thread = NULL;
		warrior->size_position_thread = 0;
	}
}

struct instruction randomize_instruction()
{
	struct instruction value;
	value.action = rand()%20;
	value.modifier_action = (rand()%7) + 1;
	value.addressing_a = rand()%8;
	value.field_a = rand()%100;
	value.addressing_b = rand()%8;
	value.field_b = rand()%100;
	value.idx_last_warrior = 0;
	return value;
}

void randomize_memory(struct mars* mars)
{
	for(int i = 0; i < mars->size_memory; i++)
	{
		mars->memory[i] = randomize_instruction();
	}	
}

void fill_memory(struct instruction* memory, unsigned short size_memory, struct instruction* initial_instruction)
{
	for(int i = 0; i < size_memory; i++)
	{
		memory[i] = *initial_instruction;
		memory[i].idx_last_warrior = 0;
	}
}


