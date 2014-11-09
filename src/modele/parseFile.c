#include "parseFile.h"

struct instruction *parse_file(char *filename, unsigned short *size_instruction)
{
	struct instruction *tab = NULL;
	*size_instruction = 0;
	FILE *fichier = NULL;
	char line[TAILLE_MAX] = "";
	struct instruction instruction;
	fichier = fopen(filename, "r+");
	if(fichier != NULL)
	{
		while(fgets(line, TAILLE_MAX, fichier))
		{
			instruction = parse_line(line);
			if(instruction.action != ERROR_ACTION)
			{
				*size_instruction += 1;
				tab = realloc(tab, (*size_instruction) * sizeof(struct instruction));
				tab[*size_instruction - 1] = instruction;
			}
		}
		fclose(fichier);
	}
	return tab;
}

struct instruction parse_line(char *line)
{
	struct instruction instruction;
	char *action = NULL;
	char tmp_action[TAILLE_MAX] = "";
	char *md_action = NULL;
	int fd_a;
	int fd_b;
	char ad_a = 0;
	char ad_b = 0;
	//Petit changement de syntaxe en dessous, j'ai remplacé l'espace par un point
	//D'autre changements sont à prévoir et à tester (on en reparle demain).
	int err = sscanf(line, "%s %c%d, %c%d", tmp_action, &ad_a, &fd_a, &ad_b, &fd_b);
	action = strtok(tmp_action, ".");
	md_action = strtok(NULL, ".");
	if(err < 5 || action == NULL || md_action == NULL)
	{
		instruction.action = ERROR_ACTION;
		return instruction;
	}
	instruction.field_a = fd_a;
	instruction.field_b = fd_b;
	if(strcmp(action, "DAT") == 0)
		instruction.action = DAT;
	else if(strcmp(action, "MOV") == 0)
		instruction.action = MOV;
	else if(strcmp(action, "ADD") == 0)
		instruction.action = ADD;
	else if(strcmp(action, "SUB") == 0)
		instruction.action = SUB;
	else if(strcmp(action, "MUL") == 0)
		instruction.action = MUL;
	else if(strcmp(action, "DIV") == 0)
		instruction.action = DIV;
	else if(strcmp(action, "MOD") == 0)
		instruction.action = MOD;
	else if(strcmp(action, "JMP") == 0)
		instruction.action = JMP;
	else if(strcmp(action, "JMZ") == 0)
		instruction.action = JMZ;
	else if(strcmp(action, "JMN") == 0)
		instruction.action = JMN;
	else if(strcmp(action, "DJN") == 0)
		instruction.action = DJN;
	else if(strcmp(action, "SPL") == 0)
		instruction.action = SPL;
	else if(strcmp(action, "CMP") == 0)
		instruction.action = CMP;
	else if(strcmp(action, "SEQ") == 0)
		instruction.action = SEQ;
	else if(strcmp(action, "SNE") == 0)
		instruction.action = SNE;
	else if(strcmp(action, "SLT") == 0)
		instruction.action = SLT;
	else if(strcmp(action, "LDP") == 0)
		instruction.action = LDP;
	else if(strcmp(action, "STP") == 0)
		instruction.action = STP;
	else if(strcmp(action, "NOP") == 0)
		instruction.action = NOP;
	else
		instruction.action = ERROR_ACTION;


	if(strcmp(md_action, "A") == 0)
		instruction.modifier_action = MODIFIER_A;
	else if(strcmp(md_action, "B") == 0)
		instruction.modifier_action = MODIFIER_B;
	else if(strcmp(md_action, "AB") == 0)
		instruction.modifier_action = MODIFIER_AB;
	else if(strcmp(md_action, "BA") == 0)
		instruction.modifier_action = MODIFIER_BA;
	else if(strcmp(md_action, "F") == 0)
		instruction.modifier_action = MODIFIER_F;
	else if(strcmp(md_action, "X") == 0)
		instruction.modifier_action = MODIFIER_X;
	else if(strcmp(md_action, "I") == 0)
		instruction.modifier_action = MODIFIER_I;
	else
		instruction.action = ERROR_ACTION;

	switch (ad_a)
	{
	case '#':
		instruction.addressing_a = ADDR_IMMEDIATE;
		break;
	case '$':
		instruction.addressing_a = ADDR_DIRECT;
		break;
	case '*':
		instruction.addressing_a = ADDR_INDIRECT_A;
		break;
	case '{':
		instruction.addressing_a = ADDR_INDIRECT_A_PREDECREMENT;
		break;
	case '}':
		instruction.addressing_a = ADDR_INDIRECT_A_POSTINCREMENT;
		break;
	case '@':
		instruction.addressing_a = ADDR_INDIRECT_B;
		break;
	case '<':
		instruction.addressing_a = ADDR_INDIRECT_B_PREDECREMENT;
		break;
	case '>':
		instruction.addressing_a = ADDR_INDIRECT_B_POSTINCREMENT;
		break;
	default:
		instruction.action = ERROR_ACTION;
	}
	switch (ad_b)
	{
	case '#':
		instruction.addressing_b = ADDR_IMMEDIATE;
		break;
	case '$':
		instruction.addressing_b = ADDR_DIRECT;
		break;
	case '*':
		instruction.addressing_b = ADDR_INDIRECT_A;
		break;
	case '{':
		instruction.addressing_b = ADDR_INDIRECT_A_PREDECREMENT;
		break;
	case '}':
		instruction.addressing_b = ADDR_INDIRECT_A_POSTINCREMENT;
		break;
	case '@':
		instruction.addressing_b = ADDR_INDIRECT_B;
		break;
	case '<':
		instruction.addressing_b = ADDR_INDIRECT_B_PREDECREMENT;
		break;
	case '>':
		instruction.addressing_b = ADDR_INDIRECT_B_POSTINCREMENT;
		break;
	default:
		instruction.action = ERROR_ACTION;
	}
	return instruction;
}
