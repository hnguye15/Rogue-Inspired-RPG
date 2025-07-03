#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void enableRawMode();
void disableRawMode();
void makeMenu();
void printMenu();
//void traverseMenu();
void cleanLine();
void highlight();
void game();

struct termios orig_termios;

int main(){
	enableRawMode();
	
	bool exit = false;
	char menu[4][50];
//	char (*menu)[50] = malloc(sizeof(char[50][50]));
	int menuIndex = 0;
	int key;
	char c;
	makeMenu(menu);
	printMenu(menu);
	
	while(!exit) {
		if (read(STDIN_FILENO, &c, 1) == 1) {
			key = c;
			
			//Move up
			if (key == 65) {
				cleanLine(menu[menuIndex]);
				if (menuIndex == 0) {
					menuIndex = 3;
				}
				else {menuIndex -= 1;}
				highlight(menu[menuIndex]);
//				system("clear");	
				printMenu(menu);
				
			}
			
			//Move down
			else if (key == 66) {
				cleanLine(menu[menuIndex]);
				if (menuIndex == 3) {
					menuIndex = 0;
				}
				else {menuIndex += 1;}
				highlight(menu[menuIndex]);
//				system("clear");
				printMenu(menu);
			}
			else if (key == 10 && menuIndex == 0) {
//				system("clear");
				break;	
			}
			else if (key == 10 && menuIndex == 3) {
				exit = true;
			}
			
		}
	}
	
	if (!exit) {
		game();
	}
	system("clear");
	
	disableRawMode();
	return 0;
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	  
	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void makeMenu(char menu[4][50]) {
	strcpy(menu[0], "--> Start");
	strcpy(menu[1], "Options");
	strcpy(menu[2], "Credits");
	strcpy(menu[3], "Exit");
}

void printMenu(char menu[4][50]){
	char xBorder[5] = "||";
	char yBorder[20] = "===========";
	int i;
	printf(" %sRandom RPG Game%s\n%s%37s\n", yBorder, yBorder, xBorder, xBorder);
	printf("%s%20s%17s\n%s%37s\n", xBorder, menu[0], xBorder, xBorder, xBorder);
	printf("%s%21s%16s\n%s%37s\n", xBorder, menu[1], xBorder, xBorder, xBorder);
	printf("%s%21s%16s\n%s%37s\n", xBorder, menu[2], xBorder, xBorder, xBorder);
	printf("%s%19s%18s\n%s%37s\n", xBorder, menu[3], xBorder, xBorder, xBorder);
	putchar(' ');
	for (i = 0; i < 37; i++) {
		putchar(yBorder[0]);
	}
	putchar('\n');
}

/*
void traverseMenu(char menu[4][50], int* menuIndex, int key){
	if (key == 72) {
		cleanLine(menu[*menuIndex]);
		if (*menuIndex == 0) {
			*menuIndex = 3;
		}
		else {*menuIndex -= 1;}
		highlight(menu[*menuIndex]);
		system("cls");
		printMenu(menu);
		
	}
	else if (key == 80) {
		cleanLine(menu[*menuIndex]);
		if (*menuIndex == 3) {
			*menuIndex = 0;
		}
		else {*menuIndex += 1;}
		highlight(menu[*menuIndex]);
		system("cls");
		printMenu(menu);
	}
	else if (key == 13 && *menuIndex == 3) {
		exit(0);
	}
}
*/

void cleanLine(char* line) {
	char cleaned[50];
	int indexer = 0;
	int i;
	for (i = 0; i < 50 && line[i] != '\0'; i++) {
		if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123)) {
			cleaned[indexer] = line[i];
			indexer++;
		}
	}
	if (line != NULL) {
		strcpy(line, cleaned);
	}
}

void highlight(char* line) {
	char highlighted[50] = "--> ";
	strcat(highlighted, line);
	strcpy(line, highlighted);
}

void game() {
	int x = 100;
	int y = 50;
	int symbol = 250;
	char* map = malloc((x * y) * sizeof(int));
//	char* cell;
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			map[i * x + j] = symbol;
		}
	}
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			printf("%c", map[i * x + j]);
		}
		printf("\n");
	}
	//getc();
}
