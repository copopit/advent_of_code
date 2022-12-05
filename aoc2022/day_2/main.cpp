#include <iostream>
#include <fstream>

enum Scores {
    SCORE_ROCK = 1,
    SCORE_PAPER = 2,
    SCORE_SCISSORS = 3,
    WIN = 6,
    DRAW = 3,
};

enum Symbols {
    OPPONENT_ROCK = 'A',
    OPPONENT_PAPER = 'B',
    OPPONENT_SCISSORS = 'C',
    RESPONSE_ROCK = 'X',
    RESPONSE_PAPER = 'Y',
    RESPONSE_SCISSORS = 'Z',
};

int resolveScorePart1(const char opponent, const char response) {
    int score = 0;

    switch(opponent) {
        case OPPONENT_ROCK:
            if (response == RESPONSE_PAPER) {
                score += SCORE_PAPER + WIN;
            } else if (response == RESPONSE_ROCK) {
                score += SCORE_ROCK + DRAW;
            } else {
                score += SCORE_SCISSORS;
            }
            break;
        case OPPONENT_PAPER:
            if (response == RESPONSE_PAPER) {
                score += SCORE_PAPER + DRAW;
            } else if (response == RESPONSE_ROCK) {
                score += SCORE_ROCK;
            } else {
                score += SCORE_SCISSORS + WIN;
            }
            break;
        case OPPONENT_SCISSORS:
            if (response == RESPONSE_PAPER) {
                score += SCORE_PAPER;
            } else if (response == RESPONSE_ROCK) {
                score += SCORE_ROCK + WIN;
            } else {
                score += SCORE_SCISSORS + DRAW;
            }
            break;
        default:
            break;
    }

    return score;
}

int resolveScorePart2(const char opponent, const char response) {
    int score = 0;

    switch(opponent) {
        case OPPONENT_ROCK:
            if (response == 'Z') {
                score = SCORE_PAPER + WIN;
            } else if (response == 'Y') {
                score = SCORE_ROCK + DRAW;
            } else {
                score = SCORE_SCISSORS;
            }
            break;
        case OPPONENT_PAPER:
            if (response == 'Z') {
                score = SCORE_SCISSORS + WIN;
            } else if (response == 'Y') {
                score = SCORE_PAPER + DRAW;
            } else {
                score = SCORE_ROCK;
            }
            break;
        case OPPONENT_SCISSORS:
            if (response == 'Z') {
                score = SCORE_ROCK + WIN;
            } else if (response == 'Y') {
                score = SCORE_SCISSORS + DRAW;
            } else {
                score = SCORE_PAPER;
            }
            break;

        default: break;
    }

    return score;
}

int main() {
    std::fstream file("input.txt", std::fstream::in);

    int sum_p1 = 0, sum_p2 = 0;

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            sum_p1 += resolveScorePart1(line[0], line[2]);
            sum_p2 += resolveScorePart2(line[0], line[2]);
        }
    }

    file.close();


    std::cout << "Total score part 1: " << sum_p1 << std::endl;
    std::cout << "Total score part 2: " << sum_p2 << std::endl;

    return 0;
}
