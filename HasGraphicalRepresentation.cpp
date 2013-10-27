#include "HasGraphicalRepresentation.h"

HasGraphicalRepresentation::HasGraphicalRepresentation(long id):
    graphical(id)
{
}

void HasGraphicalRepresentation::setPosition(Position position)
{
    graphical.setRelativePosition(position);
}
