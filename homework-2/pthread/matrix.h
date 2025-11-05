#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <pthread.h>
#include <chrono>

std::vector<std::vector<int32_t>> createMatrix(const int32_t n);

std::vector<std::vector<int64_t>> simpleMultiplication(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B);

void rowsMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B, std::vector<std::vector<int64_t>> &C,
                  int32_t start_row, int32_t end_row);

void *rowsMultiply_wrapper(void *args);

std::vector<std::vector<int64_t>> threadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B);

void blocksMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B, std::vector<std::vector<int64_t>> &C,
                    const int32_t &start_row, const int32_t &start_col, const int32_t &BLOCK_SIZE);

void* blocksMultiply_wrapper(void* args);

std::vector<std::vector<int64_t>> blocksThreadMultiply(const std::vector<std::vector<int32_t>> &A, const std::vector<std::vector<int32_t>> &B,
                                                       const int32_t &BLOCK_SIZE);

