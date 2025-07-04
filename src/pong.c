#include <stdio.h>

// Объявляем все функции до их использования
void screenRendering(int racket1, int racket2, int ball_x, int ball_y, int score1, int score2, int width,
                     int height);
int moveRacket(int racket_y, char input, int height, int isLeft);
int checkRacketCollision(int racket_y, int height);
int checkWallCollision(int ball_y, int vector_y, int height);
int checkRacketBallCollision(int ball_x, int ball_y, int vector_x, int racket1, int racket2, int width);
int checkScore(int ball_x, int width);
void congratulations(int winner, int width, int height);
void clearScreen(void);

int main(void) {
    int width = 80, height = 25;
    int winning_score = 21;
    int score_player_1 = 0;
    int score_player_2 = 0;

    clearScreen();

    // Главный игровой цикл (пока кто-то не наберёт 21 очко)
    while (score_player_1 < winning_score && score_player_2 < winning_score) {
        int center_y = height / 2;  // Центр поля по высоте
        int racket1 = center_y;
        int racket2 = center_y;
        int ball_x = width / 2;
        int ball_y = center_y;
        int vector_x = (score_player_1 + score_player_2) % 2 == 0 ? -1 : 1;
        int vector_y = 1;

        int round_over = 0;  // Флаг завершения раунда

        // Цикл одного раунда (пока раунд не завершён)
        while (!round_over) {
            screenRendering(racket1, racket2, ball_x, ball_y, score_player_1, score_player_2, width, height);
            char input = getchar();

            if (input == 'q' || input == 'Q') return 0;

            if (input == 'a' || input == 'z' || input == 'k' || input == 'm' || input == 'A' ||
                input == 'Z' || input == 'K' || input == 'M' || input == ' ') {
                if (input != ' ') {
                    racket1 = moveRacket(racket1, input, height, 1);
                    racket2 = moveRacket(racket2, input, height, 0);
                }

                ball_x += vector_x;
                ball_y += vector_y;

                vector_y = checkWallCollision(ball_y, vector_y, height);
                vector_x = checkRacketBallCollision(ball_x, ball_y, vector_x, racket1, racket2, width);

                int winner = checkScore(ball_x, width);
                if (winner == 1) {
                    score_player_1++;
                    round_over = 1;  // Раунд завершён, игрок 1 забил гол
                } else if (winner == 2) {
                    score_player_2++;
                    round_over = 1;  // Раунд завершён, игрок 2 забил гол
                }
            }
        }
    }

    // Показываем экран поздравления победителя
    congratulations((score_player_1 > score_player_2 ? 1 : 2), width, height);
    return 0;
}

void clearScreen(void) { printf("\033[H\033[J"); }

int checkRacketCollision(int racket_y, int height) {
    if (racket_y < 2) return 2;
    if (racket_y > height - 3) return height - 3;
    return racket_y;
}

int moveRacket(int racket_y, char input, int height, int isLeft) {
    if (isLeft) {
        if (input == 'a' || input == 'A') return checkRacketCollision(racket_y - 1, height);
        if (input == 'z' || input == 'Z') return checkRacketCollision(racket_y + 1, height);
    } else {
        if (input == 'k' || input == 'K') return checkRacketCollision(racket_y - 1, height);
        if (input == 'm' || input == 'M') return checkRacketCollision(racket_y + 1, height);
    }
    return racket_y;
}

int checkWallCollision(int ball_y, int vector_y, int height) {
    if (ball_y == 1 || ball_y == height - 2) {
        return -vector_y;
    }
    return vector_y;
}

int checkRacketBallCollision(int ball_x, int ball_y, int vector_x, int racket1, int racket2, int width) {
    if (ball_x == 4 && (ball_y == racket1 - 1 || ball_y == racket1 || ball_y == racket1 + 1)) {
        return -vector_x;
    }
    if (ball_x == width - 5 && (ball_y == racket2 - 1 || ball_y == racket2 || ball_y == racket2 + 1)) {
        return -vector_x;
    }
    return vector_x;
}

int checkScore(int ball_x, int width) {
    if (ball_x <= 1) return 2;
    if (ball_x >= width - 2) return 1;
    return 0;
}

void congratulations(int winner, int width, int height) {
    clearScreen();

    // Верхняя граница
    for (int i = 0; i < width; i++) printf("#");
    printf("\n");

    for (int y = 0; y < height - 2; y++) {
        printf("#");

        if (y == height / 4) {
            // Центрируем текст "PLAYER X WINS!"
            for (int i = 0; i < (width - 32) / 2; i++) printf(" ");
            printf("CONGRATULATIONS, PLAYER %d!", winner);
            for (int i = 0; i < (width - 24) / 2; i++) printf(" ");
        } else {
            // Пустое пространство
            for (int i = 0; i < width - 2; i++) printf(" ");
        }

        printf("#\n");
    }

    // Нижняя граница
    for (int i = 0; i < width; i++) printf("#");
    printf("\n");
}

void screenRendering(int racket1, int racket2, int ball_x, int ball_y, int score1, int score2, int width,
                     int height) {
    clearScreen();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == ball_x && y == ball_y) {
                printf("o");  // Мячик
            } else if (y == 0 || y == height - 1) {
                printf("-");  // Верхняя и нижняя границы поля
            } else if (x == 0 || x == width - 1) {
                printf("|");  // Левая и правая границы поля
            } else if (x == width / 2) {
                printf("|");  // Вертикальная линия по центру поля
            } else if ((x == 3 && (y == racket1 - 1 || y == racket1 || y == racket1 + 1)) ||
                       (x == width - 4 && (y == racket2 - 1 || y == racket2 || y == racket2 + 1))) {
                printf("|");  // Ракетки
            } else if (y == 2 && x == width / 4) {
                printf("%d", score1);  // Счёт игрока 1
            } else if (y == 2 && x == (3 * width) / 4) {
                printf("%d", score2);  // Счёт игрока 2
            } else {
                printf(" ");  // Пустое пространство
            }
        }
        printf("\n");
    }
}

