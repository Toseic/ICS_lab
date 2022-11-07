
/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"
#include "contracts.h"


int s0,s1,s2,s3,s4,s5,s6,s7,s8,s9;
int i, j;

void action(int i, int j, int M, int N, int A[N][M], int B[M][N]) {
    s0 = A[i][j];     s1 = A[i][j+1];  
    s2 = A[i][j+2];   s3 = A[i][j+3]; 
    s4 = A[i+1][j];   s5 = A[i+1][j+1]; 
    s6 = A[i+1][j+2]; s7 = A[i+1][j+3]; 
    B[j][i] = s0;    B[j+1][i] = s1; 
    B[j+2][i] = s2;   B[j+3][i] = s3; 
    B[j][i+1] = s4;   B[j+1][i+1] = s5; 
    B[j+2][i+1] = s6; B[j+3][i+1] = s7;

}






void action2_1(int i, int j,int M, int N, int A[N][M], int B[M][N]) {
    action(i,j,M,N,A,B); // false
    action(i+2,j,M,N,A,B);
    action(i+4,j,M,N,A,B);
    action(i+6,j,M,N,A,B);
    action(i+4,j+4,M,N,A,B);
    action(i+6,j+4,M,N,A,B);    
    action(i,j+4,M,N,A,B);
    action(i+2,j+4,M,N,A,B);
}




int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. The REQUIRES and ENSURES from 15-122 are included
 *     for your convenience. They can be removed if you like.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    REQUIRES(M > 0);
    REQUIRES(N > 0);

    if (M==32) {    
    for (j=0;j<32;j+=8) {
        for (i=0;i<32;i+=8) {
            action2_1(i,j,M,N,A,B);
        }
    } 
    } else if (M == 64){  
        for (s8 = 0; s8 < N; s8 += 8) {
            for (s9 = 0; s9 < M; s9 += 8) {
                for (i = s8; i < s8 + 4; i++) {
                    s0 = A[i][0+s9]; s1 = A[i][1+s9]; s2 = A[i][2+s9]; s3 = A[i][3+s9];  s4 = A[i][4+s9]; s5 = A[i][5+s9]; s6 = A[i][6+s9]; s7 = A[i][7+s9];
                    B[0+s9][i] = s0; B[1+s9][i] = s1; B[2+s9][i] = s2; B[3+s9][i] = s3;  B[0+s9][4+i] = s4; B[1+s9][4+i] = s5; B[2+s9][4+i] = s6; B[3+s9][4+i] = s7;  
                }
                for (j = s9; j < s9 + 4; j++) {
                    s0 = A[4+s8][j]; s1 = A[5+s8][j]; s2 = A[6+s8][j]; s3 = A[7+s8][j];    s4 = B[j][4+s8]; s5 = B[j][5+s8]; s6 = B[j][6+s8]; s7 = B[j][7+s8];  
                    B[j][4+s8] = s0; B[j][5+s8] = s1; B[j][6+s8] = s2; B[j][7+s8] = s3;     B[4+j][0+s8] = s4; B[4+j][1+s8] = s5; B[4+j][2+s8] = s6; B[4+j][3+s8] = s7; 
                }
                for (i = s8 + 4; i < s8 + 8; i++) {
                    s0 = A[i][4+s9]; s1 = A[i][5+s9]; s2 = A[i][6+s9]; s3 = A[i][7+s9];  B[4+s9][i] = s0; B[5+s9][i] = s1; B[6+s9][i] = s2; B[7+s9][i] = s3; 
                }
            }
        }
 

    } else if (M == 60){
        for (j=0;j<56;j+=8) { 
            for (i = 0;i<64;i+=8) {
                action2_1(i,j,M,N,A,B);
            }
        }    
        j = 56;
        for (i=0;i<68;i+=2) {
            action(i,j,M,N,A,B);
        }
        i = 64;
        for (j=0;j<60;j+=4) {
                 action(i,j,M,N,A,B);
            i += 2;
                 action(i,j,M,N,A,B);
            i -= 2;
        }

    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

 /*
  * trans - A simple baseline transpose function, not optimized for the cache.
  */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    REQUIRES(M > 0);
    REQUIRES(N > 0);

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

    ENSURES(is_transpose(M, N, A, B));
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

