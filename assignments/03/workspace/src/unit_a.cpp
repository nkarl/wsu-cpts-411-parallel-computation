#include "unit_a.h"

using std::cout;
using std::queue;
using std::string;

#define TIME_STEPS 4
#define M 3
#define N 4

void print_board(int board[M][N]); 

bool run_unit_a() {
    int inp_cells[M][N] {};  // placeholder
    int out_cells[M][N] {};  // placeholder

    // RANDOMIZE THE BOARD
    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            inp_cells[i][j] = rand() % 2;
        }
    }

    print_board(inp_cells);

    return true;
}

void print_board(int board[M][N]) {
    cout << "\nINPUT CELLS:";
    cout << "\n------------\n";
    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

