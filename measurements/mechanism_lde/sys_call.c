#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char** argv)
{
    struct timeval start, end;
    int iter = 10000, total = 0;

    if (gettimeofday(&start, NULL) == -1) {
        fprintf(stderr, "gettimeofday failed\n");
        exit(-1);
    }

    for (int i = 0; i < iter; i++) { total += getpid(); }

    if (gettimeofday(&end, NULL) == -1) {
        fprintf(stderr, "gettimeofday failed\n");
        exit(-1);
    }

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 10000.0;
    double avg_time = elapsed / iter;

    printf("Total time for %d getpid calls: %.6f seconds\n", iter, elapsed);
    printf("Average time per getpid call: %.6f microseconds\n", avg_time * 100000.0);
    printf("Total (for verification): %d\n", total);

    return 0;    
}