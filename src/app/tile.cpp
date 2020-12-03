#include "tile.h"

Tile::Tile(const QColor &color, bool isBackground) : color_(color), isBackground_(isBackground) {

}

QColor Tile::color() {
    return color_;
}

bool Tile::isBackground() {
    return isBackground_;
}
