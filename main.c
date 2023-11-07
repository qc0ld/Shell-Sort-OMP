#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void shell_sort(int *array, int count);

int main() {

    srand(time(NULL));

    const int count = 10000000;
    const int max_threads = 12;
    
    int *temp = malloc(count * sizeof(int));
    int *array = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        temp[i] = rand();
        array[i] = temp[i];
    }

    for (int threads = 1; threads <= max_threads; threads++){
        double start_time = omp_get_wtime();

        omp_set_num_threads(threads);

        shell_sort(array, count);

        printf("Threads: %d. Time: %f\n", threads, omp_get_wtime() - start_time);

        for (int i = 0; i < count; i++) { array[i] = temp[i]; }
    }
    return 0;
}

void shell_sort(int *array, int count) {
    for (int i = count / 2; i > 0; i /= 2) {
        #pragma omp parallel for shared(array, count, i) default(none)
        for (int k = 0; k < i; k++) {
            for (int j = k + i; j < count; j += i) {
                int key = array[j];
                int l = j;

                while (l >= i && array[l - i] > key) {
                    int temp = array[l];
                    array[l] = array[l - i];
                    array[l - i] = temp;
                    l -= i;
                }
                array[l] = key;
            }
        }
    }
}