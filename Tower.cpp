#include "Tower.h"

const char *Tower::TOWER_TYPE = "TOWER";

Tower::Tower(long id):
    HasGraphicalRepresentation(id, TOWER_TYPE)
{
}
