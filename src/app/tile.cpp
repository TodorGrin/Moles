#include "tile.h"

Tile::Tile(const QColor &color, const QColor backgroundColor) :
    color_(color),
    backgroundColor_(backgroundColor),
    isBackground_(false)
{

}

Tile::Tile(const QColor backgroundColor) :
    backgroundColor_(backgroundColor),
    isBackground_(true)
{

}

void Tile::destroy() {
    isBackground_ = true;
}

QColor Tile::color() const {
    return isBackground_ ? backgroundColor_ : color_;
}

bool Tile::isBackground() const {
    return isBackground_;
}
