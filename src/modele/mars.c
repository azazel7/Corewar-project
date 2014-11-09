#include "mars.h"

void add_warrior(struct mars *mars, struct instruction *list_instruction, unsigned short size_instruction)
{
	unsigned short new_index, compteur = 0;
	do
	{
		if(compteur > 15)		//Not sure if all the position are checked
		{
			if((new_index = find_good_index(mars, new_index, size_instruction)) == mars->size_memory)
			{
				return;
			}
			else
			{
				break;
			}
		}
		new_index = rand() % mars->size_memory;
		compteur++;
	} while(check_index_warrior(mars, size_instruction, new_index));
	add_warrior_index(mars, list_instruction, size_instruction, new_index);
}

void add_warrior_index(struct mars *mars, struct instruction *list_instruction, unsigned short size_instruction, unsigned short index)
{
	if(list_instruction == NULL || size_instruction == 0 || check_index_warrior(mars, size_instruction, index) == 1)
	{
		return;
	}
	//create a warrior and realloc a_warrior
	mars->size_a_warrior++;
	mars->a_warrior = realloc(mars->a_warrior, mars->size_a_warrior*sizeof(struct warrior));
	//puts the warrion in memory
	struct instruction *current_instruction = NULL;
	for(int i = 0; i < size_instruction; i++)
	{
		current_instruction = get_instruction_pointer(mars, index + i);
		*current_instruction = list_instruction[i];
		current_instruction->idx_last_warrior = mars->size_a_warrior;
	}
	//create warrior
	struct warrior *current_warrior = &(mars->a_warrior[mars->size_a_warrior - 1]);
	current_warrior->position_thread = malloc(sizeof(unsigned short));
	current_warrior->position_thread[0] = index;
	current_warrior->size_position_thread = 1;
	current_warrior->next_thread = 0;
	current_warrior->size_warrior = size_instruction;
}

char check_index_warrior(struct mars *mars, unsigned short size_instruction, unsigned short index)
{
	unsigned short size_all_warrior = size_of_all_warrior(mars);
	if(size_instruction + size_all_warrior >= mars->size_memory)
	{
		return 1;
	}
	if(index_is_in_warrior(mars, index, size_instruction))
	{
		return 1;
	}
	return 0;
}

void spend_cycle(struct mars *mars)
{
	for(int i = 0; i < mars->size_a_warrior; i++)
	{
		if(warrior_is_dead(&(mars->a_warrior[i])) == 0)
		{
			execute_warrior(mars, &(mars->a_warrior[i]));
		}
	}
	mars->current_cycle++;
}

void execute_warrior(struct mars *mars, struct warrior *current_warrior)
{
	if(current_warrior->next_thread < 0)
	{
		return;
	}
	unsigned short index_instruction = current_warrior->position_thread[current_warrior->next_thread];
	current_warrior->has_change_current_thread = 0;
	execute_instruction(mars, index_instruction, current_warrior);
	mark_memory_by_warrior(mars, current_warrior);
	//if the index of instruction has change, that's because something modify it lik a JMP instruction
	if(current_warrior->has_change_current_thread == 0 && current_warrior->next_thread < current_warrior->size_position_thread)
	{
		current_warrior->position_thread[current_warrior->next_thread]++;
		current_warrior->position_thread[current_warrior->next_thread] = current_warrior->position_thread[current_warrior->next_thread]%mars->size_memory;
	}
	turn_thread_warrior(current_warrior);
}

void turn_thread_warrior(struct warrior *warrior)
{
	if(warrior->size_position_thread > 0)
	{
		warrior->next_thread = (warrior->next_thread + 1) % warrior->size_position_thread;
	}
}

void execute_instruction(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior)
{
	struct instruction instruction = get_instruction(mars, index_instruction);
	switch (instruction.action)
	{
	case DAT:
		execute_DAT(mars, index_instruction, current_warrior, instruction);
		break;
	case MOV:
		execute_MOV(mars, index_instruction, current_warrior, instruction);
		break;
	case ADD:
		execute_ADD(mars, index_instruction, current_warrior, instruction);
		break;
	case SUB:
		execute_SUB(mars, index_instruction, current_warrior, instruction);
		break;
	case MUL:
		execute_MUL(mars, index_instruction, current_warrior, instruction);
		break;
	case DIV:
		execute_DIV(mars, index_instruction, current_warrior, instruction);
		break;
	case MOD:
		execute_MOD(mars, index_instruction, current_warrior, instruction);
		break;
	case JMP:
		execute_JMP(mars, index_instruction, current_warrior, instruction);
		break;
	case JMZ:
		execute_JMZ(mars, index_instruction, current_warrior, instruction);
		break;
	case JMN:
		execute_JMN(mars, index_instruction, current_warrior, instruction);
		break;
	case DJN:
		execute_DJN(mars, index_instruction, current_warrior, instruction);
		break;
	case SPL:
		execute_SPL(mars, index_instruction, current_warrior, instruction);
		break;
	case CMP:
		execute_CMP(mars, index_instruction, current_warrior, instruction);
		break;
	case SEQ:
		execute_SEQ(mars, index_instruction, current_warrior, instruction);
		break;
	case SNE:
		execute_SNE(mars, index_instruction, current_warrior, instruction);
		break;
	case SLT:
		execute_SLT(mars, index_instruction, current_warrior, instruction);
		break;
	case POW:
		execute_POW(mars, index_instruction, current_warrior, instruction);
		break;
	case LDP:
		break;
	case STP:
		break;
	case NOP:
		break;
	}
}

int warrior_is_dead(struct warrior *warrior)
{
	//If it doesn't have a thread anymore
	return (warrior->size_position_thread == 0);
}

