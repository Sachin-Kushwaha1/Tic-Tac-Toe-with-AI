#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
public:
    TicTacToe() : board(9, 0), currentPlayer(-1) {} // Initialize board and current player (X starts)

    void play() {
        int choice;
        while (true) {
            cout << "Enter 1 for single player, 2 for multiplayer: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
            } else if (choice == 1 || choice == 2) {
                break;
            } else {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }

        isSinglePlayer = (choice == 1);

        if (isSinglePlayer) {
            char playerChoice;
            while (true) {
                cout << "Enter to play first (X) or second (O): ";
                cin >> playerChoice;
                if (playerChoice == 'X' || playerChoice == 'O' ||
                    playerChoice == 'x' || playerChoice == 'o') {
                    playerChoice = toupper(playerChoice);
                    if (playerChoice == 'O') {
                        computerMove(); // Computer starts if player chooses O
                    }
                    break;
                } else {
                    cout << "Invalid choice. Please enter X or O.\n";
                }
            }
        }

        while (true) {
            drawConsoleGUI();

            int result = analyzeBoard();
            if (result != -2) {
                if (result == 0) {
                    cout << "It's a Draw!!!\n";
                } else if (result == -1) {
                    cout << "X Wins :)\n";
                } else {
                    cout << "O Wins :)\n";
                }
                break;
            }

            if (isSinglePlayer && currentPlayer == 1) {
                computerMove();
            } else {
                handlePlayerMove();
            }

            currentPlayer = -currentPlayer;
        }

        cout << "Press Enter to Exit...";
        cin.ignore();
        cin.get();
    }

private:
    vector<int> board;
    int currentPlayer;
    bool isSinglePlayer;

    void displayBoard() const {
        cout << "Current State Of Board : \n\n";
        for (int i = 0; i < 9; ++i) {
            if (i > 0 && i % 3 == 0) {
                cout << "\n";
            }
            if (board[i] == 0) {
                cout << "- ";
            } else if (board[i] == 1) {
                cout << "O ";
            } else if (board[i] == -1) {
                cout << "X ";
            }
        }
        cout << "\n\n";
    }

    void handlePlayerMove() {
        int pos;
        while (true) {
            cout << "Enter " << ((currentPlayer == -1) ? 'X' : 'O') << "'s position from [1...9]: ";
            cin >> pos;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
            } else if (1 <= pos && pos <= 9 && board[pos - 1] == 0) {
                board[pos - 1] = currentPlayer;
                break;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    int analyzeBoard() const {
        const int winCombinations[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
            {0, 4, 8}, {2, 4, 6}  // Diagonals
        };

        for (int i = 0; i < 8; ++i) {
            if (board[winCombinations[i][0]] != 0 &&
                board[winCombinations[i][0]] == board[winCombinations[i][1]] &&
                board[winCombinations[i][0]] == board[winCombinations[i][2]]) {
                return board[winCombinations[i][0]];
            }
        }

        for (int i = 0; i < 9; ++i) {
            if (board[i] == 0) {
                return -2; // Game not over
            }
        }
        return 0; // Draw
    }

    int minimax(int player) {
        int result = analyzeBoard();
        if (result != -2) { 
            return result * player;
        }

        int bestScore = -2;
        int bestMove = -1;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == 0) {
                board[i] = player;
                int score = -minimax(-player);
                board[i] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }

        return bestScore;
    }

    void computerMove() {
        int bestScore = -2;
        int bestMove = -1;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == 0) {
                board[i] = 1;
                int score = -minimax(-1);
                board[i] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        board[bestMove] = 1;
    }

    void drawConsoleGUI() {
        // Clear the console (platform-specific, may need adjustment)
        system("cls"); // For Windows
        // system("clear"); // For macOS/Linux

        cout << "Tic-Tac-Toe\n\n";
        displayBoard();
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}