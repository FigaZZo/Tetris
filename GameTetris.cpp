#include <bits/stdc++.h>
#include <conio.h>
 
using namespace std;
 
const int N = 1e3;
 
enum eDirection {None, Left, Down, Right, Roll};
eDirection dir;
char board[N][N]; int TypeFigure[140];
bool GameOver = 0, FigureExist = 0;
int LastFigure, TypeScroll;
char updBoard[N][N];
int Score=0;
set<pair<int,string> > Top;
//mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
 
void Pause(){
    int cnt = 0;
    while(cnt < (int)1e8 + (int)5e7)
        cnt++;
}
 
void Lose(){
	string s;
  for(int i=0;i<=12;i++)
    if(board[0][i]=='0')
      GameOver=1;
    if(GameOver==0){
    	return;
	}
    if(GameOver==1){
    	cout << "Game Over" << endl << "Enter your Name: ";
    	cin >> s;
	}
	Top.insert({Score,s});
	set<pair<int,string> > Exam=Top;
	int i=1;
	while(Exam.size()){
		pair<int,string> p=(*(--Exam.end()));
		cout << i << ". "<< p.second << "\n";	
		Exam.erase(p);
		i++;
	}
	int lo;
	cin >> lo;
	if(lo==1){
		Score=0;
		for(int i=0;i<=50;i++){
			for(int j=1;j<=10;j++){
				board[i][j]=' ';
			}
		}
	}else{
		exit(0);
	}
}
void Delete(){
    int kol = 0;
    for(int i = 0; i <= 51; i++){
      int sum = 0;
      for(int j = 0; j <= 11; j++)
        if(board[i][j] == '0')
          sum++;
      if(sum == 10){
        kol++;
        for(int j = 1; j <= 10; j++)
          board[i][j] = ' ';
        for(int k = i - 1; k >= 0; k--)
          for(int j = 0; j <= 11; j++)
            if(board[k][j] == '0'){
              board[k + 1][j] = '0';
              board[k][j] = ' ';
            }
      }
    }
    if(kol == 1)
      Score +=100;
    if(kol == 2)
      Score += 250;
    if(kol == 3)
      Score += 500;
    if(kol == 4)
      Score += 1200;
}
bool Check(){
    bool ok = 1;
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            if(updBoard[i][j] == '1' && (board[i][j] == '#' || board[i][j] == '0'))
                ok = 0;
    return ok;
}
 
void update(){
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            if(board[i][j] == '1')
                board[i][j] = ' ';
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++) 
            if(updBoard[i][j] == '1')
                board[i][j] = '1';
}
 
void Rolling(){
	bool ok = 0;
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            updBoard[i][j] = ' ';
    if(LastFigure == 2){
        int x = -1, y = -1;
        for(int i = 0; i <= 51; i++)
            for(int j = 0; j <= 11; j++)
                if(board[i][j] == '1'){
                    if(x == -1)
                        x = i, y = j;
                    int addx = i - x, addy = j - y;
                    updBoard[x + addy][y + addx] = '1';    
                }
        ok = 1;        
    }
 
    if(LastFigure == 3){
      int x = -1, y = -1;
      for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
          if(board[i][j] == '1'){
            if(x == -1)
              if(TypeScroll%4==0 ||TypeScroll%4==1){
              	x=i;
              	y=j-1;
			  }else{
			  	x=i;
			  	y=j;
			  }
            int x1 = i - x, y1 = j - y;
            if(TypeScroll % 2 == 0)
              updBoard[x + y1][y + (2 - x1)] = '1';
            else
              updBoard[x + y1][y + (1 - x1)] = '1';
          }
      ok = 1;
    }
 
    if(LastFigure == 6){
      int x = -1, y = -1;
      for(int i = 0; i <= 51; i++)
          for(int j = 0; j <= 11; j++)
              if(board[i][j] == '1'){
                  if(x == -1)
                      if(TypeScroll % 2 == 0)
                          x = i, y = j;
                      else
                          x = i, y = j - 1;
                  int x1 = i - x, y1 = j - y;
                  if(TypeScroll % 2 == 0)
                      updBoard[y1 + x][y + (1 - x1)] = '1';
                  else
                      updBoard[x + (1 - y1)][x1 + y] = '1';
              }
        ok = 1;      
    }
 
    if(LastFigure == 5){
      int x = -1, y = -1;
      for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++){
          if(board[i][j] == '1'){
            if(TypeScroll % 4 == 3)
              x = i, y = j - 2;
          else
            x = i, y = j;
          }
            int x1 = i - x, y1 = j - y;
            if(TypeScroll % 2 == 0)
              updBoard[x + y1][y + (2 - x1)] = '1';
            else
              updBoard[x + y1][y + (1 - x1)] = '1';
          }
 
      ok = 1;
    }
 
    if(LastFigure == 4){
      int x = -1, y = -1;
      for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
          if(board[i][j] == '1'){
            if(x == -1)
              if(TypeScroll % 4 == 0)
                x = i, y = j - 1;
              else
                x = i, y = j;
            int x1 = i - x, y1 = j - y;
            if(TypeScroll % 2 == 0)
              updBoard[x + y1][y + (2 - x1)] = '1';
            else
              updBoard[x + y1][y + (1 - x1)] = '1';
          }
      ok = 1;
    }
 
    if(LastFigure == 7){
      int x = -1, y = -1;
      for(int i = 0; i <= 51; i++)
          for(int j = 0; j <= 11; j++)
              if(board[i][j] == '1'){
                  if(x == -1)
                      if(TypeScroll % 2 == 1)
                          x = i, y = j;
                      else
                          x = i, y = j - 1;
                  int x1 = i - x, y1 = j - y;
                  if(TypeScroll % 2 == 0)
                      updBoard[y1 + x][y + (1 - x1)] = '1';
                  else
                      updBoard[x + (1 - y1)][x1 + y] = '1';
              }
              ok = 1;
    }
 
    if(Check() and ok)
        update(), TypeScroll++;
}
 
