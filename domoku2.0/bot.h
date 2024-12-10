//
// Created by aoyeningluosi on 24-11-24.
//

#ifndef BOT_H
#define BOT_H

#endif //BOT_H

#define MAX_DEPTH 3

#define ONE_SCORE 30
#define TWO_SCORE 100
#define THERE_SCORE 1000
#define FOUR_SCORE 10000
#define FIVE_SCORE 1000000
#define STATE1 10
#define STATE2 3
#define STATE3 3
#define STATE4 2

extern time_t thinking_time;
extern int human_current_number;
extern int human_current_char;

int defend_number, defend_char;
int forbidden_check(int number,int num_char);
int left_whitespace_number=-1,left_whitespace_char=-1;
int right_whitespace_number=-1,right_whitespace_char=-1;


inline void getscore(int cur_state, int fin_state, int in_row_pics,int enemy, int * situation_score,int white_state) {
    if(white_state==0){
        if(cur_state==0 && fin_state==0) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE*STATE1;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE*STATE1;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE*STATE1*5;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE*STATE1*5;
            }
            if(in_row_pics>=5) {
                *situation_score+=FIVE_SCORE*STATE1;
            }


        }
        if(cur_state==0 && (fin_state==enemy || fin_state==-1)) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE*STATE2;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE*STATE2;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE*STATE2;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE*STATE2*2;
            }
            if(in_row_pics>=5) {
                *situation_score+=FIVE_SCORE*STATE2;
            }
        }
        if((cur_state==enemy || cur_state==-1) && fin_state==0) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE*STATE3;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE*STATE3;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE*STATE3;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE*STATE3*2;
            }
            if(in_row_pics>=5) {
                *situation_score+=FIVE_SCORE*STATE3;
            }
        }
        if((cur_state==enemy || cur_state==-1) && (fin_state==enemy || fin_state==-1)) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE*STATE4;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE*STATE4;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE*STATE4;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE*STATE4;
            }
            if(in_row_pics>=5) {
                *situation_score=FIVE_SCORE*STATE4;
            }
        }

    }else {
        if(cur_state==0 && fin_state==0) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE*5;
            }
            if(in_row_pics==5) {
                *situation_score+=FIVE_SCORE*5;
            }
            if(in_row_pics>=6) {
                *situation_score+=FIVE_SCORE*STATE1;
            }

        }

        if(cur_state==0 && (fin_state==enemy || fin_state==-1)) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE;
            }
            if(in_row_pics==5) {
                *situation_score+=FIVE_SCORE;
            }
            if(in_row_pics>=6) {
                *situation_score+=FIVE_SCORE*STATE1;
            }
        }


        if((cur_state==enemy || cur_state==-1) && fin_state==0) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE;
            }
            if(in_row_pics==5) {
                *situation_score+=FIVE_SCORE;
            }
            if(in_row_pics>=6) {
                *situation_score+=FIVE_SCORE*STATE1;
            }
        }
        if((cur_state==enemy || cur_state==-1) && (fin_state==enemy || fin_state==-1)) {
            if(in_row_pics==1) {
                *situation_score+=ONE_SCORE;
            }
            if(in_row_pics==2) {
                *situation_score+=TWO_SCORE;
            }
            if(in_row_pics==3) {
                *situation_score+=THERE_SCORE;
            }
            if(in_row_pics==4) {
                *situation_score+=FOUR_SCORE;
            }
            if(in_row_pics==5) {
                *situation_score=FIVE_SCORE;
            }
            if(in_row_pics>=6) {
                *situation_score+=FIVE_SCORE*STATE1;
            }
        }
    }
}

