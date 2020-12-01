#include "tile.h"

Tile::Tile(const QColor &color) : color_(color) {
}

QColor Tile::color() {
    return color_;
}
