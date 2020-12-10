#ifndef UZI_H
#define UZI_H

#include "gun.h"

class Uzi : public Gun {
    public:
        Uzi();

        virtual QString name() const override;
};

#endif // UZI_H
