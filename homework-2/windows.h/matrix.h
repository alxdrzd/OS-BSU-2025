#ifndef MATRIX_H
#define MATRIX_H

#include <windows.h>
#undef min
#undef max

#include <chrono>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>

std::vector<std::vector<int32_t>> createMatrix(const int32_t n);

void print(const std::vector<std::vector<int64_t>> &matrix);

std::vector<std::vector<int64_t>> simpleMultiplication(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B);

std::vector<std::vector<int64_t>> threadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B);

std::vector<std::vector<int64_t>> blocksThreadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B,
                                                       const int32_t &BLOCK_SIZE);

#endif // MATRIX_H