/*
int evaluate(int n,int c,enum COLOR target_pic) {

    int score=0;

    int target= target_pic==black ? 1 : 2;
    int enemy= target_pic==black ? 2 : 1;
    int copy_n1=n,copy_n2=c,copy_c1=c,copy_c2=c;
    int l_state=-1,r_state=-1;
    //check --
    int in_row=1;
    for(int i=c+1;i<SIZE;i++) {
        if(arrayForInnerBoardLayout[n][i].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[n][i].state==enemy) {
            r_state=enemy;
            break;
        }

    }
    for(int i=c-1;i>=0;i--) {
        if(arrayForInnerBoardLayout[n][i].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[n][i].state==enemy) {
            l_state=enemy;
            break;
        }

    }
    getscore(l_state,r_state,in_row,enemy,&score);
    if(score==INT_MAX)
        return INT_MAX;
    in_row=1;

    //check for |
    l_state=-1;r_state=-1;
    for(int i=n+1;i<SIZE;i++) {
        if(arrayForInnerBoardLayout[i][c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i][c].state==enemy) {
            r_state=enemy;
            break;
        }

    }
    for(int i=n-1;i>=0;i--) {
        if(arrayForInnerBoardLayout[i][c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i][c].state==enemy) {
            l_state=enemy;
            break;
        }

    }
    getscore(l_state,r_state,in_row,enemy,&score);
    if(score==INT_MAX)
        return INT_MAX;
    in_row=1;

    //check for \

    for(int i_n=n+1,i_c=c+1;i_n<SIZE && i_c<SIZE;i_n++,i_c++) {
        if(arrayForInnerBoardLayout[i_n][i_c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i_n][i_c].state==enemy) {
            r_state=enemy;
            break;
        }

    }
    for(int i_n=n-1,i_c=c-1;i_n>=0 && i_c>=0;i_n--,i_c--) {
        if(arrayForInnerBoardLayout[i_n][i_c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i_n][i_c].state==enemy) {
            l_state=enemy;
            break;
        }

    }
    getscore(l_state,r_state,in_row,enemy,&score);
    if(score==INT_MAX)
        return INT_MAX;
    in_row=1;

    //check for /
    for(int i_n=n+1,i_c=c-1;i_n<SIZE && i_c>=0;i_n++,i_c--) {
        if(arrayForInnerBoardLayout[i_n][i_c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i_n][i_c].state==enemy) {
            l_state=enemy;
            break;
        }

    }
    for(int i_n=n-1,i_c=c+1;i_n>=0 && i_c<SIZE;i_n--,i_c++) {
        if(arrayForInnerBoardLayout[i_n][i_c].state==target) {
            in_row++;
        }
        if(arrayForInnerBoardLayout[i_n][i_c].state==enemy) {
            r_state=enemy;
            break;
        }

    }
    getscore(l_state,r_state,in_row,enemy,&score);
    if(score==INT_MAX)
        return INT_MAX;
    in_row=1;
    return score;
}
*/

/*int forbidden_check(int number,int num_char) {
    //检测长连
    if(six_in_row(number,num_char)==1)
        return 1;

}
int double_three(int number,int num_char) {
    int ptr_number=number,ptr_char=num_char;
    int in_row_pics=0;
    int have_three=0;
    int have_four
    int left_empty=-1,right_empty=-1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_char>=0) {
        ptr_char--;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        left_empty=1;
    }
    ptr_char=num_char+1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_char<SIZE) {
        ptr_char++;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        right_empty=1;
    }
    if(in_row_pics==3 && left_empty==1 && right_empty==1) {
        have_three++;
    }
    if(in_row_pics==4 && left_empty==1 && right_empty==1) {
        have_three++;
    }
}*/

