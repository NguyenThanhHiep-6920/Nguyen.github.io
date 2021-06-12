// Typing project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
HANDLE  hConsoleOut;                   /* Handle ke konzolovemu oknu */
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;   /* informace o konzolovem okne */

void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void GotoXY(int x, int y)  //added
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


void TypeLineStyle(char* file);
void TypeFiles(std::string sourceCode[50],int pocet);

int main()
{
	// TypeFiles
	std::string ListFile[3] = { "random.txt","DecimalSystemAndOther.txt","Vektor.txt" };
	int Pocet = 3;

	//LINESTYLE_1FILE
	char File[] = "SourceCode.txt";


	clock_t start = clock();

	TypeFiles(ListFile, Pocet);
	//TypeLineStyle(File);         //Esc to escape
	
	clock_t end = clock();

	system("cls");               
	GotoXY(0, 0);
	printf("total time: %f s", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}

void TypeLineStyle(char* file) {
	FILE* soubor;
	bool konec = false;
	int pocetRadku = 0;
	fopen_s(&soubor, file, "r");
	char temp[200];
	while (fgets(temp, 200, soubor) != NULL) {
		int typingIndex = 0;
		GotoXY(0, pocetRadku);
		SetColor(0, 7);
		std::cout << temp;
		GotoXY(0, pocetRadku);
		pocetRadku++;
		while (true) {
			int znak;
			if (_kbhit()) {
				znak = _getch();
				if (znak == 27) {
					konec = true; //escape
					break;
				}
				if (znak == 9) {
					printf("\t");    //tab           
				}
				else if (znak == temp[typingIndex]) {
					SetColor(0, 2);
					printf("%c", znak);
				}
				else {
					SetColor(0, 4);
					printf("%c", znak);
				}
				++typingIndex;
				if (typingIndex == strlen(temp)) {
					break;
				}
			}
		}
		if (konec) break;
	}
	fclose(soubor);
}
void TypeFiles(std::string listFile[50], int pocet) {
	FILE* soubor;
	////random 1 file
	//srand(time(NULL));
	//int randomIndex =rand()%pocet;
	//fopen_s(&soubor, listFile[randomIndex].c_str(), "r");
	for (size_t i = 0; i < pocet; i++)
	{
		char temp[5000];
		int indexCharacterTemp = 0;
		fopen_s(&soubor, listFile[i].c_str(), "r");
		while ((temp[indexCharacterTemp] = fgetc(soubor)) != EOF) {
			++indexCharacterTemp;
		}
		fclose(soubor);
		temp[indexCharacterTemp] = NULL;
		system("cls");
		GotoXY(0, 0);
		SetColor(0, 7);
		std::cout <<temp;
		int typingIndex = 0;
		GotoXY(0, 0);
		while (true) {
			int znak;
			if (_kbhit()) {
				znak = _getch();
				if (znak == 27) {
					break;        //escape. to next file
				}
				if (znak == 13) {
					printf("\n");//enter
				}
				if (znak == 9) {
					printf("\t");    //tab           
				}
				else if (znak == temp[typingIndex]) {
					SetColor(0, 2);
					printf("%c", znak);
				}
				else {
					SetColor(0, 4);
					printf("%c", znak);
				}
				++typingIndex;
				if (typingIndex == strlen(temp)) {
					break;
				}
			}
		}
	}
}
