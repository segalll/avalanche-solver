#include <array>
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<std::vector<
        std::pair<std::vector<int>, std::array<int, 13>>
    >> continuingSequences = {{
        std::make_pair(
            std::vector<int>(),
            std::array<int, 13> {
                4, 4, 4, 4, 4, 4, // our side
                0, // our pot
                4, 4, 4, 4, 4, 4, // opponent side
            }
        )
    }};

    int sequenceLength = 1;

    while (true) {
        continuingSequences.push_back({});
        for (const auto& p : continuingSequences[sequenceLength - 1]) {
            for (int m = 1; m <= 6; m++) {
                std::array<int, 13> gameState = p.second;

                int currentMove = m - 1;
                bool firstIter = true;
                while (gameState[currentMove] > 1 || (firstIter && gameState[currentMove] > 0)) {
                    if (firstIter) firstIter = false;
                    int count = gameState[currentMove];
                    gameState[currentMove] = 0;
                    for (int j = 1; j <= count; j++) {
                        ++gameState[(currentMove + j) % 13];
                    }

                    if ((currentMove + count) % 13 == 6) { // final is our pot
                        std::vector<int> s = p.first;
                        s.push_back(m);
                        continuingSequences[sequenceLength].push_back(std::make_pair(s, gameState));
                        break;
                    }
                    currentMove = (currentMove + count) % 13;
                }
            }
        }

        if (continuingSequences[sequenceLength].size() == 0) {
            std::ofstream file;
            file.open("out.txt");
            for (int i = 1; i < sequenceLength; i++) {
                for (const auto& p : continuingSequences[i]) {
                    std::vector<int> s = p.first;
                    file << "\n";
                    for (int n : s) {
                        file << std::abs((n * 6) % 7) << " ";
                    }
                    file << "\n";
                    std::array<int, 13> gameState = p.second;
                    for (int k = 0; k < gameState.size(); k++) {
                        if (k == 6) {
                            file << "\n" << gameState[k] << "\n";
                        } else {
                            file << gameState[k] << " ";
                        }
                    }
                    file << "\n";
                }
            }
            return 0;
        }

        ++sequenceLength;
    }

    return 0;
}