inline int forbidden_check(int number,int num_char){
    int ptr_number=number,ptr_char=num_char;
    int in_row_pics=0;
    int have_three=0;
    int have_four=0;
    int left_empty=-1,right_empty=-1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_char>=0) {
        ptr_char--;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        left_empty=1;
    }
    ptr_char=num_char+1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_char<SIZE) {
        ptr_char++;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        right_empty=1;
    }

    if(in_row_pics>=6) {
        return 1;//长连
    }
    if(in_row_pics==3 && left_empty==1 && right_empty==1) {
        have_three++;//活三
        if(have_three==2){return 1;}
    }
    if(in_row_pics==4 && (left_empty==1 || right_empty==1)) {
        have_four++;//冲四或活四
        if(have_four==2){return 1;}
    }

    ptr_number=number,ptr_char=num_char;
    in_row_pics=0;
    have_three=0;
    have_four=0;
    left_empty=-1,right_empty=-1;

    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number>=0) {
        ptr_number--;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        left_empty=1;
    }
    ptr_number=number+1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number<SIZE) {
        ptr_number++;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        right_empty=1;
    }

    if(in_row_pics>=6) {
        return 1;//长连
    }
    if(in_row_pics==3 && left_empty==1 && right_empty==1) {
        have_three++;//活三
        if(have_three==2){return 1;}
    }
    if(in_row_pics==4 && (left_empty==1 || right_empty==1)) {
        have_four++;//冲四或活四
        if(have_four==2){return 1;}
    }

    ptr_number=number,ptr_char=num_char;
    in_row_pics=0;
    have_three=0;
    have_four=0;
    left_empty=-1,right_empty=-1;


    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number>=0 && ptr_char>=0) {
        ptr_number--;
        ptr_char--;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        left_empty=1;
    }
    ptr_number=number+1;
    ptr_char=num_char+1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number<SIZE && ptr_char<SIZE) {
        ptr_number++;
        ptr_char++;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        right_empty=1;
    }


    if(in_row_pics>=6) {
        return 1;//长连
    }
    if(in_row_pics==3 && left_empty==1 && right_empty==1) {
        have_three++;//活三
        if(have_three==2){return 1;}
    }
    if(in_row_pics==4 && (left_empty==1 || right_empty==1)) {
        have_four++;//冲四或活四
        if(have_four==2){return 1;}
    }

    ptr_number=number,ptr_char=num_char;
    in_row_pics=0;
    have_three=0;
    have_four=0;
    left_empty=-1,right_empty=-1;

    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number>=0 && ptr_char<SIZE) {
        ptr_number--;
        ptr_char++;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        left_empty=1;
    }
    ptr_number=number+1;
    ptr_char=num_char-1;
    while(arrayForInnerBoardLayout[ptr_number][ptr_char].state==1 && ptr_number<SIZE && ptr_char>=0) {
        ptr_number++;
        ptr_char--;
        in_row_pics++;
    }
    if(arrayForInnerBoardLayout[ptr_number][ptr_char].state==0) {
        right_empty=1;
    }
    if(in_row_pics>=6) {
        return 1;//长连
    }
    if(in_row_pics==3 && left_empty==1 && right_empty==1) {
        have_three++;//活三
        if(have_three==2){return 1;}
    }
    if(in_row_pics==4 && (left_empty==1 || right_empty==1)) {
        have_four++;//冲四或活四
        if(have_four==2){return 1;}
    }
    return 0;

}


