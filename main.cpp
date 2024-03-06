#include <iostream>

using namespace std;


const int SIZE = 10;


double det(double matrix[][SIZE], int size, int j);
void print_matrix(double matrix[][SIZE], int size);
void copy_matrix(double src[][SIZE], double dest[][SIZE], int size);
void to_minor(double matrix[][SIZE], int size, int i, int j);
void to_triangular(double matrix[][SIZE], int size);
double det_for_triangular(double matrix[][SIZE], int size);


double matrix[SIZE][SIZE];


int main()
{
    int size;
    cout << "Enter size of matrix: ";
    cin >> size;
    if (size < 1 || size > SIZE)
    {
        cout << "Incorrect size of matrix";
        return 0;
    }

    cout << "\nEnter matrix:\n";
    for (int row = 0; row < size; row++)
    {
        cout << "Row " << row + 1 << ": ";
        for (int col = 0; col < size; col++)
        {
            cin >> matrix[row][col];
        }
    }

    int row;
    cout << "\nEnter row for expansion: ";
    cin >> row;
    if (row < 1 || row > size)
    {
        cout << "Incorrect row";
        return 0;
    }
    row -= 1;

    cout << "\nEntered matrix:\n";
    print_matrix(matrix, size);

    double det1 = det(matrix, size, row);
    cout << "\nValue of determinant: " << det1 << endl;

    to_triangular(matrix, size);
    cout << "\nTriangular matrix:\n";
    print_matrix(matrix, size);

    double det2 = det_for_triangular(matrix, size);
    cout << "\nValue of determinant for triangular matrix: " << det2 << endl;

    cout << "\nThe differ beetween the determinants: " << abs(det1 - det2) << endl;

    return 0;
}


double det(double matrix[][SIZE], int size, int col)
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
        to_minor(minor_matrix, size, row, col);
        result += det(minor_matrix, size - 1, 0) * matrix[row][col] * ((row + col) % 2 != 0 ? -1 : 1);
    }
    return result;
}


void to_triangular(double matrix[][SIZE], int size)
{
    for (int col1 = 0; col1 < size; col1++)
    {
        int row1 = col1, row2 = col1;
        while (row2 < size && matrix[row2][col1] == 0)
        {
            row2++;
        }
        if (row2 != size)
        {
            if (row1 != row2)
            {
                for (int col2 = 0; col2 < size; col2++)
                {
                    swap(matrix[row1][col2], matrix[row2][col2]);
                    matrix[0][col2] *= -1;
                }
            }
            for (int row2 = col1 + 1; row2 < size; row2++)
            {
                double factor = matrix[row2][col1] / matrix[row1][col1];
                for (int col2 = 0; col2 < size; col2++)
                {
                    matrix[row2][col2] -= matrix[row1][col2] * factor;
                }
            }
        }
    }
}


double det_for_triangular(double matrix[][SIZE], int size)
{
    double p = 1;
    for (int row = 0; row < size; row++)
    {
        p *= matrix[row][row];
    }
    return p;
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
