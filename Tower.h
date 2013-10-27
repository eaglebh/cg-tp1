#ifndef TOWER_H
#define TOWER_H

#include "HasGraphicalRepresentation.h"


class Tower : public HasGraphicalRepresentation
{
private:
    const static char *TOWER_TYPE;
public:
    Tower(long id);
};

#endif // TOWER_H
