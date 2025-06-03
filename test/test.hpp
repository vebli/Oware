#pragma once
#include <GameLogic.hpp>
#include <string>
#include <vector>
#include <iostream>

#define EXPECT_EQ(actual, expected, name) \
    do { \
        auto a = (actual); \
        auto e = (expected); \
        if (a != e) { \
            std::cerr << name << ": FAILED"<< "\n" \
                      << "  Expected: " << e << "\n" \
                      << "  Actual:   " << a << "\n"; \
        } else { \
            std::cout << name << ": PASSED.\n"; \
        } \
    } while (0)

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) os << ", ";
    }
    os << "}";
    return os;
}

void test_getLegalMoves(){
    GameState s({10, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0}, {0, 0});
    EXPECT_EQ((getLegalMoves(s, player1)), (std::vector<int>{1, 5}), "Legal moves test 1");
    s = GameState({1, 0, 0, 0, 0, 0, 1, 5, 2, 4, 1, 18}, {4, 12});
    EXPECT_EQ((getLegalMoves(s, player2)), (std::vector<int>{1, 2, 3, 4, 5, 6}), "Legal moves test 2");
    s = GameState({0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 19, 2}, {4, 12});
    EXPECT_EQ((getLegalMoves(s, player2)), (std::vector<int>{3, 6}), "Legal moves test 3");
}


