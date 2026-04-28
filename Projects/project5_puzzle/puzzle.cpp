#include "puzzle.hpp"
#include <stdexcept>
#include <cmath> // for abs

bool Puzzle::fromString(const std::string &str)
{
  if (str.size() != 9)
  {
    return false;
  }
  bool seen[9] = {false, false, false, false, false, false, false, false, false};
  for (int i = 0; i < 9; ++i)
  {
    if ((str[i] < '0') || (str[i] > '8'))
      return false;
    int val = str[i] - '0';
    if (seen[val])
      return false;
    seen[val] = true;
    board[i] = static_cast<Tile>(val);
    if (board[i] == BLANK)
    {
      blankpos.row = i / 3;
      blankpos.col = i % 3;
    }
  }
  return true;
}

std::string Puzzle::toString() const
{
  std::string result;
  for (int i = 0; i < 9; ++i)
  {
    result.push_back('0' + board[i]);
  }
  return result;
}

Puzzle::Tile Puzzle::getLabel(Position p) const
{
  if ((p.row < 0) || (p.row > 2) || (p.col < 0) || (p.col > 2))
  {
    throw std::range_error("invalid row/column in Puzzle::getLabel");
  }
  return board[3 * p.row + p.col];
}

void Puzzle::setLabel(Position p, Tile tile)
{
  if ((p.row < 0) || (p.row > 2) || (p.col < 0) || (p.col > 2))
  {
    throw std::range_error("invalid row/column in Puzzle::setLabel");
  }
  board[3 * p.row + p.col] = tile;
}

std::pair<bool, Puzzle> Puzzle::apply(Action a) const
{
  Puzzle temp = *this;
  bool valid = false;
  int newRow = blankpos.row;
  int newCol = blankpos.col;
  if ((a == LEFT) && (blankpos.col > 0))
  {
    newCol -= 1;
    valid = true;
  }
  else if ((a == RIGHT) && (blankpos.col < 2))
  {
    newCol += 1;
    valid = true;
  }
  else if ((a == UP) && (blankpos.row > 0))
  {
    newRow -= 1;
    valid = true;
  }
  else if ((a == DOWN) && (blankpos.row < 2))
  {
    newRow += 1;
    valid = true;
  }
  if (valid)
  {
    int oldIndex = 3 * blankpos.row + blankpos.col;
    int newIndex = 3 * newRow + newCol;
    temp.board[oldIndex] = temp.board[newIndex];
    temp.board[newIndex] = BLANK;
    temp.blankpos.row = newRow;
    temp.blankpos.col = newCol;
  }
  return std::make_pair(valid, temp);
}

Image<Pixel> Puzzle::toPicture() const
{
  Image<Pixel> img = readFromFile("../lib/puzzle.png");
  int blockHeight = img.height() / 3;
  int blockWidth = img.width() / 3;
  Image<Pixel> rearrangedImg(img.height(), img.width());
  for (int blockIndex = 0; blockIndex < 9; ++blockIndex)
  {
    int srcBlockRow = board[blockIndex] / 3;
    int srcBlockCol = board[blockIndex] % 3;
    int destBlockRow = blockIndex / 3;
    int destBlockCol = blockIndex % 3;
    for (int r = 0; r < blockHeight; ++r)
    {
      for (int c = 0; c < blockWidth; ++c)
      {
        rearrangedImg(destBlockRow * blockHeight + r, destBlockCol * blockWidth + c) =
            img(srcBlockRow * blockHeight + r, srcBlockCol * blockWidth + c);
      }
    }
  }
  return rearrangedImg;
}

unsigned long long Puzzle::hash() const
{
  // TODO
  // use bitwise << and | to implemnt the concatenation
  // e.g., 2<<4 | 3 is actually hex 23, which is 35 in decimal
  unsigned long long result = 0;
  for (int i = 0; i < 9; ++i) {
    result = (result << 4) | board[i];  //multiply current result by 16 (shift left by 4) and bitwise OR with the next tile value
  }
  return result;
}

bool Puzzle::operator==(const Puzzle &rhs) const
{
  // TODO
  // do not compare tile by tile, use other public member functions
  return hash() == rhs.hash();  
  //Since hash() packs the entire board into one unique number, 
  // two puzzles are equal if and only if their hashes are equal — no need to compare tile by tile.
}

bool Puzzle::operator!=(const Puzzle &rhs) const
{
  // TODO
  // call the == operator i implemented above
  return !(*this == rhs);
}

int Puzzle::heuristic(const Puzzle &goal) const
{
  // TODO
  // Research Manhattan distance and implement the heuristic function
  int manhattanDistance = 0;
  // For each tile (except the blank), calculate the distance from its current
  // position to its goal position and sum these distances.
  for (int i = 0; i < 9; ++i)
  {
    if (board[i] != BLANK)
    {
      int tileValue = board[i]; // the value of the tile at index i
      int currentRow = i / 3; // the current row of the tile (0, 1, or 2)
      int currentCol = i % 3; // the current column of the tile (0, 1, or 2)
      int goalIndex = -1; // the index of the tile in the goal state
      /*
        i=0: row=0/3=0, col=0%3=0
        i=1: row=1/3=0, col=1%3=1
        i=2: row=2/3=0, col=2%3=2
        i=3: row=3/3=1, col=3%3=0
        i=4: row=4/3=1, col=4%3=1
        i=5: row=5/3=1, col=5%3=2
        i=6: row=6/3=2, col=6%3=0
        i=7: row=7/3=2, col=7%3=1
        i=8: row=8/3=2, col=8%3=2
      */
      // find the index of the tile in the goal state
      for (int j = 0; j < 9; ++j)
      {
        if (goal.board[j] == tileValue) // if the tile value matches the current tile, we found its position in the goal state
        {
          goalIndex = j;
          break;
        }
      }
      int goalRow = goalIndex / 3;
      int goalCol = goalIndex % 3;
      manhattanDistance += abs(currentRow - goalRow) + abs(currentCol - goalCol);
    }
  }
  return manhattanDistance;
}