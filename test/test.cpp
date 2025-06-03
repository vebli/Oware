#include "GameLogic.hpp"
#include "test.hpp"
#include <iostream>

// std::vector<bool (*)()> tests = {
//     test_legal_moves1,
//     test_legal_moves2,
//     test_minimax
// };
//
//
// int main(){
//     for (size_t i = 0; i < tests.size(); ++i) {
//         std::cout << "Test " << i << ": " << (tests[i]() ? "PASSED" : "FAILED") << "\n";
//     }
//     return 0;
// }

int main(){
    test_getLegalMoves();
}
