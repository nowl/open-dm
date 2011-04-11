#include "OpenDM.h"

StateManager::StateManager(DataReader *dr)
    : DataMan(dr)
{}

bool
StateManager::isEnterable(int x, int y)
{
    return DataMan->getMapElement(x, y) == 1;
}
