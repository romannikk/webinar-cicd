
#include <iostream>
#include <assert.h>
#include <tuple>

#include "tests/lib.h"

#include "Matrix.h"

int main(int, char **)
{
    Matrix<int, 0> matrix;
    constexpr int size = 10;

     // Заполнение матрицы диагональными элементами
    for (int i = 0; i < size; ++i) 
    {
        matrix[i][i] = i;
        matrix[i][10 - (i + 1)] = 10 - (i + 1);
    }

    // Вывод участка матрицы от [1, 1]  до  [8, 8]
    for (int i = 1; i < size - 1; ++i) 
    {
        for (int j = 1; j < size - 1; ++j) std::cout << matrix[i][j] << ' ';
            std::cout << std::endl;
    }
    // Вывести количество занятых ячеек
    std::cout << "Size = " << matrix.size() << std::endl;
    std::cout << std::endl;

    // Вывести все занятые ячейки
    for(const auto& [s ,b] : matrix)
    {
        std::cout <<"Row: "<<s[0]<<" Column: " << s[1] << " Value: "<< b << std::endl;
    }
    
    std::cout << "Size: "<< matrix.size() << std::endl;


    matrix.clear();

    ((matrix[100][100] = 314) = 0) = 217;

    std::cout << "Size: "<< matrix.size() <<" Value: "<< matrix[100][100]<< std::endl;
}
