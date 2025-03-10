// Copyright @lucabotez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10007

// temp variables (***temp_a, **temp_result) are temporary matrices /
// collections of matrices used in functions, being copies or reallocations

// a = the collection of matrices
// vl = line array
// vc = column array
// s = number of elements in the collection
// number, n, n1, n2 = indices of matrices on whcih operations are performed

// function used to multiply square matrices of same size
void p_multiplication(int ***result, int **m1, int **m2, int size)
{
	int i, j, k;
	int **temp_result = *result;

	for (i = 0; i < size; i++) {
		for (k = 0; k < size; k++)
			for (j = 0; j < size; j++) {
				int x = m1[i][j] * m2[j][k];
				temp_result[i][k] = temp_result[i][k] + x;
				temp_result[i][k] = temp_result[i][k] % MAX;

				if (temp_result[i][k] < 0)
					temp_result[i][k] += MAX;
			}
	}
}

// function that initializes matrix m2 with zeros, and matrix m1
// with the elements of the identity matrix or copies of values
// in m2, depending on the character c
void set_matrix_values(int ***m1, int ***m2, int size, char c)
{
	int i, j;
	int **temp_m1 = *m1, **temp_m2 = *m2;

	if (c == 'I') { // temp_m1 becomes identity matrix
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++) {
				if (i == j)
					temp_m1[i][j] = 1;
				else
					temp_m1[i][j] = 0;
				temp_m2[i][j] = 0;
			}
	} else {        // temp_m1 becomes temp_m2
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++) {
				temp_m1[i][j] = temp_m2[i][j];
				temp_m2[i][j] = 0;
			}
	}
}

// function that dynamically allocates a matrix collection
// and 2 arrays in which the lines and columns of the matrices
// will be stored
void alloc_arrays(int ****a, int **vl, int **vc)
{
	*a = (int ***)malloc(1 * sizeof(int **));
	if (!a)
		exit(-1);

	*vl = (int *)malloc(1 * sizeof(int *));
	if (!vl) {
		free(a);
		exit(-1);
	}

	*vc = (int *)malloc(1 * sizeof(int *));
	if (!vc) {
		free(a);
		free(vl);
		exit(-1);
	}
}

// function that frees all the allocated memory
void free_all(int s, int ***a, int *vl, int *vc)
{
	int i, j;

	for (i = 0; i < s; i++) {
		for (j = 0; j < vl[i]; j++)
			free(a[i][j]);
		free(a[i]);
	}
	free(a);
	free(vl);
	free(vc);
}

