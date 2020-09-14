#include <iostream>
#include <Windows.h>
using namespace std;

//tools (I used another method)
void Clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}
//outputs the table
void display(char table[7][7]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	for (i = 0; i <= 5; ++i) {
		for (j = 0; j <= 5; ++j) {
			if (table[i][j] == 'O') {
				SetConsoleTextAttribute(hConsole, 3);
			}
			else if (table[i][j] == 'X') {
				SetConsoleTextAttribute(hConsole, 4);
			}
			else if (table[i][j]+0>=49 && table[i][j]+0<=51) {
				SetConsoleTextAttribute(hConsole, 13);
			}
			else {
				SetConsoleTextAttribute(hConsole, 15);
			}
			cout << table[i][j]<<' ';
		}
		cout << '\n';
	}
}
//initialize the table with empty spaces
void firstInit(char table[7][7]) {
	int i, j;
	for (i = 0; i <= 4; ++i) {
		for (j = 0; j <= 4; ++j) {
		table[i][j] = ' ';
		}
	}
}
//makes the table (the lines and colums)
void init(char table[7][7]) {
	for (int i = 0; i <= 4; i += 2) {
		table[i][1] = '|';
		table[i + 1][1] = '.';
		table[i][3] = '|';
		table[i + 1][3] = '.';
	}
	for (int j = 0; j <= 4; j += 2) {
		table[1][j] = '_';
		table[3][j] = '_';
	}
	int kk = 1;
	for(int k=0;k<=4;k+=2){
		table[5][k] = kk+'0';
		table[5][k+1]= ' ';
		table[k][5] = kk+'0';
		table[k+1][5] = ' ';
		kk++;
	}
}

//translates the x and y from the user variant to the actual position in the matrix
void translate(int& x, int& y) {
	if (x == 1) { x = 0; }
	else if (x == 3) { x = 4; }
	if (y == 1) { y = 0; }
	else if (y == 3) { y = 4; }
}
//takes the data from the user, also checks if the spot is "available", and here is where the translation is happening
void inputMutare(int& x, int& y, char table[7][7]) {
	while (true) {
		cout << "Introduceti linia si coloana pe care vreti sa mutati:\nLinia:  ";
		cin >> x;
		cout << "\nColoana: ";
		cin >> y;
		translate(x, y);
		if (table[x][y] == ' ') { break; }
	}
	//translate(x, y);
}
//aplies the move accordingly wiht the player O or X
void mutare(int x, int y, int player, char table[7][7]) {
	if (player == 1) { table[x][y] = 'O'; }
	else { table[x][y] = 'X'; }
}


//check if the game is over in all of the directions
bool checkGameOver(char table[7][7]) {
	//check the lines:
	int i, j, count;
	for (i = 0; i <= 4; i += 2) {
		if (table[i][0]!=' ' && table[i][2] != ' ' && table[i][4] != ' ' && table[i][0] == table[i][2] && table[i][2] == table[i][4]) return true;
	}
	
	//check the collumns:
	for (i = 0; i <= 4; i += 2) {
		if (table[0][i] != ' ' && table[2][i] != ' ' && table[4][i] != ' ' && table[0][i] == table[2][i] && table[2][i] == table[4][i]) return true;
	}

	//check the first diagonal ->
	/*
	00		04
		22
	40		44
	*/
	if (table[0][0] != ' ' && table[2][2] != ' ' && table[4][4] != ' ' && table[0][0] == table[2][2] && table[2][2] == table[4][4]) return true;

	//check the second diagonal <-
	if (table[0][4] != ' ' && table[2][2] != ' ' && table[4][0] != ' ' && table[0][4] == table[2][2] && table[2][2] == table[4][0]) return true;
	
	//It gets here only in the case of a TIE
	return false;
}
//verifies if the game is a tie.
bool checkTie(char table[7][7]) {
	int i, j, count = 0;
	for (i = 0; i <= 4; i += 2) {
		for (j = 0; j <= 4; j += 2) {
			if (table[i][j] == 'O' || table[i][j]=='X') {
				count++;
			}
		}
	}
	if (count == 9) { return true; }
	else { return false; }

}

int main() {
	bool gameOver = false;
	int x = 0, y = 1; //initializez pozitia pe care ar trebui sa o verificam prima data invalida.
	int player = 1;
	char table[7][7];
	firstInit(table);
	init(table);
	display(table);
	while (gameOver==false) {
		inputMutare(x, y, table);
		mutare(x, y, player, table);
		display(table);
		system("CLS"); //goleste consola ca sa nu fim nevoiti sa facem scroll, o da avem tabela in acelasi loc mereu.
		display(table);//din cauza ca am curatat consola trebuie sa afisam din nou si tabela
		if (checkGameOver(table) == true) {
			if (player == 1) {
				cout << "GAME OVER\nJucatorul O a castigat!!!\n";
			}
			else {
				cout << "GAME OVER\nJucatorul X a castigat!!!\n";

			}
			gameOver = true;
			break;
		}
		else if (checkTie(table) == true)
		{
			gameOver = true;
			cout << "GAME OVER\nRemiza!!!";
			break;
		}
		//schimbam playerul care trebuie sa faca mutarea.
		if (player == 1) { player = 2; }
		else{player = 1;}

	}
}