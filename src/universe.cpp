#include <cstdint>
#include <iostream>

#include <common.h>
#include <universe.h>

using namespace std;

Universe::Universe(uint32_t _height, uint32_t _width, uint32_t _p_row, uint32_t _p_col, Direction _direction)
    : height(_height), width(_width), p_row(_p_row), p_col(_p_col), direction(_direction) {}

Universe::~Universe() {}

void Universe::set_cell(uint32_t row, uint32_t col, Cell state) {
  cells[get_index(row, col)] = state;
}

Cell Universe::get_cell(uint32_t row, uint32_t col) {
  return cells[get_index(row, col)];
}

uint32_t Universe::get_index(uint32_t row, uint32_t col) const {
  return (row * width + col);
}

void Universe::evolve() {
  uint32_t idx = get_index(p_row, p_col);
  if (cells[idx] == Alive) {
    set_cell(p_row, p_col, Dead);
    switch (direction) {
      case Up:
        direction = Left;
        break;
      case Left:
        direction = Down;
        break;
      case Right:
        direction = Up;
        break;
      case Down:
        direction = Right;
        break;
    }
  } else {
    set_cell(p_row, p_col, Alive);
    switch (direction) {
      case Up:
        direction = Right;
        break;
      case Left:
        direction = Up;
        break;
      case Right:
        direction = Down;
        break;
      case Down:
        direction = Left;
        break;
    }
  }
  switch (direction) {
      case Up:
        p_row++;
        break;
      case Left:
        p_col--;
        break;
      case Right:
        p_col++;
        break;
      case Down:
        p_row--;
        break;
  }
}

cells_output_t Universe::output(uint32_t on, uint32_t off) {
  cells_output_t cells_output(new uint32_t[height * width]);
  for (uint32_t row = 0; row < height; row++) {
    for (uint32_t col = 0; col < width; col++) {
      uint32_t idx = get_index(row, col);
      if (cells[idx] == Alive) {
        cells_output[idx] = on;
      } else {
        cells_output[idx] = off;
      }
    }
  }
  return cells_output;
}

ostream &operator<<(ostream &stream, const Universe &u) {
  for (uint32_t row = 0; row < u.height; row++) {
    for (uint32_t col = 0; col < u.width; col++) {
      stream << (u.cells[u.get_index(row, col)] ? "◼" : "◻");
    }
    stream << endl;
  }
  return stream;
}