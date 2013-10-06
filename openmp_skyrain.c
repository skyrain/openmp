#include<stdio.h>
#include<stdlib.h>
#include<opm.h>

#define LEN 250
#define RANGE 10000


void initialize_array(int[], int);
void getRandomArray(int[], int);
void print_matrice(int[], int, int);

int main(int argc, char** argv)
{
    int A[LEN * LEN];
    getRandomArray(A, LEN * LEN);
    int B[LEN * LEN];
    getRandomArray(B, LEN * LEN);
    int C[LEN * LEN];
    getRandomArray(C, LEN * LEN);

    //set loop chunk size
    int chunk = 10;
    int PID, p_size, i, j, k;
    #pragma omp parallel shared(A, B, C, p_size, chunk) private(PID, i, j, k)
    {
        PID = omp_get_thread_num();
        if(PID == 0)
        {
            p_size = omp_get_num_threads();
            printf("Use %d threads", p_size);
        }

        //allocate matrices data
        #pragma omp parallel for schedule(static, chunk)
        for(i = 0; i < LEN; i++)
        {
            for(j = 0; j < LEN; j++)
            {
                for(k = 0; k < LEN; k++)
                    C[i * LEN + j] += A[i * LEN + k] * B[k * LEN + j];
            }
        }
    }

    //print matrices
    printf("Matrice A:\n");
    print_matrice(A, LEN, LEN);
    printf("Matrice B:\n");
    print_matrice(B, LEN, LEN);
    printf("Matrice C:\n");
    print_matrice(C, LEN, LEN);

    return EXIT_SUCCESS;
}









/*
 *method
 */
void initialize_array(int array[], int len)
{
    int i;
    for(i = 0; i < len; i++)
        array[i] = 0;
}

void getRandomArray(int array[], int len)
{
    int i;
    for(i = 0; i < len; i++)
        array[i] = rand() % RANGE;
}
void print_matrice(int matrice[], int row, int column)
{
    int i,j;
    for(i = 0; i < row; i++)
    {                   
        for(j = 0; j < column; j++)
        {
            printf("%d ", matrice[i * row + j]);
        }
        printf("\n");
    }       
    printf("\n");       
}
