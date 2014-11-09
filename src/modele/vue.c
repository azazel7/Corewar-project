#include "vue.h"
#define ENTER 10

void init_view(struct mars *mars)
{
	initscr();					/* Start curses mode        */
	WINDOW *my_win = newwin(0, 0, 0, 0);
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_WHITE);
	init_pair(10, COLOR_GREEN, COLOR_WHITE);
	init_pair(11, COLOR_YELLOW, COLOR_WHITE);
	init_pair(12, COLOR_BLUE, COLOR_WHITE);
	init_pair(13, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(14, COLOR_CYAN, COLOR_WHITE);
	init_pair(15, COLOR_WHITE, COLOR_WHITE);
	init_pair(16, COLOR_BLACK, COLOR_WHITE);
	struct instruction tampon[mars->size_memory];	//memoire tampon
	int cursor = 0;
	char offset_color = 0, finish = 0;
	char *titre = "CORE WAR !!!\n";
	char letter;
	int color;	
	curs_set(0);				//cursor invisible
	noecho();					//No display of characters
	int c = 0;
	short nb_dead = 0;
	clear();
	keypad(stdscr, TRUE);	
	int height, width;
	while(mars->current_cycle < mars->max_cycle)
	{
		getmaxyx(stdscr, height, width);	
		move(0, 0);
		if(c == 'q')
		{
			break;
		}
		else if(c == '\n' && finish == 0)
		{
			spend_cycle(mars);
		}
		else if(c == ' ' && finish == 0)
		{
			for(int i = 0; i < 100; i++)
			{
				spend_cycle(mars);
			}
		}
		else if(c == KEY_LEFT)
		{
			cursor--;
			if(cursor < 0)
			{
				cursor = 0;
			}
		}
		else if(c == KEY_RIGHT)
		{
			cursor++;
			if(cursor >= mars->size_memory )
			{
				cursor = mars->size_memory - 1;
			}
		}
		else if(c == KEY_DOWN)
		{
			cursor+=width;
			if(cursor >= mars->size_memory )
			{
				cursor = mars->size_memory - 1;
			}
		}
		else if(c == KEY_UP)
		{
			cursor-=width;
			if(cursor < 0)
			{
				cursor = 0;
			}
		}

		printw(titre);
		printw("\n");
		//Affichage des n-guerriers (n[1;7])   
		for(int i = 0; i < mars->size_a_warrior; i++)
		{
			choose_color_letter(i, &color, &letter);

			attron(COLOR_PAIR(color));
			if(warrior_is_dead(&(mars->a_warrior[i])))
			{
				printw("Warrior %d -> Dead\n", i + 1);
			}
			else
			{
				printw("Warrior %d (%c) -> (", i + 1, letter);
				for(int j = 0; j < mars->a_warrior[i].size_position_thread; j++)
				{
					if(j != 0)
					{
						printw ( "," );
					}
					printw(" %u",mars->a_warrior[i].position_thread[j]);
				}
				printw ( ")\n" );
			}
			attroff(COLOR_PAIR(color));
		}
		printw("\n");

		printw ( "=== Begin of memory\n" );
		for(int i = 0; i < mars->size_memory; i++)
		{
			if(cursor == i)
			{
				offset_color = 8;
			}
			if(mars->memory[i].idx_last_warrior >= 1 && mars->memory[i].idx_last_warrior <= 7*26)
			{
				choose_color_letter(mars->memory[i].idx_last_warrior - 1, &color, &letter);
				attron(COLOR_PAIR(color + offset_color));
				printw("%c", letter);
				attroff(COLOR_PAIR(color + offset_color));
			}
			else
			{
				attron(COLOR_PAIR(8 + offset_color));
				printw(" ");
				attroff(COLOR_PAIR(8+ offset_color));
			}
			offset_color = 0;
		}
		printw ( "===End of memory\n" );

		printw("\n Cycles :%u / %u",mars->current_cycle, mars->max_cycle);
		printw("\n Press ENTER to spend one cycle !");
		printw("\n Press 'q' to quit !\n");
		printw(" Cursor : %d -> ", cursor);
		print_instrction(mars->memory[cursor]); 
		printw("\n");
		//================Victory test
		nb_dead = 0;
		for(int i = 0; i < mars->size_a_warrior; i++)
		{
			if(warrior_is_dead(&(mars->a_warrior[i])))
			{
				nb_dead++;
			}
		}
		if(mars->size_a_warrior - nb_dead == 1)
		{
			for(int i = 0; i < mars->size_a_warrior; i++)
			{
				if( ! warrior_is_dead(&(mars->a_warrior[i])))
				{
					printw("\nWARRIOR %d WIN !!!", i + 1);
					finish = 1;
				}
			}
		}
		else if(mars->size_a_warrior == nb_dead)
		{
					printw("\nIt's funny, everybody is dead ;-)\n");
					finish = 1;
		}
		refresh();
		c = getch();
	}
	endwin();					/* End curses mode        */
}


