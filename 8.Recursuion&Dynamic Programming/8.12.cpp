// Eight Queens: Write an algorithm to print all ways of arranging eight queens
// on an 8x8 chess board so that none of them share the same row, column, or
// diagonal. In this case, "diagonal" means all diagonals, not just the two that
// bisect the board.

#include <cmath>
#include <deque>
#include <vector>

const int GRID_SIZE = 8;

bool checkValid(std::vector<int>& columns, int row1, int column1);

void placeQueens(int row,
                 std::vector<int>& columns,
                 std::deque<std::vector<int>>& results) {
  if (row == GRID_SIZE) {
    // Found valid placement
    results.push_back(columns);
  } else {
    for (int col = 0; col < GRID_SIZE; ++col) {
      if (checkValid(columns, row, col)) {
        columns[row] = col;  // Place queen
        placeQueens(row + 1, columns, results);
      }
    }
  }
}

// Check if (row1, column1) is a valid spot for a queen by checking if there is
// a queen in the same column or diagonal. We don't need to check it for queens
// in the same row because the calling placeQueen only attempts to place one
// queen at a time. We know this row is empty.
bool checkValid(std::vector<int>& columns, int row1, int column1) {
  for (int row2 = 0; row2 < row1; ++row2) {
    auto column2 = columns[row2];

    // Check if (row2, column2) invalidates (row1, column1) as a queen spot.

    // Check if rows have a queen in the same column
    if (column1 == column2)
      return false;

    // Check diagonals: if the distance between the columns equals the distance
    // between the rows, then they're in the same diagonal.
    auto columnDistance = std::abs(column2 - column1);

    // row1 > row2, so no need for abs
    auto rowDistance = row1 - row2;
    if (columnDistance == rowDistance)
      return false;
  }
  return true;
}

int main(){
}
