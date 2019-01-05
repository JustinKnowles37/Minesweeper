#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>
#include "board.h"
#include "gfx2.h"

void createBlankBoard(Board&);

int main() {

  // Set random seed to time
  srand(time(NULL));

  // Declare Variables
  Board gameBoard;
  Board blankBoard;
  int screenWidth = 931, screenHeight = 597;
  int numPixels = 30; // number of pixels per zone
  char c = '0'; // Initialize c with unused value

  // Open window
  gfx_open(screenWidth, screenHeight, "Minesweeper");

  // Create blank board
  createBlankBoard(gameBoard);

  while(c != 'q') {

    // Get user input
    c = gfx_wait();

    int x = floor(gfx_xpos()/(numPixels+1));
    int y = floor(gfx_ypos()/(numPixels+1));

    vector<vector<Zone>> v = gameBoard.getMyBoard(); // Used in cases 2, 'f'

    // Switch statement
    switch (c) {
      case 1: // Click on square
        if (!gameBoard.getMyBoard()[x][y].getFlaggedStatus()) {
          if (gameBoard.getMyBoard()[x][y].getMineStatus()) { // You lose if you click a mine
            c = gameBoard.youLose();
            if (c == 'r') { // Play again
              gfx_clear();
              gameBoard = blankBoard;
              createBlankBoard(gameBoard);
            } else if (c == 'q') { // Quit
              return 0;
            }
          } else {
            gameBoard.revealNumbers(x, y);
          }
          if (gameBoard.getNumRemSquares() == 0) { // You win when all non-mines are cleared
            c = gameBoard.youWin();
            if (c == 'r') {
              gfx_clear();
              gameBoard = blankBoard;
              createBlankBoard(gameBoard);
            } else if (c == 'q') {
              return 0;
            }
          }
      	}
      	break;
      case 3: // Place/remove flag
      case 'f': // Place/remove flag
        if (!gameBoard.getMyBoard()[x][y].getFlaggedStatus()) {
          v[x][y].setFlaggedStatus(true);
          gameBoard.setMyBoard(v);
          gameBoard.setNumRemMines(gameBoard.getNumRemMines() - 1);
        } else {
          v[x][y].setFlaggedStatus(false);
          gameBoard.setMyBoard(v);
          gameBoard.setNumRemMines(gameBoard.getNumRemMines() + 1);
        }
	      break;
      case 'r': // Restart game
        gfx_clear();
        gameBoard = blankBoard;
        createBlankBoard(gameBoard);
        break;
      case 'q': // Quit
        return 0;
        break;
      default:
	      break;
    }
    gameBoard.displayBoard();
  }
  return 0;
}

void createBlankBoard(Board& gameBoard) {
  // Change Font
  gfx_changefont("12x24");

  // Clear screen and then display board
  gfx_clear_color(200,200,200); // Set the background color to light gray
  gfx_clear();

  gfx_color(100,100,100);
  gfx_fill_rectangle(0,497,931,100);

  gameBoard.createBoard();
  gameBoard.displayBoard();
}
