#include "actions.h"
#include "weapons/uzi.h"

Actions::Actions() : weapon(std::make_shared<Uzi>()) {
}

void Actions::reset() {
    shoot = false;
    jump = false;
}
