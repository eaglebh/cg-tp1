#include "HasGraphicalRepresentation.h"

HasGraphicalRepresentation::HasGraphicalRepresentation(long id, string type):
    graphical(id, type)
{
}

void HasGraphicalRepresentation::setPosition(Position position)
{
    graphical.setRelativePosition(position);
}
Graphical& HasGraphicalRepresentation::getGraphical()
{
    return graphical;
}

