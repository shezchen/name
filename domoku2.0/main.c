#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15
#define CHARSIZE 2

time_t thinking_time;
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);


int human_current_number=-1;
int human_current_char=-1;
int human_first=0;

enum GameMode{human,bot};
enum GameMode mode=human;
enum COLOR{black,white};
enum COLOR player_pic=black;
enum COLOR bot_pic=black;
extern inline long long int unique_evaluate(enum COLOR target_pic,int number,int char_number);
extern int forbidden_check(int number,int num_char);
extern inline long long int min_max(int depth, int search_for_bot, int alpha, int beta);
typedef struct {
    int state;//0：无落子  1：已有黑 2：已有白  3：刚刚黑落子 4：刚刚白落子
    float white_value;//对于白棋的价值
    float black_value;//对于黑棋的价值
    float weight;//位置权重
}position;
//棋盘使用的是GBK编码，每一个中文字符占用2个字节。
//空棋盘模板
/*char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] =
{
    "□□□□□□□□□□□□□□□",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};*/
//此数组存储用于显示的棋盘
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] =
{
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□",
    "□□□□□□□□□□□□□□□"
};
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];

char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲";
char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";
//此数组用于记录当前的棋盘的格局
position arrayForInnerBoardLayout[SIZE][SIZE];
int check_all_pic(){
    //check line
    int black_check = 0,white_check=0;
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            if(arrayForInnerBoardLayout[i][j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[i][j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[i][j].state == 0) {
                black_check=0;
                white_check=0;
            }
        }
        black_check=white_check=0;
    }
    //check row
    for(int j=0;j<SIZE;j++) {
        for(int i=0;i<SIZE;i++) {
            if(arrayForInnerBoardLayout[i][j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[i][j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[i][j].state == 0) {
                black_check=0;
                white_check=0;
            }
        }
        black_check=white_check=0;
    }

    //check /

    for(int i=0,j=0;i<SIZE;i++) {
        int _i=i,_j=j;
        while(_i<SIZE &&_i>=0 && _j<SIZE) {
            if(arrayForInnerBoardLayout[_i][_j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 0) {
                black_check=0;
                white_check=0;
            }
            _i--;
            _j++;
        }
        black_check=white_check=0;
    }
    for(int j=0,i=SIZE-1;j<SIZE;j++) {
        int _i=i,_j=j;
        while(_i<SIZE &&_i>=0 && _j<SIZE) {
            if(arrayForInnerBoardLayout[_i][_j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 0) {
                black_check=0;
                white_check=0;
            }
            _i--;
            _j++;
        }
        black_check=white_check=0;
    }

    //check \

    for(int i=0,j=0;j<SIZE;j++) {
        int _i=i,_j=j;
        while(_i<SIZE && _j<SIZE) {
            if(arrayForInnerBoardLayout[_i][_j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 0) {
                black_check=0;
                white_check=0;
            }
            _i++;
            _j++;
        }
        black_check=white_check=0;
    }
    for(int j=0,i=0;i<SIZE;i++) {
        int _i=i,_j=j;
        while(_i<SIZE && _j<SIZE) {
            if(arrayForInnerBoardLayout[_i][_j].state == 1) {
                white_check=0;
                black_check++;
                if(black_check == 5) {
                    return 1;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 2) {
                black_check=0;
                white_check++;
                if(white_check == 5) {
                    return 2;
                }
            }
            if(arrayForInnerBoardLayout[_i][_j].state == 0) {
                black_check=0;
                white_check=0;
            }
            _i++;
            _j++;
        }
        black_check=white_check=0;
    }
    return 0;//no winner
}

int readinput(int * input_number, char * input_char, char * str) {
    int i=0;
    *input_number=0;
    while(str[i]!='\n' && str[i]!='\0' && i<=9) {
        if(isdigit(str[i])) {
            *input_number=*input_number*10+str[i]-'0';
        }
        if(str[i]>='a' && str[i]<='z') {
            *input_char=str[i];
        }
        if(str[i]>='A' && str[i]<='Z') {
            *input_char=tolower(str[i]);
        }
        i++;
    }
    if(*input_number<=0 || *input_number>=16 || *input_char<'a' || *input_char>'z') {
        return -1;
    }
    return 0;
}
/*void reshape_frost() {
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            arrayForInnerBoardLayout[i][j].weight=0;
        }
    }
}

void frost_break(int n, int c) {
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            arrayForInnerBoardLayout[i][j].weight=0;
        }
    }

    arrayForInnerBoardLayout[n-1][c-1].weight=1;
    arrayForInnerBoardLayout[n-1][c].weight=1;
    arrayForInnerBoardLayout[n-1][c+1].weight=1;
    arrayForInnerBoardLayout[n][c-1].weight=1;
    arrayForInnerBoardLayout[n][c+1].weight=1;
    arrayForInnerBoardLayout[n+1][c-1].weight=1;
    arrayForInnerBoardLayout[n+1][c].weight=1;
    arrayForInnerBoardLayout[n+1][c+1].weight=1;

    arrayForInnerBoardLayout[n-2][c-2].weight=1;
    arrayForInnerBoardLayout[n-2][c-1].weight=1;
    arrayForInnerBoardLayout[n-2][c].weight=1;
    arrayForInnerBoardLayout[n-2][c+1].weight=1;
    arrayForInnerBoardLayout[n-2][c+2].weight=1;
    arrayForInnerBoardLayout[n-1][c-2].weight=1;
    arrayForInnerBoardLayout[n-1][c+2].weight=1;
    arrayForInnerBoardLayout[n][c-2].weight=1;
    arrayForInnerBoardLayout[n][c+2].weight=1;
    arrayForInnerBoardLayout[n+1][c-2].weight=1;
    arrayForInnerBoardLayout[n+1][c+2].weight=1;
    arrayForInnerBoardLayout[n+2][c-2].weight=1;
    arrayForInnerBoardLayout[n+2][c-1].weight=1;
    arrayForInnerBoardLayout[n+2][c].weight=1;
    arrayForInnerBoardLayout[n+2][c+1].weight=1;
    arrayForInnerBoardLayout[n+2][c+2].weight=1;
}
*/
#include "bot.h"
int main()
{

    initRecordBorard();//初始化一个空棋盘
    init_process:
    system("cls");
    printf("Start five_in_row\nEnter 1 for playing with human\nEnter 2 for playing with me:\n");
    int use_number;
    scanf("%d",&use_number);
    if(use_number==1) {
        printf("Human is playing with human\n");
        mode=human;
        system("pause");
        system("cls");
    }
    else if(use_number==2) {
        printf("You are playing with me:\n");
        mode=bot;
        printf("You should enter 1 for black or 2 for white:\n");
        scanf("%d",&use_number);
        if(use_number==1) {player_pic=black;human_first=1;bot_pic=white;}
        else if(use_number==2) {bot_pic=black;player_pic=white;}
    }
    else {goto init_process;}

    system("cls");
    innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
    displayBoard();          //显示棋盘

    int playing=1;
    int input_number;
    char input_char;
    char input[10];

enum COLOR pic=black;
    if(mode==human) {while(playing) {
        play:
        if(pic==black) {printf("Black round \n");}else{printf("White round \n");}
        printf("Please enter number and letter: \n");
        scanf("%s",input);
        int read_state;
        read_state=readinput(&input_number,&input_char,input);
        if(read_state==-1) {
            printf("Wrong input!\n");
            goto play;
        }
        if(arrayForInnerBoardLayout[input_number-1][input_char-'a'].state==0) {arrayForInnerBoardLayout[input_number-1][input_char-'a'].state= pic==black ? 3 : 4 ;}
        else{printf("Wrong input!\n");goto play;}
        innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
        displayBoard();          //显示棋盘
        if(pic==black && forbidden_check(input_number-1,input_char-'a')==1) {
            printf("Break the rule!\n");
            printf("White win! \n");
            break;
        }
        int winner=check_all_pic();
        if(winner==1) {printf("Black win! \n");playing=0;}
        if(winner==2) {printf("White win! \n");playing=0;}
        if(pic==black){pic=white;}else{pic=black;}
    }}
    else {
        while(playing) {
            _play:
            if(pic==bot_pic) {
                int bot_choice_x,bot_choice_y;
                printf("Thinking...\n");
                thinking_time=time(nullptr);
                long long int points=0;
                choice(&bot_choice_x,&bot_choice_y,&points);
                thinking_time=time(nullptr)-thinking_time;
                arrayForInnerBoardLayout[bot_choice_x][bot_choice_y].state= bot_pic==black ? 3 : 4 ;




                innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
                displayBoard();          //显示棋盘
                printf("I chose %d,%c\nThinking time:%llds\n",1+bot_choice_x,bot_choice_y+'a',thinking_time);
                if(points==INT_MIN) {
                    printf("This thinking close to time limit,use default choice.\n");
                }

                printf("correct:%lld\n",points);
            }
            else{
                if(pic==black) {printf("Black(you) round \n");}
                if(pic==white) {printf("White(you) round \n");}
                printf("Please enter number and letter: \n");
                scanf("%s",input);
                int read_state;
                read_state=readinput(&input_number,&input_char,input);
                if(read_state==-1) {
                    printf("Wrong input!\n");
                    goto _play;
                }

                if(arrayForInnerBoardLayout[input_number-1][input_char-'a'].state==0) {
                    human_current_number=input_number-1;
                    human_current_char=input_char-'a';
                    arrayForInnerBoardLayout[input_number-1][input_char-'a'].state= pic==black ? 3 : 4 ;
                }
                else{printf("Wrong input!\n");goto _play;}
                innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
                displayBoard();          //显示棋盘
                if(player_pic==black && forbidden_check(input_number-1,input_char-'a')==1) {
                    printf("Break the rule!\n");
                    printf("White win! \n");
                    break;
                }
            }


            int winner=check_all_pic();
            if(winner==1) {printf("Black win! \n");playing=0;}
            if(winner==2) {printf("White win! \n");playing=0;}
            if(pic==black){pic=white;}else{pic=black;}
        }
    }


    system("pause");
fin:    return 0;
}
//初始化一个空棋盘格局
void initRecordBorard(void){
    //通过双重循环，将arrayForInnerBoardLayout清0
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            arrayForInnerBoardLayout[i][j].state=0;
            arrayForInnerBoardLayout[i][j].white_value=0;
            arrayForInnerBoardLayout[i][j].black_value=0;
            arrayForInnerBoardLayout[i][j].weight=0;

        }
    }
}
//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
    //第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE*CHARSIZE+1;j++) {
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
        }
    }
//第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            if(arrayForInnerBoardLayout[i][j].state!=0) {
                switch(arrayForInnerBoardLayout[i][j].state) {
                    case 1:
                        arrayForDisplayBoard[i][j*CHARSIZE]=play1Pic[0];
                        arrayForDisplayBoard[i][j*CHARSIZE+1]=play1Pic[1];
                    break;
                    case 2:
                        arrayForDisplayBoard[i][j*CHARSIZE]=play2Pic[0];
                        arrayForDisplayBoard[i][j*CHARSIZE+1]=play2Pic[1];
                    break;
                    case 3:
                        arrayForDisplayBoard[i][j*CHARSIZE]=play1CurrentPic[0];
                        arrayForDisplayBoard[i][j*CHARSIZE+1]=play1CurrentPic[1];
                        arrayForInnerBoardLayout[i][j].state-=2;
                    break;
                    case 4:
                        arrayForDisplayBoard[i][j*CHARSIZE]=play2CurrentPic[0];
                        arrayForDisplayBoard[i][j*CHARSIZE+1]=play2CurrentPic[1];
                        arrayForInnerBoardLayout[i][j].state-=2;
                    break;
                }
            }
        }
    }
//注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
}

//显示棋盘格局
void displayBoard(void){
    //第一步：清屏
    system("cls");   //清屏
    //第二步：将arrayForDisplayBoard输出到屏幕上
    for(int i=0;i<SIZE;i++) {
        printf("%2d  ",i+1);
        for(int j=0;j<SIZE;j++) {
            printf("%c",arrayForDisplayBoard[i][j*CHARSIZE]);
            printf("%c",arrayForDisplayBoard[i][j*CHARSIZE+1]);

        }
        printf("\n");
    }

//第三步：输出最下面的一行字母A B ....
printf("    ");
    for(char display_letter='A';display_letter<='O';display_letter++) {
        printf("%c",display_letter);
    }
    printf("\n");
}