#include <stdlib.h>
#include <assert.h>
#include "header.h"
#include "mars_initialisation.h"
#include "mars.h"
#include "vue.h"

void test_create_mars(void);
void test_execute_MOV(void);
void test_execute_SPL(void);
void test_execute_DAT(void);
void test_execute_SUB(void);
void test_execute_ADD(void);
void test_execute_JMP(void);
void test_execute_MUL(void);
void test_execute_MOD(void);
void test_execute_DIV(void);
void test_execute_JMZ(void);
void test_execute_DJN(void);
void test_execute_JMN(void);
void test_execute_SNE(void);
void test_execute_SLT(void);
void test_execute_CMP(void);
void test_execute_POW(void);
void test_add_warrior_index(void);
void test_add_warrior(void);
void test_kill_current_thread(void);

int main(int argc, char *argv[])
{
	test_create_mars();
	test_add_warrior_index();
	test_kill_current_thread();
	test_add_warrior();
	test_execute_MOV();
	test_execute_SPL();
	test_execute_DAT();
	test_execute_SUB();
	test_execute_ADD();
	test_execute_JMP();
	test_execute_MUL();
	test_execute_MOD();
	test_execute_DIV();
	test_execute_JMZ();
	test_execute_DJN();
	test_execute_JMN();
	test_execute_SNE();
	test_execute_SLT();
	test_execute_CMP();
	test_execute_POW();

	return EXIT_SUCCESS;
}

void test_create_mars(void)
{
	struct instruction instruction, mem;
	instruction.action = MOV;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.field_a = 5;
	instruction.addressing_b = ADDR_INDIRECT_A;
	instruction.field_b = 7;

	struct mars *mars = create_mars(7, 8, &instruction);
	assert(mars != NULL);
	assert(mars->memory != NULL);
	assert(mars->size_memory == 7);
	assert(mars->max_cycle == 8);
	assert(mars->current_cycle == 0);
	assert(mars->a_warrior == NULL);
	assert(mars->size_a_warrior == 0);
	mem = mars->memory[2];
	assert(mem.action == instruction.action);
	assert(mem.modifier_action == instruction.modifier_action);
	assert(mem.addressing_a == instruction.addressing_a);
	assert(mem.field_a == instruction.field_a);
	assert(mem.addressing_b == instruction.addressing_b);
	assert(mem.field_b == instruction.field_b);
	destroy_mars(mars);
}



void test_execute_MOV(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	//Create the instruction which will fill the memory of mars
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;
	//Create mars with only two case and fill is memory with « DAT.A $0, $0 »
	mars = create_mars(2, 8, &instruction);
	//Create the only instruction of the warrior
	instruction.action = MOV;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 1;
	//I place one warrior with length of one in mars at the first index
	//Because it's just one instruction, I can avoid to create an array and give a pointer to instruction
	add_warrior_index(mars, &instruction, 1, 0);
	assert(mars->memory[1].action == DAT);
	assert(mars->memory[1].modifier_action == MODIFIER_A);
	assert(mars->memory[1].addressing_a == ADDR_DIRECT);
	assert(mars->memory[1].addressing_b == ADDR_DIRECT);
	assert(mars->memory[1].field_a == 0);
	assert(mars->memory[1].field_b == 0);

	execute_MOV(mars, 0, &(mars->a_warrior[0]), instruction);

	assert(mars->memory[1].action == mars->memory[0].action);
	assert(mars->memory[1].action == MOV);
	assert(mars->memory[1].field_a == mars->memory[0].field_a);
	assert(mars->memory[1].field_a == 0);
	assert(mars->memory[1].field_b == mars->memory[0].field_b);
	assert(mars->memory[1].field_b == MOV);
	destroy_mars(mars);
}

