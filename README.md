# Parallel Programming - Assignment 3

https://github.com/AlexandreSabbadin/pp-assignment3

How to run the program:

```bash
gcc par_sieve.c -o par_sieve -lm -fopenmp
srun -c 2 par_sieve 2 1000
```

To test the program I ran it with `-c` on *dione* cluster. For each message size I did 5 tries then took the smallest result. All the results are compiled into the following table. Time unit is seconds.

| N         | Sequential | -c 2     | -c 4     | -c 8     | -c 16    |
|-----------|------------|----------|----------|----------|----------|
| 100       | 0.000000   | 0.000126 | 0.000304 | 0.000468 | 0.077740 |
| 1000      | 0.000000   | 0.000131 | 0.000325 | 0.234208 | 0.000797 |
| 10000     | 0.000000   | 0.000223 | 0.000334 | 0.643597 | 0.598184 |
| 100000    | 0.000000   | 0.000684 | 0.000994 | 1.990877 | 2.037884 |
| 1000000   | 0.010000   | 0.004960 | 0.006771 | 0.313519 | 6.399243 |
| 10000000  | 0.130000   | 0.045959 | 0.043782 | 1.156262 | 9.918036 |
| 100000000 | 1.280000   | 0.513822 | 0.503772 | 0.563138 | 3.729863 |

Console logs for `srun -c 8 par_sieve 8 1000000`:

![output3](https://user-images.githubusercontent.com/85174595/197785017-5c351808-bb0c-4d8a-a77d-b8876888fca7.PNG)