void MoveFigure(){
    dir = None;
    if(_kbhit()){
        switch(_getch ()){
            case 'x':
                dir = Roll;
                break;
            case 's':
                dir = Down;
                break;
            case 'd':
                dir = Right;
                break;
            case 'a':
                dir = Left;
                break;
            case '/':
                GameOver = 1;
                break;                
        }
    }
 
    bool ok = 0;
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            updBoard[i][j] = ' ';
    for(int i = 0; i <= 50; i++)
        for(int j = 0; j <= 10; j++)
            if(board[i][j] == '1'){
                switch(dir){
                    case Left:
                        updBoard[i][j - 1] = '1';
                        ok = 1;
                        break;
                    case Right:
                        updBoard[i][j + 1] = '1'; 
                        ok = 1;
                        break;
                    case Down:
						              updBoard[i + 1][j] = '1';
						              ok = 1;
						              break;	    
                }
            }
    if(dir == Roll)
        Rolling();
    if(ok)
        ok = Check();
    if(ok)
        update();
 
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            updBoard[i][j] = ' ';
    for(int i = 0; i <= 51; i++)
        for(int j = 0; j <= 11; j++)
            if(board[i][j] == '1')
                updBoard[i + 1][j] = '1';
 
    ok = Check();
    if(ok)
        update();
    else
        for(int i = 0; i <= 51; i++)
            for(int j = 0; j <= 11; j++)
                if(board[i][j] == '1')
                    board[i][j] = '0', FigureExist = 0;                                               
}
 
void SpawnFigure(){
    TypeScroll = 0;
    FigureExist = 1;
    int id = rand() % 140;
    int type = TypeFigure[id];
    LastFigure = TypeFigure[id];
 
    switch(type){
        case 1:
            board[0][5] = board[1][5] = board[1][6] = board[0][6] = '1';
            break;
        case 2:
            board[0][5] = board[0][6] = board[0][7] = board[0][8] = '1';
            break;
        case 3:
            board[0][6] = board[1][5] = board[1][6] = board[2][6] = '1';
            break;
        case 4:
            board[2][5] = board[1][6] = board[0][6] = board[2][6] = '1';
            break;
        case 5:
            board[2][6] = board[1][5] = board[0][5] = board[2][5] = '1';
            break;
        case 6:
            board[0][5] = board[0][4] = board[1][5] = board[1][6] = '1';
            break;
        case 7:
            board[1][6] = board[1][5] = board[0][6] = board[0][7] = '1';
            break;
    }
}
 
void DrawBoard(){
    system("cls");
    for(int i = 0; i <= 31; i++){
        for(int j = 0; j <= 11; j++){
        	if(board[i][j] == '1' or board[i][j] == '0')
            	cout << char(219);
            else
				        cout << board[i][j];	
        }
        cout << "\n";
    }
    cout <<"\n";
    cout << "\nYour score: " << Score << '\n';
}
 
int main(){
    srand(time(NULL));
 
    for(int i = 0; i <= 31; i++)
        for(int j = 0; j <= 11; j++)
            board[i][j]=' ';
    for(int i = 0; i <= 11; i++)
        board[31][i] = '#';
    for(int i = 0; i <= 31; i++)
        board[i][0] = board[i][11] = '#';
    for(int i = 0; i < 140; i++){
        if(i < 20)
            TypeFigure[i] = 1;
        if(20 <= i and i < 40)
            TypeFigure[i] = 2; 
        if(40 <= i and i < 60)
            TypeFigure[i] = 3; 
        if(60 <= i and i < 80)
            TypeFigure[i] = 4; 
        if(80 <= i and i < 100)
            TypeFigure[i] = 5; 
        if(100 <= i and i < 120)
            TypeFigure[i] = 6; 
        if(120 <= i and i < 140)
            TypeFigure[i] = 7;    
    }
 
    int Step = 0;
    while(true){
        Step++;
        Lose();
        Pause();
        DrawBoard();
        if(!FigureExist){
            Delete();
            SpawnFigure();
        }
        MoveFigure();    
    }   
 
    return 0;
}