/*inline long long int evaluate(enum COLOR target_pic) {

    /*int situation_score = check_all_pic();
    if(target_pic==black) {
        if(situation_score==1)
            return 1000000;
        if(situation_score==2)
            return -1000000;
    }else {
        if(situation_score==1)
            return -1000000;
        if(situation_score==2)
            return 1000000;
    }
    int situation_score=0;
    int cur_state=-1,fin_state=0;

    int enemy,bot;
    if(target_pic==black) {
        enemy=2;bot=1;
    }else {
        enemy=1;bot=2;
    }

    //check --
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int temp_j=0;
            if(arrayForInnerBoardLayout[i][j].state==0) {
                cur_state=0;
                continue;
            }
            if(arrayForInnerBoardLayout[i][j].state==enemy) {
                cur_state=enemy;
                continue;
            }
            if(arrayForInnerBoardLayout[i][j].state==bot) {
                int in_row_pics=1;

                    for (temp_j=j+1;temp_j<SIZE;temp_j++) {
                        if(arrayForInnerBoardLayout[i][temp_j].state==bot) {
                            in_row_pics++;
                        }
                        if(arrayForInnerBoardLayout[i][temp_j].state==enemy) {
                            fin_state=enemy;
                            break;
                        }
                        if(arrayForInnerBoardLayout[i][temp_j].state==0) {
                            fin_state=0;
                            break;
                        }
                    }
                    if(temp_j==SIZE) {
                        fin_state=-1;
                        j=temp_j;
                    }else {
                        j=temp_j;
                        cur_state=arrayForInnerBoardLayout[i][temp_j].state;
                    }

                    getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);


                }


            }
        }


//check |
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                int temp_i=0;
                if(arrayForInnerBoardLayout[i][j].state==0) {
                    cur_state=0;
                    continue;
                }
                if(arrayForInnerBoardLayout[i][j].state==enemy) {
                    cur_state=enemy;
                    continue;
                }
                if(arrayForInnerBoardLayout[i][j].state==bot) {
                    int in_row_pics=1;

                        for (temp_i=i+1;temp_i<SIZE;temp_i++) {
                            if(arrayForInnerBoardLayout[temp_i][j].state==bot) {
                                in_row_pics++;
                            }
                            if(arrayForInnerBoardLayout[temp_i][j].state==enemy) {
                                fin_state=enemy;
                                break;
                            }
                            if(arrayForInnerBoardLayout[temp_i][j].state==0) {
                                fin_state=0;
                                break;
                            }
                        }
                        if(temp_i==SIZE) {
                            fin_state=-1;
                            i=temp_i;
                        }else {
                            i=temp_i;
                            cur_state=arrayForInnerBoardLayout[temp_i][j].state;
                        }
                        getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);


                    }


                }
            }

//check \

    for(int j=SIZE-1;j>=0;j--) {
        for(int lean_i=0,lean_j=j;lean_i<SIZE && lean_j<SIZE;lean_i++,lean_j++) {
            int temp_i=0,temp_j=0;
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==0) {
                cur_state=0;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==enemy) {
                cur_state=enemy;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==bot) {
                int in_row_pics=1;

                for (temp_i=lean_i+1,temp_j=lean_j+1;temp_i<SIZE && temp_j<SIZE;temp_i++,temp_j++) {
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==bot) {
                        in_row_pics++;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==enemy) {
                        fin_state=enemy;
                        break;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==0) {
                        fin_state=0;
                        break;
                    }
                }
                if(temp_i==SIZE || temp_j==SIZE) {
                    fin_state=-1;
                    lean_i=temp_i;
                    lean_j=temp_j;
                }else {
                    lean_i=temp_i;
                    lean_j=temp_j;
                    cur_state=arrayForInnerBoardLayout[temp_i][temp_j].state;
                }
                getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);

            }
        }
    }
        for(int i=0;i<SIZE;i++) {
            for(int lean_i=i,lean_j=0;lean_i<SIZE && lean_j<SIZE;lean_i++,lean_j++) {
                int temp_i=0,temp_j=0;
                if(arrayForInnerBoardLayout[lean_i][lean_j].state==0) {
                    cur_state=0;
                    continue;
                }
                if(arrayForInnerBoardLayout[lean_i][lean_j].state==enemy) {
                    cur_state=enemy;
                    continue;
                }
                if(arrayForInnerBoardLayout[lean_i][lean_j].state==bot) {
                    int in_row_pics=1;

                        for (temp_i=lean_i+1,temp_j=lean_j+1;temp_i<SIZE && temp_j<SIZE;temp_i++,temp_j++) {
                            if(arrayForInnerBoardLayout[temp_i][temp_j].state==bot) {
                                in_row_pics++;
                            }
                            if(arrayForInnerBoardLayout[temp_i][temp_j].state==enemy) {
                                fin_state=enemy;
                                break;
                            }
                            if(arrayForInnerBoardLayout[temp_i][temp_j].state==0) {
                                fin_state=0;
                                break;
                            }
                        }
                        if(temp_i==SIZE || temp_j==SIZE) {
                            fin_state=-1;
                            lean_i=temp_i;
                            lean_j=temp_j;
                        }else {
                            lean_i=temp_i;
                            lean_j=temp_j;
                            cur_state=arrayForInnerBoardLayout[temp_i][temp_j].state;
                        }
                        getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);

                }
            }
        }



    //check /

    for(int j=0;j<SIZE;j++) {
        for(int lean_i=0,lean_j=j;lean_i<SIZE && lean_j>=0;lean_i++,lean_j--) {
            int temp_i=0,temp_j=0;
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==0) {
                cur_state=0;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==enemy) {
                cur_state=enemy;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==bot) {
                int in_row_pics=1;

                for (temp_i=lean_i+1,temp_j=lean_j-1;temp_i<SIZE && temp_j>=0;temp_i++,temp_j--) {
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==bot) {
                        in_row_pics++;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==enemy) {
                        fin_state=enemy;
                        break;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==0) {
                        fin_state=0;
                        break;
                    }
                }
                if(temp_i==SIZE || temp_j==-1) {
                    fin_state=-1;
                    lean_i=temp_i;
                    lean_j=temp_j;
                }else {
                    lean_i=temp_i;
                    lean_j=temp_j;
                    cur_state=arrayForInnerBoardLayout[temp_i][temp_j].state;
                }
                getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);

            }
        }
    }
    for(int i=0;i<SIZE;i++) {
        for(int lean_j=SIZE-1,lean_i=i;lean_j>=0 && lean_i<SIZE;lean_i++,lean_j--) {
            int temp_i=0,temp_j=0;
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==0) {
                cur_state=0;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==enemy) {
                cur_state=enemy;
                continue;
            }
            if(arrayForInnerBoardLayout[lean_i][lean_j].state==bot) {
                int in_row_pics=1;

                for (temp_i=lean_i+1,temp_j=lean_j-1;temp_i<SIZE && temp_j>=0;temp_i++,temp_j--) {
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==bot) {
                        in_row_pics++;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==enemy) {
                        fin_state=enemy;
                        break;
                    }
                    if(arrayForInnerBoardLayout[temp_i][temp_j].state==0) {
                        fin_state=0;
                        break;
                    }
                }
                if(temp_i==SIZE || temp_j==-1) {
                    fin_state=-1;
                    lean_i=temp_i;
                    lean_j=temp_j;
                }else {
                    lean_i=temp_i;
                    lean_j=temp_j;
                    cur_state=arrayForInnerBoardLayout[temp_i][temp_j].state;
                }
                getscore(cur_state,fin_state,in_row_pics,enemy,&situation_score);

            }
        }
    }
    return situation_score;


}*/
inline long long int unique_evaluate(enum COLOR target_pic,int number,int char_number) {
    int situation_score=0;
    int alpha_state=-1,beta_state=-1;

    int enemy,bot;
    if(target_pic==black) {
        enemy=2;bot=1;
    }else {
        enemy=1;bot=2;
    }
    int pics_in_row=0;
    int sm_number,sm_char;
    //检测附近的连子
    //check --
    int white_state=0;//没有遇到空白为0，遇到一次空白为-1，-1状态下再遇到棋子为1
    sm_number=number;
    sm_char=char_number-1;
    for(pics_in_row=1;sm_char>=0;sm_char--) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {

            alpha_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                alpha_state=0;
                break;
            }
            if(white_state==1) {
                alpha_state=0;
                break;
            }
        }
    }
    sm_number=number;
    sm_char=char_number+1;
    for(;sm_char<SIZE;sm_char++) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            beta_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                beta_state=0;
                break;
            }
            if(white_state==1) {
                beta_state=0;
                break;
            }
        }
    }
    getscore(alpha_state,beta_state,pics_in_row,enemy,&situation_score,white_state);


    //check |
    white_state=0;
    alpha_state=beta_state=-1;
    sm_number=number-1;
    sm_char=char_number;
    for(pics_in_row=1;sm_number>=0;sm_number--) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            alpha_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                alpha_state=0;
                break;
            }
            if(white_state==1) {
                alpha_state=0;
                break;
            }
        }
    }
    sm_number=number+1;
    sm_char=char_number;
    for(;sm_number<SIZE;sm_number++) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            beta_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                beta_state=0;
                break;
            }
            if(white_state==1) {
                beta_state=0;
                break;
            }
        }
    }
    getscore(alpha_state,beta_state,pics_in_row,enemy,&situation_score,white_state);

    //check \
    white_state=0;
    alpha_state=beta_state=-1;
    sm_number=number-1;
    sm_char=char_number-1;
    for(pics_in_row=1;sm_number>=0 && sm_char>=0;sm_number--,sm_char--) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            alpha_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                alpha_state=0;
                break;
            }
            if(white_state==1) {
                alpha_state=0;
                break;
            }
        }
    }
    sm_number=number+1;
    sm_char=char_number+1;
    for(;sm_number<SIZE && sm_char<SIZE;sm_number++,sm_char++) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            beta_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                beta_state=0;
                break;
            }
            if(white_state==1) {
                beta_state=0;
                break;
            }
        }
    }
    getscore(alpha_state,beta_state,pics_in_row,enemy,&situation_score,white_state);

    //check /
    white_state=0;
    alpha_state=beta_state=-1;
    sm_number=number+1;
    sm_char=char_number-1;
    for(pics_in_row=1;sm_number<SIZE && sm_char>=0;sm_number++,sm_char--) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            alpha_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                alpha_state=0;
                break;
            }
            if(white_state==1) {
                alpha_state=0;
                break;
            }
        }
    }
    sm_number=number-1;
    sm_char=char_number+1;
    for(;sm_number>=0 && sm_char<SIZE;sm_number--,sm_char++) {
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==bot) {
            if(white_state==-1) {
                white_state=1;
            }
            pics_in_row++;
            continue;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==enemy) {
            beta_state=enemy;
            break;
        }
        if(arrayForInnerBoardLayout[sm_number][sm_char].state==0) {
            if(white_state==0) {
                white_state=-1;
                continue;
            }
            if(white_state==-1) {
                beta_state=0;
                break;
            }
            if(white_state==1) {
                beta_state=0;
                break;
            }
        }
    }
    getscore(alpha_state,beta_state,pics_in_row,enemy,&situation_score,white_state);
    return situation_score;
}

