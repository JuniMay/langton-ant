#include <memory>

#define HEIGHT 250
#define WIDTH 400
#define INIT_ROW 150
#define INIT_COL 300
#define INIT_DIR Up
#define SCALE 2
#define ON_COLOR 0x66D9EF
#define OFF_COLOR 0x272822

typedef std::unique_ptr<uint32_t[]> cells_output_t;