#include <stdio.h>
#include <omp.h>

#define TIME_STEPS 4
#define M 9
#define N 9

// HEADER
int gol();

// MAIN
int main() {
    gol();
    return 0;
}

int gol() {
    int inp_cells[M][N];    // placeholder
    int out_cells[M][N];    // placeholder

    for (int outer=0; outer<TIME_STEPS; ++outer) {
        for (int i=0; i<N; ++i) {
            for (int j=0; i<M; ++j) {
                int neigh_count;

                if (inp_cells[i][j] == 1) {
                    out_cells[i][j] = neigh_count >= 2 ? 1 : 0;
                }
                else {
                    out_cells[i][j] = neigh_count >= 4 ? 1 : 0;
                }
            }
        }
    }
    // swap(out_cells, imp_cells);
    return 0;
}