inline long long int min_max(int depth, int search_for_bot, int alpha, int beta) {

    if(depth==MAX_DEPTH) {/*long long int bot_val=evaluate(bot_pic);
        long long int enemy_val=evaluate(player_pic);return bot_val-enemy_val;*/
    return 0;}


    if (search_for_bot) {
        long long int best = INT_MIN;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                    //选择一个落点为了让alpha最大
                    if (arrayForInnerBoardLayout[i][j].state == 0) {
                        arrayForInnerBoardLayout[i][j].state = bot_pic==black?1:2;

                        if(bot_pic==black && forbidden_check(i,j)==1) {
                            arrayForInnerBoardLayout[i][j].state = 0;//收回落子
                            continue;
                        }
                        long long int temp=min_max(depth + 1, !search_for_bot, alpha, beta)+unique_evaluate(bot_pic,i,j);
                        alpha = alpha>=temp?alpha:temp;

                        arrayForInnerBoardLayout[i][j].state = 0;//收回落子
                        if (beta <= alpha)
                            goto rtn1;
                    }


            }
        }
        rtn1:return alpha;
    } else {
        //对手的回合，选择一个落点为了让beta最小
        long long int best = INT_MAX;

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    if (arrayForInnerBoardLayout[i][j].state == 0) {
                        arrayForInnerBoardLayout[i][j].state = player_pic==black?1:2;
                        ;
                        if(player_pic==black && forbidden_check(i,j)==1) {
                            arrayForInnerBoardLayout[i][j].state = 0;//收回落子
                            continue;
                        }
                        long long int temp=min_max(depth + 1, !search_for_bot, alpha, beta)-unique_evaluate(player_pic,i,j);

                        beta = beta<=temp?beta:temp;// 取最小值,  尽可能降低beta
                        arrayForInnerBoardLayout[i][j].state = 0;//收回落子
                        if (beta <= alpha)
                            goto rtn2;
                    }
                }
            }
            rtn2:return beta;
        }
}



