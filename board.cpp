#include <cstdlib>
#include <string>
#include <sstream>
#include "board.h"
#include "gfx2.h"
using namespace std;

Board::Board()
{
  width = 30;
  height = 16;
  numMines = 99;
  numRemSquares = width*height - numMines;
  numRemMines = 99;
  for (int w = 0; w < width; w++) {
    vector<Zone> myZones;
    Zone currentZone;
    for (int h = 0; h < height; h++) {
      currentZone.setX(w);
      currentZone.setY(h);
      myZones.push_back(currentZone);
    }
    myBoard.push_back(myZones);
  }
}

Board::~Board()
{  }

vector<vector<Zone>> Board::getMyBoard()
{
  return myBoard;
}

void Board::setMyBoard(vector<vector<Zone>> z)
{
  myBoard = z;
}

int Board::getWidth()
{
  return width;
}

void Board::setWidth(int w)
{
  width = w;
}

int Board::getHeight()
{
  return height;
}

void Board::setHeight(int h)
{
  height = h;
}

int Board::getNumMines()
{
  return numMines;
}

void Board::setNumMines(int n)
{
  numMines = n;
}

int Board::getNumRemSquares()
{
  return numRemSquares;
}

void Board::setNumRemSquares(int n)
{
  numRemSquares = n;
}

int Board::getNumRemMines()
{
  return numRemMines;
}

void Board::setNumRemMines(int n)
{
  numRemMines = n;
}

void Board::createBoard()
{
  placeBombs();
  placeNumbers();
}

void Board::placeBombs()
{
  int n = 0; // Keeps track of current number of mines placed
  while (n < getNumMines()) {
    int w = rand()%width; // random width coordinate
    int h = rand()%height; // random height coordinate

    // If not already a mine, add a mine and increment n
    if (myBoard[w][h].getMineStatus() == false) {
      myBoard[w][h].setMineStatus(true);
      n++;
    }
  }
}

