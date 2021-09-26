1. Consider a program whose sequential execution time is 100 days.  Assume that the program can be parallelized and the performance scales linearly in terms of number of processors.  Write an expression to compute the parallel execution time in terms of P, where P is the number of parallel processors. (1 mark)

2. Consider a program whose sequential execution time is 100 days.  Part A of this program cannot be parallelized and accounts for 40% of total execution time.  Part B of this program can be linearly parallelized and the performance scales linearly in terms of number of processors.  Part B accounts for 60% of total execution time.  Write an expression to compute the parallel execution time in terms of P, where P is the number of parallel processors. (1 mark)

3. Write all data dependences in the following codes (concise representation is fine for part B) (2 marks)
a)

```c
    a = b + c;
    b = b * 2;
    b = b - 2;
    d = b + a;
    c = (a>b)? a:b;
```

b)
```c
    for (i =3; i<10; i++ )
        for (j =3; j<20; j++ )
            for(k=20; k<42; k++)
                A[i][j] += C[i][k] / D[k][j]
                B[i][j][k] = B[i-1][j][k] + E[i][j][k]
                F[i][j][k] = F[i][j-1][k] + E[i][j][k]
                G[i][j][k] = G[i][j][k-1] + E[i][j][k]
```


4. Write a parallel program to add two 3-D arrays A[100][100][100] and B[100][100][100]. Report the execution time for num threads = 1, 2, 4, 8, 16, and 32. How do you explain the observed performance trend as a function of number of threads( a simple textual explain is fine). (3 marks)
