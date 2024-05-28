#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int colms) : rows(rows), colms(colms) {
        data.resize(rows, vector<double>(colms, 0));
    }

    void input() {
        cout << "Enter values for a " << rows << "x" << colms << " matrix:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < colms; ++j) {
                cin >> data[i][j];
            }
        }
    }

    void print() const {
        cout << "Matrix (" << rows << "x" << colms << "):\n";
        for (const auto& row : data) {
            for (double val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

    Matrix operator*(const Matrix& other) const {
        if (colms != other.rows) {
            throw invalid_argument("Matrix dimensions do not allow multiplication");
        }

        Matrix result(rows, other.colms);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.colms; ++j) {
                for (int k = 0; k < colms; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

private:
    int rows, colms;
    vector<vector<double>> data;
};

int main() {
    int m, n;
    cout << "Enter the number of rows (m): ";
    cin >> m;
    cout << "Enter the number of columns (n): ";
    cin >> n;

    Matrix matA(m, n);
    Matrix matB(n, m);
    Matrix matC(m, m);

    cout << "Input matrix A:\n";
    matA.input();
    cout << "Input matrix B:\n";
    matB.input();

    matC = matA * matB;

    cout << "Matrix A:\n";
    matA.print();
    cout << "Matrix B:\n";
    matB.print();
    cout << "Matrix C (A * B):\n";
    matC.print();

    return 0;
}