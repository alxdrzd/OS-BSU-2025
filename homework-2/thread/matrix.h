//
// Created by alxdrzd on 10/26/25.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <chrono>
#include <thread>

std::vector<std::vector<int32_t>> createMatrix(int32_t);

void print(const std::vector<std::vector<int64_t>> &);

std::vector<std::vector<int64_t>> simpleMultiplication(const std::vector<std::vector<int32_t>> &, const std::vector<std::vector<int32_t>> &);

void rowsMultiply(const std::vector<std::vector<int32_t>> &, const std::vector<std::vector<int32_t>> &, std::vector<std::vector<int64_t>> &,
                  int32_t, int32_t);

std::vector<std::vector<int64_t>> threadMultiply(const std::vector<std::vector<int32_t>> &, const std::vector<std::vector<int32_t>> &);

void blocksMultiply(const std::vector<std::vector<int32_t>> &, const std::vector<std::vector<int32_t>> &, std::vector<std::vector<int64_t>> &,
                    const int32_t &, const int32_t &, const int32_t &);

std::vector<std::vector<int64_t>> blocksThreadMultiply(const std::vector<std::vector<int32_t>> &, const std::vector<std::vector<int32_t>> &, const int32_t &);

#endif // MATRIX_H
