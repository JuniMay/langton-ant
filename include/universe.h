#include <cstdint>
#include <iostream>
#include <vector>

#include <common.h>

using namespace std;

enum Cell {
  Dead = 0,
  Alive = 1,
};

enum Direction {
  Up = 0,
  Left = 1,
  Right = 2,
  Down = 3,
};

class Universe {
 private:
  uint32_t height, width;
  uint32_t p_row, p_col;
  Direction direction;
  vector<Cell> cells{vector<Cell>(height * width, Dead)};

 public:
  Universe(uint32_t _width, uint32_t _height, uint32_t _p_row, uint32_t _p_col, Direction _direction);
  ~Universe();

  void set_cell(uint32_t row, uint32_t col, Cell state);
  Cell get_cell(uint32_t row, uint32_t col);
  uint32_t get_index(uint32_t row, uint32_t col) const;
  void evolve();

  cells_output_t output(uint32_t on, uint32_t off);

  friend ostream &operator<<(ostream &stream, const Universe &u);
};
