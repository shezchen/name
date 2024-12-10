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
    int state;//0��������  1�����к� 2�����а�  3���ոպ����� 4���ոհ�����
    float white_value;//���ڰ���ļ�ֵ
    float black_value;//���ں���ļ�ֵ
    float weight;//λ��Ȩ��
}position;
//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�
//������ģ��
/*char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] =
{
    "������������������������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "�ĩ��������������",
    "���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};*/
//������洢������ʾ������
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] =
{
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������",
    "������������������������������"
};
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];

char play1Pic[]="��";//������;
char play1CurrentPic[]="��";
char play2Pic[]="��";//������;
char play2CurrentPic[]="��";
//���������ڼ�¼��ǰ�����̵ĸ��
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

    initRecordBorard();//��ʼ��һ��������
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
    innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
    displayBoard();          //��ʾ����

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
        innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
        displayBoard();          //��ʾ����
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




                innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
                displayBoard();          //��ʾ����
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
                innerLayoutToDisplayArray();  //�����е�����ת��������ʾ������
                displayBoard();          //��ʾ����
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
//��ʼ��һ�������̸��
void initRecordBorard(void){
    //ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE;j++) {
            arrayForInnerBoardLayout[i][j].state=0;
            arrayForInnerBoardLayout[i][j].white_value=0;
            arrayForInnerBoardLayout[i][j].black_value=0;
            arrayForInnerBoardLayout[i][j].weight=0;

        }
    }
}
//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
void innerLayoutToDisplayArray(void){
    //��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��
    for(int i=0;i<SIZE;i++) {
        for(int j=0;j<SIZE*CHARSIZE+1;j++) {
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
        }
    }
//�ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
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
//ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
}

//��ʾ���̸��
void displayBoard(void){
    //��һ��������
    system("cls");   //����
    //�ڶ�������arrayForDisplayBoard�������Ļ��
    for(int i=0;i<SIZE;i++) {
        printf("%2d  ",i+1);
        for(int j=0;j<SIZE;j++) {
            printf("%c",arrayForDisplayBoard[i][j*CHARSIZE]);
            printf("%c",arrayForDisplayBoard[i][j*CHARSIZE+1]);

        }
        printf("\n");
    }

//������������������һ����ĸA B ....
printf("    ");
    for(char display_letter='A';display_letter<='O';display_letter++) {
        printf("%c",display_letter);
    }
    printf("\n");
}