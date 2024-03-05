#include <iostream>

using namespace std;


const int SIZE = 10;


double det(double matrix[][SIZE], int size, int j);
void print_matrix(double matrix[][SIZE], int size);
void copy_matrix(double src[][SIZE], double dest[][SIZE], int size);
void to_minor(double matrix[][SIZE], int size, int i, int j);


double matrix[SIZE][SIZE];


int main()
{
    int size;
    cout << "Enter size of matrix: ";
    cin >> size;
    // check
    cout << "Enter matrix:\n";
    for (int row = 0; row < size; row++)
    {
        cout << "row " << row + 1 << ": ";
        for (int col = 0; col < size; col++)
        {
            cin >> matrix[row][col];
        }
    }
    cout << "Entered matrix:\n";
    print_matrix(matrix, size);
    cout << "Value of determinant: " << det(matrix, size, 0);
    return 0;
}


double det(double matrix[][SIZE], int size, int j)
{
    if (size == 1)
    {
        return matrix[0][0];
    }
    double result = 0;
    for (int row = 0; row < size; row++)
    {
        double minor_matrix[SIZE][SIZE];
        copy_matrix(matrix, minor_matrix, size);
        to_minor(minor_matrix, size, row, j);
        result += det(minor_matrix, size - 1, 0) * matrix[row][j] * ((row + j) % 2 != 0 ? -1 : 1);
    }
    return result;
}


void print_matrix(double matrix[][SIZE], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            cout << matrix[row][col] << "\t";
        }
        cout << endl;
    }
}


void copy_matrix(double src[][SIZE], double dest[][SIZE], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            dest[row][col] = src[row][col];
        }
    }
}


void to_minor(double matrix[][SIZE], int size, int i, int j)
{
    for (int row = i; row < size - 1; row++)
    {
        for (int col = 0; col < size; col++)
        {
            matrix[row][col] = matrix[row + 1][col];
        }
    }
    for (int row = 0; row < size - 1; row++)
    {
        for (int col = j; col < size - 1; col++)
        {
            matrix[row][col] = matrix[row][col + 1];
        }
    }
}
