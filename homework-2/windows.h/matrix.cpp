#pragma once
#include "matrix.h"

std::vector<std::vector<int32_t>> createMatrix(const int32_t n)
{
    std::vector<std::vector<int32_t>> matrix(n, std::vector<int32_t>(n, 0));
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            matrix[i][j] = static_cast<int32_t>(rand()) % 21;
        }
    }
    return matrix;
}

void print(const std::vector<std::vector<int64_t>> &matrix)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
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

void blocksMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B, std::vector<std::vector<int64_t>> &C,
                    const int32_t &start_col, const int32_t &start_row, const int32_t &BLOCK_SIZE)
{
    const int32_t n = A.size(), m = A[0].size(), l = B[0].size();
    const int32_t end_row = std::min(start_row + BLOCK_SIZE, n);
    const int32_t end_col = std::min(start_col + BLOCK_SIZE, l);

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

struct RowData
{
    const std::vector<std::vector<int32_t>> *A;
    const std::vector<std::vector<int32_t>> *B;
    std::vector<std::vector<int64_t>> *C;

    int32_t start_row;
    int32_t end_row;
};

struct BlockData
{
    const std::vector<std::vector<int32_t>> *A;
    const std::vector<std::vector<int32_t>> *B;
    std::vector<std::vector<int64_t>> *C;

    int32_t start_row;
    int32_t start_col;
    int32_t BLOCK_SIZE;
};

DWORD WINAPI rowsMultiplyThread(LPVOID lpParam)
{
    RowData *data = static_cast<RowData *>(lpParam);
    rowsMultiply(*data->A, *data->B, *data->C, data->start_row, data->end_row);
    delete data;
    return 0;
}

DWORD WINAPI blocksMultiplyThread(LPVOID lpParam)
{
    BlockData *data = static_cast<BlockData *>(lpParam);
    blocksMultiply(*data->A, *data->B, *data->C, data->start_col, data->start_row, data->BLOCK_SIZE);
    delete data;
    return 0;
}

std::vector<std::vector<int64_t>> threadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B)
{
    if (A.empty() || B.empty() || A[0].size() != B.size())
    {
        throw std::invalid_argument("The Matrices are not adjusted");
    }

    const int32_t n = A.size();
    const int32_t l = B[0].size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(l, 0));

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    uint32_t num_threads = sysInfo.dwNumberOfProcessors;
    num_threads = num_threads == 0 ? 2 : num_threads;
    num_threads = std::min(static_cast<uint32_t>(n), num_threads);

    std::vector<HANDLE> threads(num_threads);
    const int32_t rows_per_thread = n / num_threads;
    int32_t current_start_row = 0;

    for (uint32_t i = 0; i < num_threads; ++i)
    {
        int32_t current_end_row = current_start_row + rows_per_thread;
        if (i == num_threads - 1)
        {
            current_end_row = n;
        }

        RowData *data = new RowData{&A, &B, &C, current_start_row, current_end_row};
        threads[i] = CreateThread(NULL, 0, rowsMultiplyThread, data, 0, NULL);
        current_start_row = current_end_row;
    }

    WaitForMultipleObjects(threads.size(), threads.data(), TRUE, INFINITE);

    for (HANDLE hThread : threads)
    {
        CloseHandle(hThread);
    }

    return C;
}

std::vector<std::vector<int64_t>> blocksThreadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B,
                                                       const int32_t &BLOCK_SIZE)
{
    if (A.empty() || B.empty() || A[0].size() != B.size())
    {
        throw std::invalid_argument("The Matrices are not adjusted");
    }

    const int32_t n = A.size();
    const int32_t l = B[0].size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(l, 0));

    std::vector<HANDLE> threads;

    for (int32_t i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int32_t j = 0; j < l; j += BLOCK_SIZE)
        {
            BlockData *data = new BlockData{&A, &B, &C, j, i, BLOCK_SIZE};
            HANDLE hThread = CreateThread(NULL, 0, blocksMultiplyThread, data, 0, NULL);
            if (hThread)
            {
                threads.push_back(hThread);
            }
        }
    }

    if (!threads.empty())
    {
        WaitForMultipleObjects(threads.size(), threads.data(), TRUE, INFINITE);
    }

    for (HANDLE hThread : threads)
    {
        CloseHandle(hThread);
    }

    return C;
}