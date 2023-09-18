#include <stdio.h> 
#include <omp.h> 

#define N 15 // Change N to the desired board size 

int board[N]; 

int isSafe(int row, int col) { 
    for (int i = 0; i < row; i++) { 
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row) { 
            return 0; 
        } 
    } 
    return 1; 
} 

void printBoard() { 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) { 
            if (board[i] == j) { 
                printf("Q "); 
            } else { 
                printf(". "); 
            } 
        } 
        printf("\n"); 
    } 
    printf("\n"); 
}

void parallelSolveNQueens() { 
	int tid, num_threads ;
	#pragma omp parallel private(tid, num_threads) num_threads(1)
	{
		int row = 0; 
		tid = omp_get_thread_num(); 
		num_threads = omp_get_num_threads(); 
		// Distribute rows among threads 
    for (int i = tid; i < N; i += num_threads) { 
        board[i] = -1; 
        row = i; 
        while (row >= 0) { 
            board[row]++; 
            while (board[row] < N && !isSafe(row, board[row])) { 
                board[row]++; 
            } 
            if (board[row] < N) { 
                if (row == N - 1) { 
                    //#pragma omp critical 
                    //printBoard(); 
                } else { 
                    row++; 
                    board[row] = -1; 
                } 
            } else { 
                row--; 
            } 
        } 
    } 
	}
} 

int main() { 
	    double starttime, stoptime;
	starttime = omp_get_wtime();
    parallelSolveNQueens(); 
    stoptime = omp_get_wtime();
	printf("Tempo de execucao: %3.2f segundos\n", stoptime-starttime);
    return 0; 

} 
