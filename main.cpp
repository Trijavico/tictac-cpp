#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>

using namespace std;

const char *ROW_DELIMITER = "+---+---+---+";

struct Game {
  char board[3][3];
  char currentTurn = 'o';
  int length;

  void play(size_t x_pos, size_t y_pos) {
    this->board[x_pos - 1][y_pos - 1] = this->currentTurn;
    this->length++;
  }

  bool gotWinner() {
    // rows
    for (size_t i = 0; i < 3; ++i) {
      if (board[i][0] != ' ' && board[i][0] == board[i][1] &&
          board[i][1] == board[i][2]) {
        return true;
      }
    }

    // columns
    for (size_t j = 0; j < 3; ++j) {
      if (board[0][j] != ' ' && board[0][j] == board[1][j] &&
          board[1][j] == board[2][j]) {
        return true;
      }
    }

    // diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
      return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
      return true;
    }

    return false;
  }

  bool isFull() const { return this->length == 9; }

  bool isFreePosition(size_t x, size_t y) {
    return this->board[x - 1][y - 1] == ' ';
  }

  void printBoard() const {
    cout << "  1   2   3  " << endl;
    cout << ROW_DELIMITER << endl;
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        std::cout << "| " << board[i][j] << " ";
      }
      cout << "| " << (i + 1) << endl;
      cout << ROW_DELIMITER << endl;
    }
  }
};

void clearCLI() {
#if defined(__WIN32__)
  system("cls");
#elif defined(__linux__)
  system("clear");
#endif
}

int main() {
  Game game = {{{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}};
  size_t pos[2] = {0, 0};

  while (!game.isFull()) {
    clearCLI();
    game.printBoard();
    cout << "Current Turn: Player '" << game.currentTurn << "'" << endl;

    while (true) {
      cout << endl << "Enter x position: ";
      cin >> pos[0];

      cout << "Enter y position: ";
      cin >> pos[1];

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\nInvalid input. Please enter numeric values." << endl;

      } else if (pos[0] <= 0 || pos[1] <= 0 || pos[0] >= 4 || pos[1] >= 4) {
        cout << endl << "Enter values between 1 through 3." << endl;

      } else if (!game.isFreePosition(pos[0], pos[1])) {
        cout << endl << "Position already filled" << endl;

      } else {
        break;
      }
    }

    game.play(pos[0], pos[1]);

    if (game.gotWinner()) {
      clearCLI();
      game.printBoard();
      cout << "Player '" << game.currentTurn << "' wins!" << endl;
      return 0;
    }

    game.currentTurn = (game.currentTurn == 'x') ? 'o' : 'x';
  }

  return 0;
}
