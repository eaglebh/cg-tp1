#ifndef HASGRAPHICALREPRESENTATION_H
#define HASGRAPHICALREPRESENTATION_H

#include "Graphical.h"

class HasGraphicalRepresentation
{
public:
    HasGraphicalRepresentation(long id, string type);
    void setPosition(Position position);

protected:
    Graphical graphical;
};

#endif // HASGRAPHICALREPRESENTATION_H
