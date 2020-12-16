#include "shotgun.h"

Shotgun::Shotgun() : Gun(0, 1, 10, 0.4, 5) {

}

void Shotgun::shoot(GameEngine &engine) {
    Gun::shoot(engine);
    angle_ -= scattering_;
    Gun::shoot(engine);
    angle_ += 2 * scattering_;
    Gun::shoot(engine);
    angle_ -= scattering_;
}

QString Shotgun::name() const {
    return "Shotgun";
}
