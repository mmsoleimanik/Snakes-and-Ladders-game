#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
using namespace std;

// Function to set text color
void SetColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor); // Apply the color
}

//delete thing from string
void deleteInStr(string *str , int id) {
    string strTemp="";
    //to delete id and shift left
    for (int i=0; i<(*str).size(); i++) {
        if ((*str)[i] == (char)(id+'0')) {
            for (int j=i; j<(*str).size(); j++) {
                (*str)[j]=(*str)[j+1];
            }
            break;
        }
    }

    //to reduce lenght
    for (int i=0; i<(*str).size()-1; i++) {
        strTemp += '0';
        strTemp[i] = (*str)[i];
    }
    (*str) = strTemp;
    return;
}

//for define board
string back[10][10] = {
    {"","","go21","","","go25","","go27","",""},
    {"","","","","","","go73","","",""},
    {"go00","","","","","","","","","go09"},
    {"","go81","","go40","","","","","",""},
    {"","","","","","","go66","","","go36"},
    {"","","","","","","","","",""},
    {"go41","","","","","","","","",""},
    {"","","","","","","","go13","",""},
    {"go62","","","go96","","","","","",""},
    {"","","","go86","","","","","go69",""},
};
string front[10][10] = {
    {"L7_ot","","S1_in","","","S2_in","","S3_in","","L8_ot"},
    {"","","","L4_ot","","","S4_in","","",""},
    {"L7_in","S1_ot","","","","S2_ot","","S3_ot","","L8_in"},
    {"","S5_in","","S6_in","","","L6_ot","","",""},
    {"S6_ot","L5_ot","","","","","S7_in","","","L6_in"},
    {"","","","","","","","","",""},
    {"L5_in","","L3_ot","","","","S7_ot","","","L2_ot"},
    {"","","","S4_ot","","","","L4_in","",""},
    {"L3_in","S5_ot","","S8_in","","","L1_ot","","",""},
    {"","","","L1_in","","","S8_ot","","L2_in",""}
};
int number[10][10];
string id[10][10];


struct player {
    int id;
    string name;
    int place[2];
    int number;

    player() {
        id=-1;
        name="-1";
        place[0]=-1; place[1]=-1;
        number = -1;
    }
};
player p[6];



int main() {
    // Define six distinct colors
    const int color[6]={FOREGROUND_RED | FOREGROUND_INTENSITY , FOREGROUND_GREEN | FOREGROUND_INTENSITY , FOREGROUND_BLUE | FOREGROUND_INTENSITY , FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY , FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY , FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
    const int DEFAULT_COLOR = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Default white text
    /*const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
    const int GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;*/

    //to define numbers
    int x=100;
    for (int i=0; i<10; i++) {
        if (i%2==0) {
            for (int j=0; j<10; j++) {
                number[i][j] = x;
                x--;
            }
        }
        else {
            for (int j=9; j>=0; j--) {
                number[i][j] = x;
                x--;
            }
        }
    }

    //for define id
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            id[i][j] = "";
        }
    }

    //for cin player
    int num;
    cout << "how many player do you want? ";
    cin >> num;
    for (int i=0; i<num; i++) {
        cout << "enter the name of player with id of " << i << ": " << endl; 
        cin >> p[i].name;
        p[i].id=i;
        p[i].number = 1;
        p[i].place[0]=9; p[i].place[1]=0;
        id[9][0] = id[9][0] + (char)(i + '0');
    }


    /*srand(static_cast<unsigned int>(time(nullptr)));
    //for tass
    int randomNum = rand();
    int tass = (randomNum%6 == 0 ? 6 : randomNum);*/

    //for cout main board
    for (int i=0; i<10; i++) {
        //first line of row
        for (int j=0; j<10; j++) {
            cout << "[";
            if (id[i][j]!="") {
                for (int k=0; k<id[i][j].size(); k++) {
                    SetColor(color[id[i][j][k]-'0']);
                    cout << id[i][j][k];
                }
                SetColor(DEFAULT_COLOR);
            }
            for (int k=0; k<(9 - id[i][j].size()); k++) {
                cout << " ";
            }
            cout << "]";
        }
        cout << endl;
        //second line of row
        for (int j=0; j<10; j++) {
            cout << "[" << (number[i][j]/10==0 ? "  " : number[i][j]!=100 ? " " : "") << number[i][j] << " ";
            cout << (front[i][j]=="" ? "     " : front[i][j]) << "]";
        }
        cout << endl << endl;
    }




    int randnum;
    int playerTurn=0;
    while (true) {
        cout << "this turn is for " << p[playerTurn].name << ". cin a random number(END GAME CODE = 404): " << endl;
        //for tass
        cin >> randnum;
        //valid for ending game
        if (randnum == 404) {
            break;
        }
        srand(static_cast<unsigned int>(time(nullptr)));
        int randomNum = rand();
        int tass = ( (randomNum+randnum)%6 == 0 ? 6 : (randomNum + randnum)%6 );
        cout << "tass is: " << tass << endl;

        //for movement
        //  move in number
        p[playerTurn].number += tass;
        //  forgot last place
        deleteInStr(&id[p[playerTurn].place[0]][p[playerTurn].place[1]] , playerTurn);
        //  move in the board
        for (int i=0; i<tass; i++) {
            if (p[playerTurn].place[0]%2 == 1) {
                if (p[playerTurn].place[1] == 9) {
                    p[playerTurn].place[0] = p[playerTurn].place[0] - 1;
                }
                else {
                    p[playerTurn].place[1]++;
                }        
            }
            else {
                if (p[playerTurn].place[1] == 0) {
                    p[playerTurn].place[0] = p[playerTurn].place[0] - 1;
                }
                else {
                    p[playerTurn].place[1]--;
                }
            }
        }
        //  move to other cell if there is any snake or letter
        if (back[p[playerTurn].place[0]][p[playerTurn].place[1]] != "") {
            int newRow , newColumn;
            newRow = (int)(back[p[playerTurn].place[0]][p[playerTurn].place[1]][2] - '0');
            newColumn = (int)(back[p[playerTurn].place[0]][p[playerTurn].place[1]][3] - '0');
            p[playerTurn].place[0] = newRow; p[playerTurn].place[1] = newColumn;
            p[playerTurn].number = number[p[playerTurn].place[0]][p[playerTurn].place[1]];
        }
        id[p[playerTurn].place[0]][p[playerTurn].place[1]] += (char)(playerTurn+'0');
        
        

        //for cout main board
        for (int i=0; i<10; i++) {
            //first line of row
            for (int j=0; j<10; j++) {
                cout << "[";
                if (id[i][j]!="") {
                    for (int k=0; k<id[i][j].size(); k++) {
                        SetColor(color[id[i][j][k]-'0']);
                        cout << id[i][j][k];
                    }
                    SetColor(DEFAULT_COLOR);
                }
                for (int k=0; k<(9 - id[i][j].size()); k++) {
                    cout << " ";
                }
                cout << "]";
            }
            cout << endl;
            //second line of row
            for (int j=0; j<10; j++) {
                cout << "[" << (number[i][j]/10==0 ? "  " : number[i][j]!=100 ? " " : "") << number[i][j] << " ";
                cout << (front[i][j]=="" ? "     " : front[i][j]) << "]";
            }
            cout << endl << endl;
        }
        cout << p[playerTurn].name << " moved " << tass << " cell in board.";

        //next player
        playerTurn = (playerTurn == num-1 ? 0 : playerTurn + 1);
    }
    cout << endl << "GAME WAS OVER!!";





    int cmj; cin >> cmj;
    
    return 0;
}