void test_execute_SPL(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	//Create the instruction which will fill the memory of mars
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;
	//Create mars with only two case and fill is memory with « DAT.A $0, $0 »
	mars = create_mars(2, 8, &instruction);
	//Create the only instruction of the warrior
	instruction.action = SPL;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;
	//I place one warrior with length of one in mars at the first index
	//Because it's just one instruction, I can avoid to create an array and give a pointer to instruction
	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(warrior->size_position_thread == 1);
	assert(warrior->position_thread[0] == 0);

	execute_SPL(mars, 0, &(mars->a_warrior[0]), instruction);

	assert(warrior->size_position_thread == 2);
	assert(warrior->position_thread[1] == 1);
	destroy_mars(mars);
}

void test_execute_DAT(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	//Create mars with only two case and fill is memory with « DAT.A $0, $0 »
	mars = create_mars(2, 8, NULL);
	//Create the only instruction of the warrior
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;
	//I place one warrior with length of one in mars at the first index
	//Because it's just one instruction, I can avoid to create an array and give a pointer to instruction
	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(warrior->size_position_thread == 1);
	assert(warrior->position_thread[0] == 0);

	execute_DAT(mars, 0, &(mars->a_warrior[0]), instruction);

	assert(warrior->size_position_thread == 0);
	destroy_mars(mars);
}

void test_execute_JMP(void)
{

	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(10, 8, &instruction);

	instruction.action = JMP;
	instruction.modifier_action = MODIFIER_I;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 3;
	instruction.field_b = 1;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);

	execute_JMP(mars, 0, warrior, instruction);


	assert(warrior->position_thread[0] == 3);
	destroy_mars(mars);
}

void test_execute_JMZ(void)
{

	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = JMZ;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 3;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);

	execute_JMZ(mars, 0, warrior, instruction);

	assert(warrior->position_thread[0] == 0);
	mars->memory[1].field_a = 0;
	execute_JMZ(mars, 0, warrior, instruction);

	assert(warrior->position_thread[0] == 3);
	destroy_mars(mars);
}

void test_execute_JMN(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = JMZ;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 3;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);

	execute_JMN(mars, 0, warrior, instruction);

	assert(warrior->position_thread[0] == 0);
	mars->memory[1].field_a = 1;
	execute_JMN(mars, 0, warrior, instruction);

	assert(warrior->position_thread[0] == 3);
	destroy_mars(mars);
}

void test_execute_DJN(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = DJN;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 2;
	instruction.field_b = 3;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	execute_DJN(mars, 0, warrior, instruction);

	assert(mars->memory[0].field_a == 1);
	execute_DJN(mars, 0, warrior, instruction);

	assert(mars->memory[0].field_a == 0);
	assert(warrior->position_thread[0] == 3);
	destroy_mars(mars);
}

void test_execute_ADD(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(2, 8, &instruction);
	instruction.action = ADD;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 1;
	instruction.field_b = 1;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == ADD);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 1);


	execute_ADD(mars, 0, warrior, instruction);

	assert(mars->memory[0].action == ADD);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 0);


	destroy_mars(mars);
}

void test_execute_POW(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(10, 8, &instruction);
	instruction.action = POW;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 2;
	instruction.field_b = 2;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == POW);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 2);


	execute_POW(mars, 0, warrior, mars->memory[0]);

	assert(mars->memory[0].action == POW);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 4);

	execute_POW(mars, 0, warrior, mars->memory[0]);

	assert(mars->memory[0].action == POW);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 6);

	mars->memory[0].modifier_action = MODIFIER_BA;

	execute_POW(mars, 0, warrior, mars->memory[0]);

	assert(mars->memory[0].field_a == 6);
	assert(mars->memory[0].field_b == 6);

	destroy_mars(mars);
}



void test_execute_SUB(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(2, 8, &instruction);
	instruction.action = SUB;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 1;
	instruction.field_b = 2;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == SUB);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 2);


	execute_SUB(mars, 0, warrior, instruction);

	assert(mars->memory[0].action == SUB);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 1);


	destroy_mars(mars);
}

void test_execute_MUL(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(2, 8, &instruction);
	instruction.action = MUL;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 1;
	instruction.field_b = 2;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == MUL);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 2);


	execute_MUL(mars, 0, warrior, instruction);

	assert(mars->memory[0].action == MUL);
	assert(mars->memory[0].field_a == 1);
	assert(mars->memory[0].field_b == 0);


	destroy_mars(mars);
}

