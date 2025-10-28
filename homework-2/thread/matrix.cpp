//
// Created by alxdrzd on 10/26/25.
//

#include "matrix.h"



std::vector<std::vector<int32_t>> createMatrix(const int32_t n)
{
    std::vector<std::vector<int32_t>> matrix(n, std::vector<int32_t>(n, 0));
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            matrix[i][j] = static_cast<int32_t>(random()) % 21;
        }
    }

    return matrix;
}

void print(const std::vector<std::vector<int64_t>> &matrix)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<int64_t>> simpleMultiplication(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B)
{
    if (A[0].size() != B.size())
    {
        throw std::invalid_argument("Matrices are not the adjusted! =-(");
    }
    const size_t n = A.size(), l = A[0].size(), m = B[0].size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(m, 0));
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            int64_t sum = 0;
            for (size_t k = 0; k < l; ++k)
            {
                sum += static_cast<int64_t>(A[i][k]) * static_cast<int64_t>(B[k][j]);
            }
            C[i][j] += sum;
        }
    }

    return C;
}

void rowsMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B, std::vector<std::vector<int64_t>> &C,
                  int32_t start_row, int32_t end_row)
{
    for (size_t i = start_row; i < end_row; ++i)
    {
        for (size_t j = 0; j < B[0].size(); ++j)
        {
            int64_t sum = 0;
            for (size_t k = 0; k < A[0].size(); ++k)
            {
                sum += static_cast<int64_t>(A[i][k]) * static_cast<int64_t>(B[k][j]);
            }
            C[i][j] = sum;
        }
    }
}

std::vector<std::vector<int64_t>> threadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B)
{
    if (A.empty() || B.empty() || A[0].size() != B.size())
    {
        throw std::invalid_argument("The Matrices are not adjusted");
    }

    const int32_t n = A.size(), l = B[0].size();

    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(l, 0));

    uint32_t num_threads = std::thread::hardware_concurrency();
    num_threads = num_threads == 0 ? 2 : num_threads;
    num_threads = std::min(static_cast<uint32_t>(n), num_threads);

    std::vector<std::thread> threads;

    const int32_t rows_per_thread = n / num_threads;
    int32_t current_start_row = 0;

    for (uint32_t i = 0; i < num_threads; ++i)
    {
        int32_t current_end_row = current_start_row + rows_per_thread;

        if (i == num_threads - 1)
        {
            current_end_row = n;
        }

        threads.emplace_back(rowsMultiply, std::ref(A), std::ref(B), std::ref(C), current_start_row, current_end_row);

        current_start_row = current_end_row;
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return C;
}

void blocksMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B, std::vector<std::vector<int64_t>> &C,
                    const int32_t &start_col, const int32_t &start_row, const int32_t &BLOCK_SIZE)
{
    const int32_t n = A.size(), m = A[0].size(), l = B[0].size();

    const int32_t end_col = std::min(start_col + BLOCK_SIZE, l);
    const int32_t end_row = std::min(start_row + BLOCK_SIZE, n);

    for (int32_t i = start_row; i < end_row; ++i)
    {
        for (int32_t j = start_col; j < end_col; ++j)
        {
            int64_t sum = 0;
            for (int32_t k = 0; k < m; ++k)
            {
                sum += static_cast<int64_t>(A[i][k]) * static_cast<int64_t>(B[k][j]);
            }
            C[i][j] = sum;
        }
    }
}

std::vector<std::vector<int64_t>> blocksThreadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B,
                                                       const int32_t &BLOCK_SIZE)
{

    if (A.empty() || B.empty() || A[0].size() != B.size())
    {
        throw std::invalid_argument("The Matrices are not adjusted");
    }

    const int32_t n = A.size(), l = B[0].size();

    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(l, 0));

    std::vector<std::thread> threads;

    for (int32_t i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int32_t j = 0; j < l; j += BLOCK_SIZE)
        {
            threads.emplace_back(
                blocksMultiply,
                std::ref(A),
                std::ref(B),
                std::ref(C),
                i,
                j,
                BLOCK_SIZE);
        }
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return C;
}