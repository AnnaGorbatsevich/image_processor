#include "SharpFilter.h"

SharpFilter::SharpFilter() {
    matrix_ = {{0, -1, 0}, {-1, 4 + 1, -1}, {0, -1, 0}};
}
