// Copyright @lucabotez

#ifndef MY_OCTAVE_H
#define MY_OCTAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10007

// function headers
void p_multiplication(int ***result, int **m1, int **m2, int size);
void set_matrix_values(int ***m1, int ***m2, int size, char c);
void alloc_arrays(int ****a, int **vl, int **vc);
void free_all(int s, int ***a, int *vl, int *vc);
void free_matrix(int *s, int ****a, int **vl, int **vc);
void read_matrix(int s, int ****a, int **vl, int **vc);
void print_dimensions(int s, int *vl, int *vc);
void print_matrix(int s, int ***a, int *vl, int *vc);
void resize_matrix(int s, int ****a, int **vl, int **vc);
void multiply_matrix(int *s, int ****a, int **vl, int **vc);
void sort_matrix(int s, int ****a, int **vl, int **vc);
void transpose_matrix(int s, int ****a, int **vl, int **vc);
void raise_matrix(int s, int ****a, int *vl, int *vc);

#endif // MY_OCTAVE_H