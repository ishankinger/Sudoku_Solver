#include<stdio.h>
#include<stdlib.h>

char board[9][9]={                                                         // AN EMPTY 2-D ARRAY OF CHARACTERS IS DEFINED
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
};

void boardPrint(int rows,int columns,char board[rows][columns]){        // FUNCTION TO PRINT THE BOARD
    printf("    ");
    for(int i=48;i<48+columns;i++){
        printf("\033[1;36m");
        printf(" %c  ",i);
        printf("\033[0m");
    }
    printf("\n   %c",201);
    for(int i=0;i<columns-1;i++) {
        if((i+1)%3==0) printf("%c%c%c%c",205,205,205,203);
        else printf("%c%c%c%c",205,205,205,209);
    }
    printf("%c%c%c%c\n",205,205,205,187);
    for(int i=0;i<rows;i++){
        printf("\033[1;36m");
        printf(" %c ",65+i);
        printf("\033[0m");
        printf("%c",179);
        for(int j=0;j<columns;j++) {
            if((j+1)%3==0){
                printf("\033[1;34m");
                printf(" %c ",board[i][j]);
                printf("\033[0m");
                printf("%c",186);
            }
            else{
                printf("\033[1;34m");
                printf(" %c ",board[i][j]);
                printf("\033[0m");
                printf("%c",179);
            }
        }
        if(i!=rows-1){
            if((i+1)%3==0){
                printf("\n   %c",204);
                for(int k=0;k<columns-1;k++){
                    if ((k+1)%3==0) printf("%c%c%c%c",205,205,205,206);
                    else printf("%c%c%c%c",205,205,205,216);
                }
                printf("%c%c%c%c\n",205,205,205,185);
            }
            else{
                printf("\n   %c",199);
                for(int k=0;k<columns-1;k++){
                    if ((k+1)%3==0) printf("%c%c%c%c",196,196,196,215);
                    else printf("%c%c%c%c",196,196,196,197);
                }
                printf("%c%c%c%c\n",196,196,196,182);
            }            
        }else{
            printf("\n   %c",200);
            for(int k=0;k<columns-1;k++){
                if((k+1)%3==0) printf("%c%c%c%c",205,205,205,202);
                else printf("%c%c%c%c",205,205,205,207);
            }
            printf("%c%c%c%c\n",205,205,205,188);
        }
    }
}

void inputSudoku(){                                                   // FUNCTION TO TAKE INPUT FROM USER
    boardPrint(9,9,board);                                            // FIRST THE EMPTY BOARD WILL PRINT
    printf("\033[1;33m");                                             // THIS WILL GIVE COLOR
    printf("Enter the coordinates\nWhen done with input write");      // THEN ASK FOR INPUT
    printf("\033[1;34m");                                           
    printf(" 'complete'\n"); 
    printf("\033[0m");                                                // THIS WILL TERMINATE THE COLOR
    while(1){                                                         // GOING IN A LOOP FOR TAKING INPUT
        char arr[5];
        scanf("%s",&arr);
        int k=(arr[0]-'c');                                           // THIS WILL CHECK COMPLETE WRITTEN OR NOT
        if(k==0) break;                                               // IF YES THEN BREAK FROM LOOP
        else{
            int rw=arr[0]-'A';                                        // ROW AND COL CONVERT FROM CHAR TO INT
            int cl=arr[1]-'0';
            char chr=arr[2];                                          // CHAR SAME
            board[rw][cl]=chr;                                        // THEN PUT VALUE
        }
        system("cls");                                                // THIS WILL DELETE THE PREVIOUS BOARD
        boardPrint(9,9,board);                                        // NOW PRINT MODIFIED BOARD

    }
}

int isSafe(char board[][9],int row, int col, int number){             // FUNCTION TO CHECK WHETHER ELEMENT CAN BE INSERTED OR NOT
    char c=number+'0';                                                // FIRST MAKE IT A CHARACTER
    for(int i=0;i<9;i++){                                             // CHECK ROW-WISE THAT ANY ELEMENT PRESENT OF SAME VALUE
        if(board[i][col]==c){                                         // IF YES THEN RETURN 0 MEANS FALSE
            return 0;
        }
    }
    for(int j=0;j<9;j++){                                             // SAME AS ROWS CHECK COLUMN WISE
        if(board[row][j]==c){
            return 0;
        }
    }
    int sr=3*(row/3);                                                 // THIS GIVE OUS VALUE OF OUR CORNER ELEMENT OF GRID ROW WISE
    int sc=3*(col/3);                                                 // THIS COLUMNWISE
    for(int i=sr;i<sr+3;i++){                                         // GOING IN NESTED LOOP TO CHECK WHETHER IN GRID THE ELEMENT PRESENT
        for(int j=sc;j<sc+3;j++){
            if(board[i][j]==c){
                return 0;
            }
        }
    }
    return 1;                                                         // IF NOTHING RETURN TILL MEANS SAFE HENCE RETURN 1 MEANS TRUE
}
int helper(char board[][9],int row,int col){                          // THIS WILL INSERT THE VALUE IN THE BOARD
    if(row==9){                                                       
        return 1;
    }
    int nrow=0;                                                       // MAKING VARIABLE FOR NEXT ROW AND NEXT COL TO CHECK
    int ncol=0;
    if(col==8){                                                       // MEANS WE ARE AT END SO MOVE TO NEXT ROW FROM 0 COLUMN
        nrow=row+1;
        ncol=0;
    }
    else{
        nrow=row;                                                     // ELSE SAME ROW MOVE COLUMN
        ncol=col+1;
    }
    if(board[row][col]!='.'){                                         // IF BOARD IS NOT EMPTY
        if(helper(board,nrow,ncol)){                                  // THEN CALL FOR NEXT ROW AND NEXT COLUMN
            return 1;                                                 // IF THAT CALL RETURNS 1 THEN IT WILL RETURN 1 ALSO AS IT IS
        }                                                             // ALREADY FILLED
    }
    else{                                                             // ELSE IF ELEMENT IS PRESENT
        for(int i=1;i<=9;i++){                                        // GO IN LOOP FROM 1 TO 9 
            if(isSafe(board,row,col,i)){                              // CHECK CONDITION FOR EACH 1 TO 9
                char c=i+'0';                                         // IF TRUE THEN INSERT THAT INTEGER IN IT
                board[row][col]=c;                                    // ALSO MAKE INT TO CHAR
                if(helper(board,nrow,ncol)){                          // NOW CALL FOR SAME THING FOR NEXT BLOCK
                    return 1;                                         // IF THAT CALL RETURN 1 THEN THIS WILL ALSO RETURN 1
                }
                else{
                    board[row][col]='.';                              // ELSE MEANS THERE IS SOME ISSUE PLACING IT SO MAKE IT AGAIN EMPTY
                }
            }
        }
    }
    return 0;                                                          // IF AFTER WHOLE FUNCTION CALL IT DOESNOT RETURN 1 THEN MEANS FALSE RETURN 0
}

void solveSudoku(char board[][9]){                                     // FUNCTION TO COMPILE ALL OUR FUNCTIONS

    printf("\033[1;34m");
    printf("\n\n*************Sudoku Solver****************\n\n");
    printf("\033[0m"); 
    inputSudoku();

    if(helper(board,0,0)){
        printf("\n\n\n");
        printf("\033[1;34m"); 
        printf("\n*************Sudoku Solved****************\n");
        printf("\033[0m"); 
    }
    else{
        printf("Input is invalid\n");
        return;
    }
    printf("\n\n");
    boardPrint(9,9,board);
}

int main(){
    solveSudoku(board);
    return 0;
}