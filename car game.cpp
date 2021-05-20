#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70


using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','*','*',' ', 
					'1','*','*','1', 
					' ','*','*',' ',
					'1','*','*','1' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 
int deathcount = 0;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"+";
			gotoxy(WIN_WIDTH-j,i); cout<<"+";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"+";
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 || enemyY[0]+3 >= 23 || enemyY[0]+2 >= 23 || enemyY[0]+1 >= 23){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			resetEnemy(0);
			return 1;
		}
	}
	
	if( enemyY[1]+4 >= 23 || enemyY[1]+3 >= 23 || enemyY[1]+2 >= 23 || enemyY[1]+1 >= 23){
		if( enemyX[1] + 4 - carPos >= 0 && enemyX[1] + 4 - carPos < 9  ){
			resetEnemy(1);
			return 1;
		}
	}
	return 0;
} 
void gamewin(){
	system("cls");
	cout<<endl;
	cout<<"\n\n\n\t\t\t\t--------------------------"<<endl;
	cout<<"\t\t\t\t--------- You Win --------"<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t\t\t----- congratulations "<<score<<" ----"<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t\t\tPress any key to go back to menu.";
	getch();
}
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\n\n\n\t\t\t\t--------------------------"<<endl;
	cout<<"\t\t\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t\t\t----- Your Score is "<<score<<" ----"<<endl;
	cout<<"\t\t\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t\t\tPress any key to go back to menu.";
	getch();
}
int updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
	return score;
}
void easyupdateDead(){
	gotoxy(WIN_WIDTH + 7, 6);cout<<"Life: "<<3-deathcount<<endl;
}

void normalupdateDead(){
	gotoxy(WIN_WIDTH + 7, 6);cout<<"Life: "<<2-deathcount<<endl;
}

void hardupdateDead(){
	gotoxy(WIN_WIDTH + 7, 6);cout<<"Life: "<<1-deathcount<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"\n\n\n\n\n\t\t\t\t\t\t\tInstructions";
	cout<<"\n\t\t\t\t\t\t---------------------------";
	cout<<"\n\t\t\t\t\t----Avoid Cars by moving left or right---- ";
	cout<<"\n\n\t\t\t\t\t\t Press 'a' to move left";
	cout<<"\n\t\t\t\t\t\t Press 'd' to move right";
	cout<<"\n\n\t\t\t\t\t\t OR";
	cout<<"\n\n\t\t\t\t\t\t Press '4' to move left";
	cout<<"\n\t\t\t\t\t\t Press '6' to move right";
	cout<<"\n\t\t\t\t\t\t Press 'escape' to exit";
	cout<<"\n\n\t\t\t\t\t----Press any key to go back to menu----";
	getch();
}

void gameinstructions(){
	
	system("cls");
	cout<<"\n\n\n\n\n\t\t\t\t\t\t\tHow to play";
	cout<<"\n\t\t\t\t\t\t---------------------------";
	cout<<"\n\t\t\t\t\tEasy mode: 3 times crash, win when the score is 120";
	cout<<"\n\t\t\t\t\tNormal mode: 2 times crash, win when the score is 120";
	cout<<"\n\t\t\t\t\tHard mode: 1 time crash, win when the score is 120";
	cout<<"\n\n\t\t\t\t\t\t Press 'a' to move left";
	cout<<"\n\t\t\t\t\t\t Press 'd' to move right";
	cout<<"\n\n\t\t\t\t\t\t OR";
	cout<<"\n\n\t\t\t\t\t\t Press '4' to move left";
	cout<<"\n\t\t\t\t\t\t Press '6' to move right";
	cout<<"\n\t\t\t\t\t\t Press 'escape' to exit";
	cout<<"\n\n\t\t\t\t\t----Press any key to go back to menu----";
	getch();
}

void easymode(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	deathcount = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	easyupdateDead();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 3);cout<<" Go Kart ";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 7);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH + 9, 17);cout<<" OR ";
	gotoxy(WIN_WIDTH + 2, 19);cout<<" 4 NumKey - Left";
	gotoxy(WIN_WIDTH + 2, 20);cout<<" 6 NumKey - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' || ch=='4'){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' || ch=='6' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			deathcount++;
			easyupdateDead();
			if (deathcount >= 3){
				gameover();
				return;
			}
		} 
		if( updateScore() == 120)
		{
			gamewin();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

void normalmode()
{
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	deathcount = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 8;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	normalupdateDead();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 3);cout<<" Go Kart ";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 7);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH + 9, 17);cout<<" OR ";
	gotoxy(WIN_WIDTH + 2, 19);cout<<" 4 NumKey - Left";
	gotoxy(WIN_WIDTH + 2, 20);cout<<" 6 NumKey - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' || ch=='4'){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' || ch=='6' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			deathcount++;
			normalupdateDead();
			if (deathcount >= 2){
				gameover();
				return;
			}
		} 
		if( updateScore() == 120)
		{
			gamewin();
			return;
		} 
		Sleep(30);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

void hardmode()
{
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	deathcount = 0;
	enemyFlag[0] = 1; /*1*/
	enemyFlag[1] = 0; /*0*/
	enemyY[0] = enemyY[1] = 10; /*1*/
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	hardupdateDead();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 3);cout<<" Go Kart ";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 7);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH + 9, 17);cout<<" OR ";
	gotoxy(WIN_WIDTH + 2, 19);cout<<" 4 NumKey - Left";
	gotoxy(WIN_WIDTH + 2, 20);cout<<" 6 NumKey - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' || ch=='4'){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' || ch=='6' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			deathcount++;
			hardupdateDead();
			if (deathcount >= 1){
				gameover();
				return;
			}
		} 
		if( updateScore() == 120)
		{
			gamewin();
			return;
		} 
		Sleep(20); /*50*/
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1; /*1*/
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){ 
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){ 
			resetEnemy(1);  
			score++;
			updateScore();
		}
	}
}

int gamemode(){
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        Game Mode       | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Easy Mode";
		gotoxy(10,10); cout<<"2. Normal Mode";	 
		gotoxy(10,11); cout<<"3. Hard Mode";
		gotoxy(10,12); cout<<"4. How to play";
		gotoxy(10,13); cout<<"5. Quit";
		gotoxy(10,16); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') easymode();
		else if( op=='2') normalmode();
		else if( op=='3') hardmode();
		else if( op=='4') gameinstructions();
		else if( op=='5') exit(0);
		
	}while(1);
	
	return 0;
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        Car Game        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
