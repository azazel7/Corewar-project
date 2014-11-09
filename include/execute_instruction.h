#ifndef  execute_instruction_INC
#define  execute_instruction_INC
#include <math.h>
#include "mars.h"
#include "header.h"

/*
 * mars             The mars machine whiche execute the instruction
 * index_instruction    The index of the instruction which will be execute
 * current_warrior  The warrior which execute the instruction
 * instruction      The value of the instruction
 */
void execute_DAT(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_SPL(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_MOV(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_JMP(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_ADD(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_SUB(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_MUL(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_DIV(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_MOD(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_CMP(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_JMZ(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_DJN(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_JMN(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_SEQ(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_SNE(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_SLT(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);
void execute_POW(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction);

void execute_arithmetique_operation(struct mars *mars, unsigned short index_instruction, struct warrior *current_warrior, struct instruction instruction, char *check_zero_flag, short (*arithmetique_function) (short, short, struct mars *));
short arithmetique_add(short origine, short destination, struct mars *mars);
short arithmetique_sub(short origine, short destination, struct mars *mars);
short arithmetique_mul(short origine, short destination, struct mars *mars);
short arithmetique_div(short origine, short destination, struct mars *mars);
short arithmetique_mod(short origine, short destination, struct mars *mars);
short arithmetique_pow(short origine, short destination, struct mars *mars);
#endif