void print_instrction(struct instruction instruction)
{
	switch (instruction.action)
	{
	case DAT:
		printw("DAT");
		break;
	case MOV:
		printw("MOV");
		break;
	case ADD:
		printw("ADD");
		break;
	case SUB:
		printw("SUB");
		break;
	case MUL:
		printw("MUL");
		break;
	case DIV:
		printw("DIV");
		break;
	case MOD:
		printw("MOD");
		break;
	case JMP:
		printw("JMP");
		break;
	case JMZ:
		printw("JMZ");
		break;
	case JMN:
		printw("JMN");
		break;
	case DJN:
		printw("DJN");
		break;
	case SPL:
		printw("SPL");
		break;
	case CMP:
		printw("CMP");
		break;
	case SEQ:
		printw("SEQ");
		break;
	case SNE:
		printw("SNE");
		break;
	case SLT:
		printw("SLT");
		break;
	case LDP:
		printw("LDP");
		break;
	case STP:
		printw("STP");
		break;
	case NOP:
		printw("NOP");
		break;
	}
	printw(".");
	switch (instruction.modifier_action)
	{
	case MODIFIER_A:
		printw("A");
		break;
	case MODIFIER_B:
		printw("B");
		break;
	case MODIFIER_AB:
		printw("AB");
		break;
	case MODIFIER_BA:
		printw("BA");
		break;
	case MODIFIER_F:
		printw("F");
		break;
	case MODIFIER_X:
		printw("X");
		break;
	case MODIFIER_I:
		printw("I");
		break;
	}
	printw(" ");
	switch (instruction.addressing_a)
	{
	case ADDR_IMMEDIATE:
		printw("#");
		break;
	case ADDR_DIRECT:
		printw("$");
		break;
	case ADDR_INDIRECT_A:
		printw("*");
		break;
	case ADDR_INDIRECT_A_PREDECREMENT:
		printw("{");
		break;
	case ADDR_INDIRECT_A_POSTINCREMENT:
		printw("}");
		break;
	case ADDR_INDIRECT_B:
		printw("@");
		break;
	case ADDR_INDIRECT_B_PREDECREMENT:
		printw("<");
		break;
	case ADDR_INDIRECT_B_POSTINCREMENT:
		printw(">");
		break;
	}
	printw("%d, ", instruction.field_a);
	switch (instruction.addressing_b)
	{
	case ADDR_IMMEDIATE:
		printw("#");
		break;
	case ADDR_DIRECT:
		printw("$");
		break;
	case ADDR_INDIRECT_A:
		printw("*");
		break;
	case ADDR_INDIRECT_A_PREDECREMENT:
		printw("{");
		break;
	case ADDR_INDIRECT_A_POSTINCREMENT:
		printw("}");
		break;
	case ADDR_INDIRECT_B:
		printw("@");
		break;
	case ADDR_INDIRECT_B_PREDECREMENT:
		printw("<");
		break;
	case ADDR_INDIRECT_B_POSTINCREMENT:
		printw(">");
		break;
	}

	printw("%d\n", instruction.field_b);
}

void print_memory(struct mars *mars, struct instruction *tampon)
{
	for(int i = 0; i < mars->size_memory; i++)
	{
		print_instrction(mars->memory[i]);
		tampon[i] = mars->memory[i];
	}
}

void choose_color_letter(unsigned short idx_warrior, int* color, char* letter)
{
	if(idx_warrior < 7*26)
	{
		*color = (idx_warrior % 7) + 1;
		*letter = ((idx_warrior - (idx_warrior % 7))/7) + 'a'; 
	}
	else
	{
		*color = 0;
	}
}