struct instruction get_instruction(struct mars *mars, unsigned short index_instruction)
{
	return *get_instruction_pointer(mars, index_instruction);
}

struct instruction *get_instruction_pointer(struct mars *mars, unsigned short index_instruction)
{
	index_instruction = index_instruction % mars->size_memory;
	return &(mars->memory[index_instruction]);
}
void kill_current_thread(struct warrior *warrior)
{
	for(int i = warrior->next_thread; i <= warrior->size_position_thread - 2; i++)
	{
		warrior->position_thread[i] = warrior->position_thread[i + 1];
	}
	warrior->size_position_thread--;
	if(warrior->size_position_thread > 0)
	{
		warrior->position_thread = realloc(warrior->position_thread, sizeof(unsigned short)*warrior->size_position_thread);
	}
	else if(warrior->size_position_thread == 0)
	{
		free(warrior->position_thread);
	}
}

char check_zero(unsigned char modifier, struct instruction instruction)
{
	switch (modifier)
	{
	case MODIFIER_AB:
	case MODIFIER_A:
		if(instruction.field_a == 0)
		{
			return 1;
		}
		break;
	case MODIFIER_BA:
	case MODIFIER_B:
		if(instruction.field_b == 0)
		{
			return 1;
		}
		break;
	case MODIFIER_F:
	case MODIFIER_X:
		if(instruction.field_a == 0 || instruction.field_b == 0)
		{
			return 1;
		}
		break;
	};
	return 0;
}

unsigned short get_referenced_instruction_indirect(struct mars *mars, unsigned short index_instruction, int field_instruction, char addressing)
{
	//MOV 0, @1
	//DAT 0, -1
	// get instruction at (index_instruction + field_instruction);
	struct instruction *instruct = get_instruction_pointer(mars, index_instruction + field_instruction);
	//switch sur le type d'adressage
	int value_field = 0, tmp;
	switch (addressing)
	{
	case ADDR_INDIRECT_A:
		value_field = instruct->field_a;
		break;
	case ADDR_INDIRECT_A_PREDECREMENT:
		instruct->field_a--;
		instruct->idx_last_warrior = -1;
		value_field = instruct->field_a;
		break;
	case ADDR_INDIRECT_A_POSTINCREMENT:
		value_field = instruct->field_a;
		instruct->field_a++;
		instruct->idx_last_warrior = -1;
		break;
	case ADDR_INDIRECT_B:
		value_field = instruct->field_b;
		break;
	case ADDR_INDIRECT_B_PREDECREMENT:
		instruct->field_b--;
		instruct->idx_last_warrior = -1;
		value_field = instruct->field_b;
		break;
	case ADDR_INDIRECT_B_POSTINCREMENT:
		value_field = instruct->field_b;
		instruct->field_b++;
		instruct->idx_last_warrior = -1;
		break;
	}
	tmp = value_field + field_instruction;
	if(index_instruction < abs(tmp) && tmp < 0)
	{
		return mars->size_memory + tmp + index_instruction; 
	}
	return index_instruction + tmp;
}

unsigned short get_referenced_instruction(struct mars *mars, unsigned short index_instruction, struct instruction instruction, char field)
{
	unsigned short index_referenced_instruction = 0;
	int field_instruction;
	unsigned char addressing;
	if(field == FIELD_A)
	{
		field_instruction = instruction.field_a;
		addressing = instruction.addressing_a;
	}
	else
	{
		field_instruction = instruction.field_b;
		addressing = instruction.addressing_b;
	}
	if(addressing == ADDR_DIRECT)
	{
		if(index_instruction < abs(field_instruction) && field_instruction < 0)
		{
			index_referenced_instruction = mars->size_memory + (index_instruction + field_instruction);
		}
		else
		{
			index_referenced_instruction = index_instruction + field_instruction;
		}
	}
	else if(addressing != ADDR_IMMEDIATE)
	{
		index_referenced_instruction = get_referenced_instruction_indirect(mars, index_instruction, field_instruction, addressing);
	}
	return index_referenced_instruction;
}


unsigned short size_of_all_warrior(struct mars *mars)
{
	unsigned short value = 0;
	for(int i = 0; i < mars->size_a_warrior; i++)
	{
		value += mars->a_warrior[i].size_warrior;
	}
	return value;
}

char index_is_in_warrior(struct mars *mars, unsigned short index_begin, unsigned short size)
{
	unsigned short begin, end, index_end = index_begin + size - 1;
	for(int i = 0; i < mars->size_a_warrior; i++)
	{
		if(mars->a_warrior[i].size_position_thread != 0)
		{
			begin = mars->a_warrior[i].position_thread[0];
			end = begin + mars->a_warrior[i].size_warrior - 1;
			if(!((begin > index_end || end < index_begin) && ((index_end >= mars->size_memory && index_end % mars->size_memory < begin) || index_end < mars->size_memory)))
			{
				return 1;
			}
		}
	}
	return 0;
}

int find_good_index(struct mars *mars, unsigned short first_index, unsigned short size)
{
	for(int i = 0; i < mars->size_memory; i++)
	{
		if(!index_is_in_warrior(mars, (first_index + i) % mars->size_memory, size))
		{
			return first_index + i;
		}
	}
	return mars->size_memory;	//Index size_memory doesn't exist, the last index is size_memory - 1  
}

void mark_memory_by_warrior(struct mars* mars, struct warrior* warrior)
{
	struct warrior* base = mars->a_warrior;
	int idx_last_warrior = (warrior - base) + 1;
	for(int i = 0; i < mars->size_memory; i++)
	{
		if(mars->memory[i].idx_last_warrior < 0)
		{
			mars->memory[i].idx_last_warrior = idx_last_warrior;
		}
	}
}
