#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


const int SIZE = 10;


double det(double matrix[][SIZE], int size, int j);
void print_matrix(double matrix[][SIZE], int size);
void copy_matrix(double src[][SIZE], double dest[][SIZE], int size);
void to_minor(double matrix[][SIZE], int size, int i, int j);
void to_triangular(double matrix[][SIZE], int size);
void fill_random(double matrix[][SIZE], int size);
void fill_natural(double matrix[][SIZE], int size);
void input_from_keyboard(double matrix[][SIZE], int size);


double matrix[SIZE][SIZE];
clock_t start, finish, ticks1, ticks2;
double time1, time2;


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

    char input_mode;
    cout << "\nSelect input mode (k - keyboard, r - random, n - natural): ";
    cin >> input_mode;

    switch (input_mode)
    {
        case 'k':
        {
            input_from_keyboard(matrix, size);
            break;
        }
        case 'r':
        {
            fill_random(matrix, size);
            break;
        }
        case 'n':
        {
            fill_natural(matrix, size);
            break;
        }
        default:
        {
            cout << "Incorrect input mode";
            return 0;
        }
    }

    cout << "\nEntered matrix:\n";
    print_matrix(matrix, size);

    int col;
    cout << "\nEnter col for expansion: ";
    cin >> col;
    if (col < 1 || col > size)
    {
        cout << "Incorrect col";
        return 0;
    }
    col -= 1;

    start = clock();
    double det1 = det(matrix, size, col);
    finish = clock();

    ticks1 = finish - start;
    time1 = 1e3 * ticks1 / CLOCKS_PER_SEC;

    cout << "\nValue of determinant: " << det1 << endl;

    start = clock();
    to_triangular(matrix, size);
    double det2 = det(matrix, size, col);
    finish = clock();

    ticks2 = finish - start;
    time2 = 1e3 * ticks2 / CLOCKS_PER_SEC;

    cout << "\nTriangular matrix:\n";
    print_matrix(matrix, size);

    cout << "\nValue of determinant for triangular matrix: " << det2 << endl;

    cout << "\nThe differ beetween the determinants: " << abs(det1 - det2) << endl;

    cout << setprecision(15);
    cout << "\nRecursive calculation took " << time1 << " miliseconds (" << ticks1 << " ticks)";
    cout << "\nCalculation from trinagular took " << time2 << " miliseconds (" << ticks2 << " ticks)";

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
        double elem = matrix[row][col];
        if (elem != 0)
        {
            result += det(minor_matrix, size - 1, 0) * elem * ((row + col) % 2 != 0 ? -1 : 1);
        }
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


void print_matrix(double matrix[][SIZE], int size)
{
    cout << setprecision(4);
    for (int col = 0; col < size; col++)
    {
        cout << "\t" << col + 1;
    }
    cout << endl;
    for (int row = 0; row < size; row++)
    {
        cout << row + 1 << "\t";
        for (int col = 0; col < size; col++)
        {
            double elem = matrix[row][col];
            cout << (abs(elem) < 1e-4 ? 0 : elem) << "\t";
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


void fill_random(double matrix[][SIZE], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            matrix[row][col] = double(rand()) * 1e-4;
        }
    }
}


void fill_natural(double matrix[][SIZE], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            matrix[row][col] = row * size + col + 1;
        }
    }
}


void input_from_keyboard(double matrix[][SIZE], int size)
{
    cout << "\nEnter matrix:\n";
    for (int row = 0; row < size; row++)
    {
        cout << "Row " << row + 1 << ": ";
        for (int col = 0; col < size; col++)
        {
            cin >> matrix[row][col];
        }
    }
}
