#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define M 10
#define N 10
#define MINE -1
// Mang B luu bang do min
int B[M][N];
// Mang T luu trang thai cac o
int T[M][N];

    
void init(){
	int i, j;
	for(i = 0; i < M; i++)
		for(j = 0; j < N; j++){
			B[i][j] = 0;
			T[i][j] = 0;	
		}
}

void init_mines(int k){
	int cnt = 0, r, c;
	init();
	srand((int)time(0));
	while(cnt < k){
		r = rand() % M;
		c = rand() % N;
		if(B[r][c] != MINE){
			B[r][c] = MINE;
			cnt++;
		}
	}
}

void count_mines(){
	int i, j;
	for(i = 0; i < M; i++)
		for(j = 0; j < N; j++){
			if(B[i][j] != MINE){
			    int cnt = 0;
				if(i-1 >= 0 && j-1 >= 0 && B[i-1][j-1] == MINE)
					cnt++;
				if(i-1 >= 0 && B[i-1][j] == MINE)
					cnt++;
				if(i-1 >= 0 && j+1 < N && B[i-1][j+1] == MINE)
					cnt++;
				if(j-1 >= 0 && B[i][j-1] == MINE)
					cnt++;
				if(j+1 < N && B[i][j+1] == MINE)
					cnt++;
				if(i+1 < M && j-1 >= 0 && B[i+1][j-1] == MINE)
					cnt++;
				if(i+1 < M && B[i+1][j] == MINE)
					cnt++;
				if(i+1 < M && j+1 < N && B[i+1][j+1] == MINE)
					cnt++;
				B[i][j] = cnt;
			}
		}
}

void printMap1(){
	// For text color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
    
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	int i, j;
	printf("  ");
	for(j = 0; j < N; j++)
		printf("%d ", j%10);
	printf("\n");
	for(i = 0; i < M; i++){
		printf("%d ", i%10);
		for(j = 0; j < N; j++){
			if(B[i][j] == MINE){
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("x ");
				SetConsoleTextAttribute(hConsole, saved_attributes);
			}
			else if(B[i][j] == 0)
				printf(". ");
			else{
				if(B[i][j] == 1){
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf("%d ", B[i][j]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if(B[i][j] == 2){
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
					printf("%d ", B[i][j]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else{
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE + B[i][j] + 8 | FOREGROUND_INTENSITY);
					printf("%d ", B[i][j]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
					
			}
				
		}
		printf("\n");		
	}
}

void printMap2(){
	// For text color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
    
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	int i, j;
	printf("  ");
	for(j = 0; j < N; j++)
		printf("%d ", j%10);
	printf("\n");
	for(i = 0; i < M; i++){
		printf("%d ", i%10);
		for(j = 0; j < N; j++){
			if(T[i][j] == 1){
				if(B[i][j] == MINE){
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("x ");
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
				else if(B[i][j] == 0)
					printf(". ");
				else{
					if(B[i][j] == 1){
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						printf("%d ", B[i][j]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else if(B[i][j] == 2){
						SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
						printf("%d ", B[i][j]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
					else{
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE + B[i][j] + 8 | FOREGROUND_INTENSITY);
						printf("%d ", B[i][j]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						
				}
			}
			else
				printf("- ");
		}
		printf("\n");		
	}
}

void open_cell_1(int r, int c){
	if(T[r][c] == 0)
		T[r][c] = 1;
}

void open_cell_2(int r, int c){
	if(T[r][c] == 0)
		T[r][c]	= 1;
	if(B[r][c] == 0){
		if(r-1 >= 0 && c-1 >= 0 && B[r-1][c-1] != MINE)
			T[r-1][c-1] = 1;
		if(r-1 >= 0 && B[r-1][c] != MINE)
			T[r-1][c] = 1;
		if(r-1 >= 0 && c+1 < N && B[r-1][c+1] != MINE)
			T[r-1][c+1] = 1;
		if(c-1 >= 0 && B[r][c-1] != MINE)	
			T[r][c-1] = 1;
		if(c+1 < N && B[r][c+1] != MINE)
			T[r][c+1] = 1;
		if(r+1 < M && c-1 >= 0 && B[r+1][c-1] != MINE)
			T[r+1][c-1] = 1;
		if(r+1 < M && B[r+1][c] != MINE)
			T[r+1][c] = 1;
		if(r+1 < M && c+1 < N && B[r+1][c+1] != MINE)
			T[r+1][c+1] = 1;
	}
	
}

void open_cell_3(int r, int c){
	if(r < 0 || r >= M || c < 0 || c >= N)
		return;
	else if(T[r][c] == 1)
		return;
	else if(B[r][c] > 0){
		T[r][c] = 1;
		return;
	}
	else{
		T[r][c] = 1;
		if(B[r][c] == 0){
			open_cell_3(r-1, c-1);
			open_cell_3(r-1, c);
			open_cell_3(r-1, c+1);
			open_cell_3(r, c-1);
			open_cell_3(r, c+1);
			open_cell_3(r+1, c-1);
			open_cell_3(r+1, c);
			open_cell_3(r+1, c+1);
		}		
	}
}

int count_remain(){
	int cnt = 0;
	int i, j;
	for(i = 0; i < M; i++)
		for(j = 0; j < N; j++)
			if(T[i][j] == 0)
				cnt++;
	return cnt;
}

void cls(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}


int main(){
	// For text color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
    
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	int r, c;
	int k;
	printf("Nhap so min: ");
	scanf("%d", &k);
	init_mines(k);
	count_mines();
	while(1){
		printMap2();
		printf("Nhap o can mo: ");
		scanf("%d%d", &r, &c);
		if(B[r][c] == MINE){
			cls(hConsole);
			printMap1();
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("\nYou LOSE.\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
			break;
		}
		open_cell_2(r, c);
		cls(hConsole);
		if(count_remain() == k){
			cls(hConsole);
			printMap2();
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("\nYou WINNNNNNNN!!!\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
			break;
		}			
	}
	return 0;
}
