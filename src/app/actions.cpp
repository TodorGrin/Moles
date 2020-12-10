#include "actions.h"
#include "weapons/bazooka.h"

Actions::Actions() : weapon(std::make_shared<Bazooka>()) {
}

void Actions::reset() {
    shoot = false;
    jump = false;
}