void choice(int *i,int *j,long long int *points) {

        {
            if(human_current_number==-1 && human_current_char==-1) {
                *i=7;
                *j=7;
                human_current_number=0;
                return;//第一步应该在中间
            }
            if(human_first==1) {
                if(human_current_number-1>=0) {
                    *i=human_current_number-1;
                    *j=human_current_char;
                    human_first=0;
                    return;
                }
                if(human_current_number+1<SIZE) {
                    *i=human_current_number+1;
                    *j=human_current_char;
                    human_first=0;
                    return;
                }
                if(human_current_char-1>=0) {
                    *i=human_current_number;
                    *j=human_current_char-1;
                    human_first=0;
                    return;
                }
                if(human_current_char+1<SIZE) {
                    *i=human_current_number;
                    *j=human_current_char+1;
                    human_first=0;
                    return;
                }
            }


            long long int bestVal = INT_MIN;
            if(bot_pic==black){
                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 1;
                            //frost_break(i__,j__);
                            if(check_all_pic()==1 && forbidden_check(i__,j__)==0) {
                                arrayForInnerBoardLayout[i__][j__].state = 0;
                                *i = i__;
                                *j = j__;
                                *points=INT_MAX;
                                return;
                            }
                            arrayForInnerBoardLayout[i__][j__].state = 0;
                        }
                    }
                }

                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 2;
                            //frost_break(i__,j__);

                            if(check_all_pic()==2) {
                                arrayForInnerBoardLayout[i__][j__].state = 0;
                                *i = i__;
                                *j = j__;
                                return;
                            }
                            arrayForInnerBoardLayout[i__][j__].state = 0;
                        }
                    }
                }
                //if bot is black
                int pre_i=0,pre_j=0;
                long long int moveVal;
                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        // Check if this place is empty
                        if (arrayForInnerBoardLayout[i__][j__].state == 0 && forbidden_check(i__,j__)==0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 1;
                            //frost_break(i__,j__);
                            if(forbidden_check(i__,j__)==1) {
                                moveVal=INT_MIN;
                            }else {
                                moveVal=unique_evaluate(bot_pic,i__,j__)+min_max(1, 0, INT_MIN, INT_MAX);
                            }
                            // Compute evaluation function for this move
                            // Undo the move
                            arrayForInnerBoardLayout[i__][j__].state = 0;
                            // If the value of the current move is more than the best value, update best
                            if (moveVal > bestVal) {
                                pre_i = i__;
                                pre_j = j__;
                                bestVal = moveVal;
                            }
                        }
                    }
                }
                bestVal=INT_MIN;
                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if(time(nullptr)-thinking_time>=9) {
                            *i = pre_i;
                            *j = pre_j;
                            bestVal = INT_MIN;
                            goto end;
                        }

                        // Check if this place is empty
                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 1;
                            //frost_break(i__,j__);


                            if(forbidden_check(i__,j__)==1) {
                                moveVal=INT_MIN;
                            }else {
                                moveVal=unique_evaluate(bot_pic,i__,j__)+min_max(0, 0, INT_MIN, INT_MAX);
                            }

                            // Compute evaluation function for this move
                            // Undo the move
                            arrayForInnerBoardLayout[i__][j__].state = 0;

                            // If the value of the current move is more than the best value, update best
                            if (moveVal > bestVal) {
                                *i = i__;
                                *j = j__;
                                bestVal = moveVal;
                            }
                        }
                    }
                }
            }else {
                //if bot is white

                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 2;
                            //frost_break(i__,j__);
                            if(check_all_pic()==2) {
                                arrayForInnerBoardLayout[i__][j__].state = 0;
                                *i = i__;
                                *j = j__;
                                *points=INT_MAX;
                                return;
                            }
                            arrayForInnerBoardLayout[i__][j__].state = 0;
                        }
                    }
                }

                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 1;
                            //frost_break(i__,j__);
                            if(check_all_pic()==1 && forbidden_check(i__,j__)==0) {
                                arrayForInnerBoardLayout[i__][j__].state = 0;
                                *i = i__;
                                *j = j__;
                                return;
                            }
                            arrayForInnerBoardLayout[i__][j__].state = 0;
                        }
                    }
                }
                int pre_i=0,pre_j=0;
                long long int moveVal;
                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        // Check if this place is empty

                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 2;
                            //frost_break(i__,j__);

                            // Compute evaluation function for this move
                            moveVal=unique_evaluate(bot_pic,i__,j__)+min_max(1, 0, INT_MIN, INT_MAX);

                            // Undo the move
                            arrayForInnerBoardLayout[i__][j__].state = 0;

                            // If the value of the current move is more than the best value, update best
                            if (moveVal > bestVal) {
                                pre_i = i__;
                                pre_j = j__;
                                bestVal = moveVal;
                            }
                        }
                    }
                }
                bestVal=INT_MIN;
                for (int i__ = 0; i__ < SIZE; i__++) {
                    for (int j__ = 0; j__ < SIZE; j__++) {
                        if(time(nullptr)-thinking_time>=9) {
                            *i = pre_i;
                            *j = pre_j;
                            bestVal = INT_MIN;
                            goto end;
                        }
                        // Check if this place is empty

                        if (arrayForInnerBoardLayout[i__][j__].state == 0) {
                            // Make the move
                            arrayForInnerBoardLayout[i__][j__].state = 2;
                            //frost_break(i__,j__);

                            // Compute evaluation function for this move
                            moveVal = unique_evaluate(bot_pic,i__,j__)+min_max(0, 0, INT_MIN, INT_MAX);

                            // Undo the move
                            arrayForInnerBoardLayout[i__][j__].state = 0;

                            // If the value of the current move is more than the best value, update best
                            if (moveVal > bestVal) {
                                *i = i__;
                                *j = j__;
                                bestVal = moveVal;
                            }
                        }
                    }
                }
            }
            end:*points=bestVal;

        }
    }



