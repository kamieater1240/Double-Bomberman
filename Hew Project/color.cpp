#define _CRT_SECURE_NO_WARNINGS
#include "color.h"



int colorDecoder(char color) {
	switch (color) {
		case('0'):
			return 17 * BLACK;
			break;
		case('1'):
			return 17 * DARK_BLUE;
		case('2'): 
			return 17 * DARK_GREEN;
		case('3'): 
			return 17 * DARK_CYAN;
		case('4'): 
			return 17 * DARK_RED;
		case('5'): 
			return 17 * DARK_VIOLET;
		case('6'): 
			return 17 * DARK_YELLOW;
		case('7'): 
			return 17 * LIGHT_GRAY;
		case('8'): 
			return 17 * DARK_GRAY;
		case('9'): 
			return 17 * BLUE;
		case('A'): 
			return 17 * GREEN;
		case('B'): 
			return 17 * CYAN;
		case('C'): 
			return 17 * RED;
		case('D'):
			return 17 * VIOLET;
		case('E'):
			return 17 * YELLOW;
		case('F'):
			return 17 * WHITE;
		case('G'):
			return TRANSPARENTFLAG;
	}

}
