#include "matrix.h"

int main()
{
    const std::vector<std::vector<int32_t>> A = createMatrix(1000);
    const std::vector<std::vector<int32_t>> B = createMatrix(1000);

    const auto simple_start = std::chrono::system_clock::now();
    std::vector<std::vector<int64_t>> C_1 = simpleMultiplication(A, B);

    const auto simple_end = std::chrono::system_clock::now();

    const auto rows_start = std::chrono::system_clock::now();
    std::vector<std::vector<int64_t>> C_2 = threadMultiply(A, B);

    const auto rows_end = std::chrono::system_clock::now();

    const auto blocks_start = std::chrono::system_clock::now();

    std::vector<std::vector<int64_t>> C_3 = blocksThreadMultiply(A, B, 16);

    const auto blocks_end = std::chrono::system_clock::now();

    std::cout
        << "with multithreading [rows]:   " << (rows_end - rows_start).count() << " ns" << '\n'
        << "with multithreading [blocks]: " << (blocks_end - blocks_start).count() << " ns" << '\n'
        << "without multithreading :      " << (simple_end - simple_start).count() << " ns" << '\n';
}