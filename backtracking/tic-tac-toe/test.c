#include <stdio.h>
#include <stdlib.h>

#define CPU 1
#define PLAYER 2
#define INF 0x3f3f3f3f

int game[3][3]={};

int max(int a, int b) {
    return a>b?a:b;
}

int min(int a, int b) {
    return a<b?a:b;
}


void print(int game[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(game[i][j]!=0) putchar(game[i][j]==1?'X':'O');
            else putchar('-');
            putchar(j==2?'\n': ' ');
        }
    }
}

int ended(int game[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=1;j<3;j++){
            if(game[i][j]&&game[i][j]==game[i][j-1]) {} 
            else {break;}

            if(j==2) return game[i][j];
        }
    }

    for(int i=0;i<3;i++){
        for(int j=1;j<3;j++){
            if(game[j][i]&&game[j][i]==game[j-1][i]) {} 
            else {break;}

            if(j==2) return game[j][i];
        }
    }

    for(int i=1;i<3;i++){
        if(game[i][i]&&game[i][i]==game[i-1][i-1]) {} 
        else {break;}

        if(i==2) return game[i][i];
    }

    for(int i=1;i<3;i++){
        if(game[2-i][i]&&game[2-i][i]==game[2-(i-1)][i-1]) {} 
        else {break;}

        if(i==2) return game[2-i][i];
    }

    return 0;
}

int search(int isMaxing, int game[3][3], int depth) {
    
    int end = ended(game);
    if(end==PLAYER) {
        return -10+depth;
    } else if(end==CPU) {
        return 10-depth;
    }

    int score = 0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(!game[i][j]){
                game[i][j]=isMaxing?CPU:PLAYER;
                score += search(1-isMaxing,game,1+depth);
                game[i][j]=0;
            }
        }
    }

    return score;
}

void get_best(int game[3][3], int* a, int* b) {
    int best=-INF,x=0,y=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(!game[i][j]){
                game[i][j]=CPU;
                int s = search(0,game,0);
                if(s>best){
                    best=s;
                    x=i;
                    y=j;
                }
                game[i][j]=0;
            }
        }
    }

    *a=x;
    *b=y;
}

void play(int who, int game[3][3]) {

    if(ended(game)) {
        print(game);
        printf("%s won\n",3-who==PLAYER?"Human":"CPU");
        return;
    }

    int x,y;

    if(who==PLAYER) {
        print(game);
        printf("It's your's turn\nType your next move (x,y): " );
        scanf("%d%d",&x,&y);
    } else {
        printf("score %d\n",search(who,game,0));
        //scanf("%d%d",&x,&y); /* tmp */
        get_best(game,&x,&y);
    }

    if(!game[x][y]) {
        game[x][y]=who;
        play(3-who,game);
    } else {
        printf("You can't do that\n");
        play(who,game);
    }
}

int main() {

    system("clear");
    play(1,game);

    return 0;
}
