#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"
#define TAILLE_MAX 1000

struct instruction *parse_file(char *filename, unsigned short *size_instruction);

struct instruction parse_line(char *line);