// function that deletes a matrix from the collection
void free_matrix(int *s, int ****a, int **vl, int **vc)
{
	int i, n;
	int ***temp_a = *a, ***temp_a2;
	int *temp_l = *vl, *temp_l2;
	int *temp_c = *vc, *temp_c2;

	scanf("%d", &n);

	if (n > *s - 1 || n < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	for (i = 0; i < temp_l[n]; i++)
		free(temp_a[n][i]);
	free(temp_a[n]);

	for (i = n; i < (*s - 1); i++) {
		temp_a[i] = temp_a[i + 1];
		temp_l[i] = temp_l[i + 1];
		temp_c[i] = temp_c[i + 1];
	}

	*s = *s - 1;

	temp_a2 = (int ***)realloc(temp_a, *s * sizeof(int **));
	temp_l2 = (int *)realloc(temp_l, *s * sizeof(int));
	temp_c2 = (int *)realloc(temp_c, *s * sizeof(int));

	*a = temp_a2;
	*vl = temp_l2;
	*vc = temp_c2;
}

// function that adds a matrix in the collection
void read_matrix(int s, int ****a, int **vl, int **vc)
{
	int ***temp_a, *temp_l, *temp_c;
	int i, j;
	int l, c;

	scanf("%d%d", &l, &c);

	temp_a = (int ***)realloc(*a, s * sizeof(int **));
	if (!temp_a) {
		free_all(s, *a, *vl, *vc);
		exit(-1);
	}

	temp_l = (int *)realloc(*vl, s * sizeof(int));
	if (!temp_l) {
		free_all(s, temp_a, *vl, *vc);
		exit(-1);
	}
	temp_c = (int *)realloc(*vc, s * sizeof(int));
	if (!temp_c) {
		free_all(s, temp_a, temp_l, *vc);
		exit(-1);
	}

	temp_l[s - 1] = l;
	temp_c[s - 1] = c;
	*vl = temp_l;
	*vc = temp_c;

	temp_a[s - 1] = (int **)malloc(l * sizeof(int *));
	if (!temp_a[s - 1]) {
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}

	for (i = 0; i < l; i++) {
		temp_a[s - 1][i] = (int *)malloc(c * sizeof(int));
		if (!temp_a[s - 1][i]) {
			for (j = 0; j < i; j++)
				free(temp_a[s - 1][j]);
			free_all(s, temp_a, temp_l, temp_c);
			exit(-1);
		}
	}

	for (i = 0; i < l; i++)
		for (j = 0; j < c; j++)
			scanf("%d", &temp_a[s - 1][i][j]);

	*a = temp_a;
}

// function that prints the dimensions of a stored matrix
void print_dimensions(int s, int *vl, int *vc)
{
	int n;

	scanf("%d", &n);
	if (n > s - 1 || n < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	printf("%d %d\n", vl[n], vc[n]);
}

// function that prints a matrix from the collection
void print_matrix(int s, int ***a, int *vl, int *vc)
{
	int i, j, n;
	scanf("%d", &n);

	if (n > s - 1 || n < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	for (i = 0; i < vl[n]; i++) {
		for (j = 0; j < vc[n]; j++)
			printf("%d ", a[n][i][j]);
		printf("\n");
	}
}

// function that resizes a matrix
void resize_matrix(int s, int ****a, int **vl, int **vc)
{
	int l, c, i, j, n;
	int *lines, *columns, **new_matrix;
	int ***temp_a = *a;
	int *temp_l = *vl;
	int *temp_c = *vc;
	scanf("%d", &n);

	if (n > s - 1 || n < 0) {
		printf("No matrix with the given index\n");
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int value;
			scanf("%d", &value);
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int value;
			scanf("%d", &value);
		}
		return;
	}

	scanf("%d", &l);  // number of lines after which the matrix is resized
	lines = (int *)malloc(l * sizeof(int)); // array where the lines
	if (!lines) {							// are stored
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}
	for (i = 0; i < l; i++)
		scanf("%d", &lines[i]);

	scanf("%d", &c);  // number of columns after which the matrix is resized
	columns = (int *)malloc(c * sizeof(int)); // array where the columns
	if (!lines) {							  // are stored
		free(lines);
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}

	for (i = 0; i < c; i++)
		scanf("%d", &columns[i]);

	// resized matrix
	new_matrix = (int **)malloc(l * sizeof(int *));
	if (!new_matrix) {
		free(lines);
		free(columns);
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}
	for (i = 0; i < l; i++) {
		new_matrix[i] = (int *)malloc(c * sizeof(int));
		if (!new_matrix[i]) {
			for (j = 0; j < i; j++)
				free(new_matrix[i]);
			free(new_matrix);
			free(lines);
			free(columns);
			free_all(s, temp_a, temp_l, temp_c);
			exit(-1);
		}
	}

	for (i = 0; i < l; i++)
		for (j = 0; j < c; j++)
			new_matrix[i][j] = temp_a[n][lines[i]][columns[j]];

	for (i = 0; i < temp_l[n]; i++)
		free(temp_a[n][i]);
	free(temp_a[n]);

	temp_a[n] = new_matrix;
	temp_l[n] = l;
	temp_c[n] = c;

	free(lines);
	free(columns);
}

// function that multiplies 2 matrices and saves the result
void multiply_matrix(int *s, int ****a, int **vl, int **vc)
{
	int i, j, k, n1, n2;
	int ***temp_a, *temp_l, *temp_c;

	scanf("%d%d", &n1, &n2);

	if ((n1 > *s - 1 || n2 > *s - 1) || (n1 < 0 || n2 < 0)) {
		printf("No matrix with the given index\n");
		return;
	}
	if ((*vc)[n1] != (*vl)[n2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	*s = *s + 1;

	temp_a = (int ***)realloc(*a, *s * sizeof(int **));
	if (!temp_a) {
		free_all(*s, *a, *vl, *vc);
		exit(-1);
	}

	temp_l = (int *)realloc(*vl, *s * sizeof(int));
	if (!temp_l) {
		free_all(*s, temp_a, *vl, *vc);
		exit(-1);
	}

	temp_c = (int *)realloc(*vc, *s * sizeof(int));
	if (!temp_c) {
		free_all(*s, temp_a, temp_l, *vc);
		exit(-1);
	}

	temp_l[*s - 1] = temp_l[n1];
	temp_c[*s - 1] = temp_c[n2];

	temp_a[*s - 1] = (int **)calloc(temp_l[*s - 1], sizeof(int *));
	if (!temp_a[*s - 1]) {
		free_all(*s, temp_a, temp_l, temp_c);
		exit(-1);
	}
	for (i = 0; i < temp_l[*s - 1]; i++) {
		temp_a[*s - 1][i] = (int *)calloc(temp_c[*s - 1], sizeof(int));
		if (!temp_a[*s - 1][i]) {
			for (j = 0; j < i; j++)
				free(temp_a[*s - 1][j]);
			free_all(*s, temp_a, temp_l, temp_c);
			exit(-1);
		}
	}

	for (i = 0; i < temp_l[*s - 1]; i++)
		for (k = 0; k < temp_c[*s - 1]; k++)
			for (j = 0; j < temp_c[n1]; j++) {
				int x = temp_a[n1][i][j] * temp_a[n2][j][k];
				temp_a[*s - 1][i][k] = temp_a[*s - 1][i][k] + x;
				temp_a[*s - 1][i][k] = temp_a[*s - 1][i][k] % MAX;
				if (temp_a[*s - 1][i][k] < 0)
					temp_a[*s - 1][i][k] += MAX;
			}

	*a = temp_a;
	*vl = temp_l;
	*vc = temp_c;
}

// function that sorts the matrices in the collection by
// the sum of their elements
void sort_matrix(int s, int ****a, int **vl, int **vc)
{
	int sum, i, j, k, aux;
	int **paux, *vsum;
	int ***temp_a = *a;
	int *temp_l = *vl;
	int *temp_c = *vc;

	vsum = (int *)malloc(s * sizeof(int));
	if (!vsum) {
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}

	for (i = 0; i < s; i++) {
		sum = 0;
		for (j = 0; j < temp_l[i]; j++)
			for (k = 0; k < temp_c[i]; k++) {
				sum = sum + temp_a[i][j][k];
				sum = sum % MAX;
				if (sum < 0)
					sum = sum + MAX;
			}

		vsum[i] = sum;
	}

	for (i = 0; i < s; i++)
		for (j = i + 1; j < s; j++)
			if (vsum[i] > vsum[j]) {
				aux = vsum[i];
				vsum[i] = vsum[j];
				vsum[j] = aux;

				aux = temp_l[i];
				temp_l[i] = temp_l[j];
				temp_l[j] = aux;

				aux = temp_c[i];
				temp_c[i] = temp_c[j];
				temp_c[j] = aux;

				paux = temp_a[i];
				temp_a[i] = temp_a[j];
				temp_a[j] = paux;
			}
	free(vsum);
}

// function that computes the transposed matrix and replaces the
// original matrix in the collection
void transpose_matrix(int s, int ****a, int **vl, int **vc)
{
	int i, j, aux, n;
	int ***temp_a = *a;
	int *temp_l = *vl;
	int *temp_c = *vc;
	int **new_matrix;

	scanf("%d", &n);

	if (n > s - 1 || n < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	// transpose matrix
	new_matrix = (int **)malloc(temp_c[n] * sizeof(int *));
	if (!new_matrix) {
		free_all(s, temp_a, temp_l, temp_c);
		exit(-1);
	}

	for (i = 0; i < temp_c[n]; i++) {
		new_matrix[i] = (int *)malloc(temp_l[n] * sizeof(int));
		if (!new_matrix[i]) {
			for (j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			free_all(s, temp_a, temp_l, temp_c);
			exit(-1);
		}
	}

	for (i = 0; i < temp_l[n]; i++)
		for (j = 0; j < temp_c[n]; j++)
			new_matrix[j][i] = temp_a[n][i][j];

	for (i = 0; i < temp_l[n]; i++)
		free(temp_a[n][i]);

	free(temp_a[n]);

	temp_a[n] = new_matrix;

	aux = temp_l[n];
	temp_l[n] = temp_c[n];
	temp_c[n] = aux;
}

// function that raises a matrix to a given power
// and replaces the original matrix in the collection
void raise_matrix(int s, int ****a, int *vl, int *vc)
{
	int ***temp_a = *a, **new_matrix, **aux, i, j, power, number;
	scanf("%d%d", &number, &power);

	if (number > s - 1 || number < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (power < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (vl[number] != vc[number]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}

	new_matrix = (int **)malloc(vl[number] * sizeof(int *));
	if (!new_matrix) {
		free_all(s, temp_a, vl, vc);
		exit(-1);
	}
	for (i = 0; i < vl[number]; i++) {
		new_matrix[i] = (int *)malloc(vl[number] * sizeof(int));
		if (!new_matrix[i]) {
			for (j = 0; j < i; j++)
				free(new_matrix[j]);
			free(new_matrix);
			free_all(s, temp_a, vl, vc);
			exit(-1);
		}
	}

	aux = (int **)malloc(vl[number] * sizeof(int *));
	if (!aux) {
		for (i = 0; i < vl[number]; i++)
			free(new_matrix[i]);
		free(new_matrix);
		free_all(s, temp_a, vl, vc);
		exit(-1);
	}

	for (i = 0; i < vl[number]; i++) {
		aux[i] = (int *)malloc(vl[number] * sizeof(int));
		if (!aux[i]) {
			for (j = 0; j < i; j++)
				free(aux[j]);
			free(aux);
			for (j = 0; j < vl[number]; j++)
				free(new_matrix[j]);
			free(new_matrix);
			free_all(s, temp_a, vl, vc);
			exit(-1);
		}
	}

	set_matrix_values(&new_matrix, &aux, vl[number], 'I');

	while (power != 0) {
		if (power % 2 != 0) {
			p_multiplication(&aux, new_matrix, temp_a[number], vl[number]);
			set_matrix_values(&new_matrix, &aux, vl[number], 'C');
		}

		p_multiplication(&aux, temp_a[number], temp_a[number], vl[number]);
		set_matrix_values(&temp_a[number], &aux, vl[number], 'C');

		power = power / 2;
	}

	for (i = 0; i < vl[number]; i++)
		for (j = 0; j < vl[number]; j++)
			temp_a[number][i][j] = new_matrix[i][j];

	for (i = 0; i < vl[number]; i++) {
		free(aux[i]);
		free(new_matrix[i]);
	}
	free(aux);
	free(new_matrix);
}

int main(void)
{
	int ***array, *lines, *columns;
	// array = the collection of matrices, lines/columns = matrices lines/columns
	char command; // requested operation
	int size = 0; // matrix collection size

	alloc_arrays(&array, &lines, &columns);

	while (scanf("%c", &command)) {
		switch (command) {
			case 'L': {
				size++;
				read_matrix(size, &array, &lines, &columns);
				break;
			}
			case 'D': {
				print_dimensions(size, lines, columns);
				break;
			}
			case 'P': {
				print_matrix(size, array, lines, columns);
				break;
			}
			case 'C': {
				resize_matrix(size, &array, &lines, &columns);
				break;
			}
			case 'M': {
				multiply_matrix(&size, &array, &lines, &columns);
				break;
			}
			case 'O': {
				sort_matrix(size, &array, &lines, &columns);
				break;
			}
			case 'T': {
				transpose_matrix(size, &array, &lines, &columns);
				break;
			}
			case 'R': {
				raise_matrix(size, &array, lines, columns);
				break;
			}
			case 'F': {
				free_matrix(&size, &array, &lines, &columns);
				break;
			}
			case 'Q': {
				free_all(size, array, lines, columns);
				return 0;
			}
			case '\n': {
				break;
			}
			default: {
				printf("Unrecognized command\n");
				break;
			}
		}
	}

	return 0;
}
