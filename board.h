#include <vector>
using namespace std;
#include "zone.h"

class Board {
public:
  Board();
  ~Board();
  vector<vector<Zone>> getMyBoard();
  void setMyBoard(vector<vector<Zone>>);
  int getWidth();
  void setWidth(int);
  int getHeight();
  void setHeight(int);
  int getNumMines();
  void setNumMines(int);
  int getNumRemSquares();
  void setNumRemSquares(int);
  int getNumRemMines();
  void setNumRemMines(int);
  void createBoard();
  void placeBombs();
  void placeNumbers();
  void revealNumbers(int, int);
  void displayBoard();
  char youLose();
  char youWin();
private:
  vector<vector<Zone>> myBoard; // 2 dimensional vector of zones
  int width; // width of board (number of squares)
  int height; // height of board (number of squares)
  int numMines; // number of mines
  int numRemSquares; // number of remaining squares that need to be cleared
  int numRemMines; // number of mines that have not been flagged
};
