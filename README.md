Copyright @lucabotez

## Octave Simulator

The program performs various operations with dynamically allocated integer matrices, based on received commands.

### COMMANDS:

#### 1) 'L' = Load a matrix into memory
We receive the dimensions of a matrix and its elements. The dimensions will be stored in two dynamically allocated vectors (one for rows, one for columns), while the elements will be stored in a matrix added to a collection of matrices (a vector storing matrix addresses in the order they were read).

Modifications to the size of the vectors will be done dynamically using the `realloc()` function, adding one position at a time.

#### 2) 'D' = Display the dimensions of a matrix
We receive the index of a matrix. If a matrix is stored at that index, its dimensions will be displayed from the respective vectors; otherwise, a corresponding message will be shown.

#### 3) 'P' = Display a matrix
We receive the index of a matrix. If a matrix is stored at that index, it will be displayed; otherwise, a corresponding message will be shown.

#### 4) 'C' = Resize a matrix
We receive a number of rows, followed by the indices of the rows for resizing. These indices are stored in a dynamically allocated vector. Similarly, column indices are stored in another vector. A new matrix is created in an auxiliary dynamically allocated variable, the memory allocated for the original matrix is freed, and the address of the new matrix is placed in the freed position of the matrix vector. The dimensions in the row and column vectors are also updated.

#### 5) 'M' = Multiply two matrices
We receive the indices of two matrices. If the indices are valid and the matrices can be multiplied, the matrix vector and the two dimension vectors are reallocated to add a new position for storing the product and its dimensions. The resulting matrix is computed and placed in the new position of the matrix vector.

#### 6) 'O' = Sort matrices
The sum of the elements of each matrix is computed and stored in a dynamically allocated vector. The sum vector is sorted using selection sort, and whenever two elements are swapped, the corresponding matrix addresses in the matrix collection and their dimensions in the row and column vectors are also swapped.

#### 7) 'T' = Transpose a matrix
We receive the index of a matrix and compute its transpose in an auxiliary dynamically allocated matrix. The memory of the original matrix is freed, and the address of the new matrix is placed in the freed position of the matrix vector. The dimensions in the row and column vectors are also updated.

#### 8) 'R' = Exponentiation in logarithmic time
We receive the index of a matrix and the power to which it should be raised. If both numbers are valid and the matrix is square, two dynamically allocated matrices are created: one that will store the exponentiated matrix (initialized as an identity matrix) and an auxiliary matrix for multiplication. Setting zero values in the auxiliary matrix and assigning specific values in the result matrix is done using the `set_matrix_values` function. Then, the exponentiation algorithm is applied in logarithmic time, based on the parity of the exponent (as described in the problem statement); multiplications are performed using the `p_multiplication` function. Finally, the memory of the original matrix is freed, and the address of the new matrix is placed in the freed position.

#### 9) 'F' = Free a matrix's memory
We receive the index of a matrix and free its allocated memory. All addresses starting from `index+1` are shifted left by one position, and the matrix vector is reallocated with one position less to avoid unnecessary memory usage. Similarly, the row and column vectors are updated by shifting elements left and reallocating memory.

#### 10) 'Q' = Free all resources
The allocated memory for each matrix is freed, followed by freeing the matrix vector and the two dimension vectors.

