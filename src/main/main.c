#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include "parseFile.h"
#include "mars.h"
#include "mars_initialisation.h"
#include "vue.h"


void test_function(void)
{
	struct instruction instruction;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_b = 1;

	struct mars *mars = create_mars(10, 10, &instruction);

	struct instruction list_instruction[3];
	list_instruction[0].action = JMN;
	list_instruction[0].modifier_action = MODIFIER_A;
	list_instruction[0].addressing_a = ADDR_DIRECT;
	list_instruction[0].field_a = -1;
	list_instruction[0].addressing_b = ADDR_DIRECT;
	list_instruction[0].field_b = 2;
	list_instruction[1].action = DAT;
	list_instruction[1].addressing_a = ADDR_DIRECT;
	list_instruction[1].field_a = 1;
	list_instruction[1].addressing_b = ADDR_DIRECT;
	list_instruction[1].field_b = 1;
	list_instruction[2].action = MOV;
	list_instruction[2].modifier_action = MODIFIER_I;
	list_instruction[2].addressing_a = ADDR_DIRECT;
	list_instruction[2].field_a = 1;
	list_instruction[2].addressing_b = ADDR_DIRECT;
	list_instruction[2].field_b = 1;

	add_warrior(mars, list_instruction, 3);
	init_view(mars);
	destroy_mars(mars);
}

void test_parse(void)
{
	initscr();
	unsigned short size;
	struct instruction *tab = NULL;
	tab = parse_file("test.narval", &size);
	for(int i = 0; i < size; i++)
	{
		print_instrction(tab[i]);
	}
	free(tab);
	getch();
	endwin();
}

int main(int argc, char **argv)
{
	printf("[i] Begin\n");
	/*
	 * test_function();
	 */
	int opth = 0;
	struct instruction initial_instruction;
	struct instruction *a_instruction = NULL;
	unsigned short size_a_instruction = 0;
	unsigned int max_cycle = 8000;
	unsigned short max_memory = 6000;
	unsigned short size_memory = 400;
	char **a_file = NULL;
	char init_instruction = 0;
	unsigned short size_a_file = 0;
	srand(time(NULL));
	while((opth = getopt(argc, argv, "hp:c:i:m:")) != -1)
	{
		switch (opth)
		{
		case 'h':
			printf("-h\tPrint help\n");
			printf("-p <file name>\tLoad this file as processus for corewar, use '-p' for each warrior\n");
			printf("-c <cycle>\tChange the number of cycle. (default : 8000)\n");
			printf("-i <instruction>\tSet the init instruction of memory (default: randomize memory)\n");
			printf("-m <size>\tSet the size of the memory (default : 400, max : 6000)\n");
			return -1;
			break;
		case 'p':
			//Add to an array
			size_a_file++;
			a_file = realloc(a_file, size_a_file * sizeof(char *));
			a_file[size_a_file - 1] = malloc(sizeof(char) * (strlen(optarg) + 1));
			strncpy(a_file[size_a_file - 1], optarg, strlen(optarg) + 1);
			a_file[size_a_file - 1][strlen(optarg)] = 0;
			break;
		case 'c':
			max_cycle = atoi(optarg);
			break;
		case 'i':
			initial_instruction = parse_line(optarg);
			if(initial_instruction.action != ERROR_ACTION)
			{
				init_instruction = 1;
			}
			break;
		case 'm':
			size_memory = atoi(optarg);
			if(size_memory >= max_memory)
			  { size_memory = max_memory;}
			break;
		}
	}
	struct mars *mars = NULL;
	if(init_instruction)
	{
		mars = create_mars(size_memory, max_cycle, &initial_instruction);
	}
	else
	{
		mars = create_mars(size_memory, max_cycle, NULL);
	}
	//Parse all warrior 
	for(int i = 0; i < size_a_file; i++)
	{
		printf("[i] Parse %s\n", a_file[i]);
		a_instruction = parse_file(a_file[i], &size_a_instruction);
		if(a_instruction != NULL)
		{
			add_warrior(mars, a_instruction, size_a_instruction);
			free(a_instruction);
		}
		else
		{
			printf("[-] Error parsing %s\n", a_file[i]);
		}
	}
	//Free file of warrior
	if(size_a_file > 0)
	{
		for(int i = 0; i < size_a_file; i++)
		{
			free(a_file[i]);
		}
		free(a_file);
	}
	//Run view
	if(mars->size_a_warrior > 0)
	{
		init_view(mars);
	}
	else
	{
		printf("[-]You have to set at least one warrior\n");
	}
	//Finish
	destroy_mars(mars);
	mars = NULL;
	printf("[i] End\n");
	return 0;
}