void test_execute_DIV(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(10, 8, &instruction);
	instruction.action = DIV;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 2;
	instruction.field_b = 6;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == DIV);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 6);


	execute_DIV(mars, 0, warrior, instruction);

	assert(mars->memory[0].action == DIV);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 3);


	destroy_mars(mars);
}



void test_execute_MOD(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;
	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 0;

	mars = create_mars(10, 8, &instruction);
	instruction.action = MOD;
	instruction.modifier_action = MODIFIER_AB;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_IMMEDIATE;
	instruction.field_a = 2;
	instruction.field_b = 2;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(mars->memory[0].action == MOD);
	assert(mars->memory[0].modifier_action == MODIFIER_AB);
	assert(mars->memory[0].addressing_a == ADDR_IMMEDIATE);
	assert(mars->memory[0].addressing_b == ADDR_IMMEDIATE);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 2);


	execute_MOD(mars, 0, warrior, instruction);

	assert(mars->memory[0].action == MOD);
	assert(mars->memory[0].field_a == 2);
	assert(mars->memory[0].field_b == 0);

	destroy_mars(mars);
}

void test_execute_CMP(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 0;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = CMP;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);
	execute_CMP(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 0);
	
	mars->memory[1].field_a = 1;
	execute_CMP(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 2);

	destroy_mars(mars);
}

void test_execute_SNE(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = SNE;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);
	execute_SNE(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 0);
	
	mars->memory[1].field_a = 0;
	execute_SNE(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 2);

	destroy_mars(mars);
}

void test_execute_SLT(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	instruction.action = DAT;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_DIRECT;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	mars = create_mars(10, 8, &instruction);

	instruction.action = SNE;
	instruction.modifier_action = MODIFIER_A;
	instruction.addressing_a = ADDR_IMMEDIATE;
	instruction.addressing_b = ADDR_DIRECT;
	instruction.field_a = 1;
	instruction.field_b = 1;

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);

	assert(warrior->position_thread[0] == 0);
	execute_SLT(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 0);
	
	mars->memory[1].field_a = 0;
	execute_SLT(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 0);

	mars->memory[1].field_a = 2;
	execute_SLT(mars, 0, warrior, instruction);
	assert(warrior->position_thread[0] == 2);

	destroy_mars(mars);
}

void test_add_warrior_index(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	mars = create_mars(10, 8, &instruction);

	assert(mars->size_a_warrior == 0);
	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(warrior->position_thread[0] == 0);
	assert(mars->size_a_warrior == 1);

	add_warrior_index(mars, &instruction, 1, 0);
	assert(mars->size_a_warrior == 1);

	destroy_mars(mars);
}

void test_add_warrior(void)
{
	struct mars *mars = NULL;
	struct instruction instruction[3];
	struct warrior *warrior = NULL;

	mars = create_mars(10, 8, instruction);

	assert(mars->size_a_warrior == 0);

	add_warrior_index(mars, instruction, 1, 0);
	add_warrior_index(mars, instruction, 1, 3);
	add_warrior_index(mars, instruction, 1, 6);
	assert(mars->size_a_warrior == 3);
	add_warrior(mars, instruction, 3);
	assert(mars->size_a_warrior == 4);
	warrior = &(mars->a_warrior[3]);
	assert(warrior->position_thread[0] == 7);


	destroy_mars(mars);
}

void test_kill_current_thread(void)
{
	struct mars *mars = NULL;
	struct instruction instruction;
	struct warrior *warrior = NULL;

	mars = create_mars(10, 8, NULL);

	add_warrior_index(mars, &instruction, 1, 0);
	warrior = &(mars->a_warrior[0]);
	assert(warrior->size_position_thread == 1);
	kill_current_thread(warrior);
	assert(warrior->size_position_thread == 0);

	destroy_mars(mars);
}