void Board::placeNumbers()
{
  // Count number of surrounding mines
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {

      // Account for edge zones
      if (!myBoard[w][h].getMineStatus()) {
        if (w != 0 && h != 0)
          if (myBoard[w-1][h-1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (w != 0)
          if(myBoard[w-1][h].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (w != 0 && h != height - 1)
          if(myBoard[w-1][h+1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (h != height - 1)
          if(myBoard[w][h+1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (w != width - 1 && h != height - 1)
          if(myBoard[w+1][h+1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (w != width - 1)
          if(myBoard[w+1][h].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (w != width - 1 && h != 0)
          if(myBoard[w+1][h-1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

        if (h != 0)
          if(myBoard[w][h-1].getMineStatus()) myBoard[w][h].setValue(myBoard[w][h].getValue() + 1);

      } else {
        myBoard[w][h].setValue(-1);
      }
    }
  }
}

void Board::revealNumbers(int x, int y)
{
  int val = myBoard[x][y].getValue();
  myBoard[x][y].setRevealedStatus(true);
  numRemSquares--;
  if (val != 0) {
    // check all neighbors, if any are 0 and have not been revealed yet, reveal those. Also account for edge squares
    if (x != 0 && y != 0)
      if (myBoard[x-1][y-1].getValue() == 0 && !myBoard[x-1][y-1].getRevealedStatus()) revealNumbers(x-1, y-1);

    if (x != 0)
      if(myBoard[x-1][y].getValue() == 0 && !myBoard[x-1][y].getRevealedStatus()) revealNumbers(x-1, y);

    if (x != 0 && y != height - 1)
      if(myBoard[x-1][y+1].getValue() == 0 && !myBoard[x-1][y+1].getRevealedStatus()) revealNumbers(x-1, y+1);

    if (y != height - 1)
      if(myBoard[x][y+1].getValue() == 0 && !myBoard[x][y+1].getRevealedStatus()) revealNumbers(x, y+1);

    if (x != width - 1 && y != height - 1)
      if(myBoard[x+1][y+1].getValue() == 0 && !myBoard[x+1][y+1].getRevealedStatus()) revealNumbers(x+1, y+1);

    if (x != width - 1)
      if(myBoard[x+1][y].getValue() == 0 && !myBoard[x+1][y].getRevealedStatus()) revealNumbers(x+1, y);

    if (x != width - 1 && y != 0)
      if(myBoard[x+1][y-1].getValue() == 0 && !myBoard[x+1][y-1].getRevealedStatus()) revealNumbers(x+1, y-1);

    if (y != 0)
      if(myBoard[x][y-1].getValue() == 0 && !myBoard[x][y-1].getRevealedStatus()) revealNumbers(x, y-1);


  } else if (val == 0) {
    // reveal all neighbors. Account for edge squares
    if (x != 0 && y != 0)
      if (!myBoard[x-1][y-1].getRevealedStatus()) revealNumbers(x-1, y-1);

    if (x != 0)
      if(!myBoard[x-1][y].getRevealedStatus()) revealNumbers(x-1, y);

    if (x != 0 && y != height - 1)
      if(!myBoard[x-1][y+1].getRevealedStatus()) revealNumbers(x-1, y+1);

    if (y != height - 1)
      if(!myBoard[x][y+1].getRevealedStatus()) revealNumbers(x, y+1);

    if (x != width - 1 && y != height - 1)
      if(!myBoard[x+1][y+1].getRevealedStatus()) revealNumbers(x+1, y+1);

    if (x != width - 1)
      if(!myBoard[x+1][y].getRevealedStatus()) revealNumbers(x+1, y);

    if (x != width - 1 && y != 0)
      if(!myBoard[x+1][y-1].getRevealedStatus()) revealNumbers(x+1, y-1);

    if (y != 0)
      if(!myBoard[x][y-1].getRevealedStatus()) revealNumbers(x, y-1);

  }

}

void Board::displayBoard()
{
  // Start by clearing off previous board
  gfx_clear_color(200, 200, 200);
  gfx_clear();

  gfx_color(100,100,100);
  gfx_fill_rectangle(0,497,931,100);

  gfx_color(0,0,0);
  int numPixels = 30;

  // Display vertical grid lines
  for (int x = 0; x < (numPixels+1)*getWidth()+1; x+=(numPixels+1)) {
    gfx_line(x,0,x,(numPixels+1)*getHeight());
  }

  // Display horizontal grid lines
  for (int y = 0; y < (numPixels+1)*getHeight()+1; y+=(numPixels+1)) {
    gfx_line(0,y,(numPixels+1)*getWidth(),y);
  }

  // Display numbers and flags if appropriate
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int xPixel = 10 + 31*x, yPixel = 25 + 31*y;
      int val = myBoard[x][y].getValue();
      if (myBoard[x][y].getFlaggedStatus()) {
        gfx_color(198,109,13); // change color to orange
        gfx_text(xPixel, yPixel, "F");
      }

      if (myBoard[x][y].getRevealedStatus()) {
        switch (val) {
          case 0:
            gfx_color(255,255,255); // change color to white
            break;
          case 1:
            gfx_color(0,0,255); // change color to blue
            break;
          case 2:
            gfx_color(28,135,37); // change color to green
            break;
          case 3:
            gfx_color(255,0,0); // change color to red
            break;
          case 4:
            gfx_color(57,15,140); // change color to indigo
            break;
          case 5:
            gfx_color(96,6,12); // change color to brown
            break;
          case 6:
            gfx_color(22,150,173); // change color to teal
            break;
          case 7:
            gfx_color(177,0,209); // change color to purple
            break;
          case 8:
            gfx_color(0,0,0); // change color to black
            break;
        }

	// If not a bomb, display the value on the board
        if (val != -1) {
          stringstream ss;
          ss << val;
          string strVal = ss.str();
          char* charVal = (char*) strVal.c_str();
          gfx_text(xPixel, yPixel, charVal);
        }
      }
    }
  }

  // Now display controls and mines remaining on the bottom of the board
  gfx_color(0,0,0); // Set color to black
  gfx_changefont("6x10"); // Make font smaller
  gfx_text(150, 510, "Controls:");
  gfx_text(150, 525, "- left click: clear square");
  gfx_text(150, 540, "- right click or f: toggle flag");
  gfx_text(150, 555, "- r: reset board");
  gfx_text(150, 570, "- q: quit game");

  // Convert number of remaining mines to a char*
  stringstream ss;
  ss << numRemMines;
  string strNumRemMines = ss.str();
  char* charNumRemMines = (char*) strNumRemMines.c_str();

  gfx_text(600, 535, "Number of remaining mines:");
  gfx_text(600, 559, charNumRemMines);
  
  gfx_changefont("12x24"); // Change font back
}

char Board::youLose()
{
  gfx_clear_color(200,200,200); // Set the background color to light gray
  gfx_clear();

  gfx_color(0,0,255); // Set losing color to blue, a sad color

  char* text1 = "Sorry! You Lose! Choose an Option:";
  char* text2 = "r: Reset board and play again";
  char* text3 = "q: Quit game";

  int l1 = gfx_textpixelwidth(text1,"12x24");
  int h1 = gfx_textpixelheight(text1, "12x24");
  int l2 = gfx_textpixelwidth(text2, "12x24");
  int h2 = gfx_textpixelheight(text2, "12x24");
  int l3 = gfx_textpixelwidth(text3,"12x24");
  int h3 = gfx_textpixelheight(text3, "12x24");

  int w = gfx_windowwidth();
  int h = gfx_windowheight();

  gfx_text((w-l1)/2, (h/2) - 2*h2, text1);
  gfx_text((w-l2)/2, (h/2), text2);
  gfx_text((w-l3)/2, (h/2) + 2*h2, text3);

  char c = gfx_wait();
  while (c != 'r' && c != 'q') {
    c = gfx_wait();
  }
  return c;
}

char Board::youWin()
{
  gfx_clear_color(200,200,200); // Set the background color to light gray
  gfx_clear();

  gfx_color(59,173,55); // Set winning color to green, a happy color

  char* text1 = "Congrats! You Win! Choose an Option:";
  char* text2 = "r: Reset board and play again";
  char* text3 = "q: Quit game";

  int l1 = gfx_textpixelwidth(text1,"12x24");
  int h1 = gfx_textpixelheight(text1, "12x24");
  int l2 = gfx_textpixelwidth(text2, "12x24");
  int h2 = gfx_textpixelheight(text2, "12x24");
  int l3 = gfx_textpixelwidth(text3,"12x24");
  int h3 = gfx_textpixelheight(text3, "12x24");

  int w = gfx_windowwidth();
  int h = gfx_windowheight();

  gfx_text((w-l1)/2, (h/2) - 2*h2, text1);
  gfx_text((w-l2)/2, (h/2), text2);
  gfx_text((w-l3)/2, (h/2) + 2*h2, text3);

  char c = gfx_wait();
  while (c != 'r' && c != 'q') {
    c = gfx_wait();
  }
  return c;
}
