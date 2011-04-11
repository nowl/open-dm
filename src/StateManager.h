#ifndef __STATE_MANAGER_H__
#define __STATE_MANAGER_H__

class DataReader;

class StateManager
{
public:
    StateManager(DataReader *dr);

    bool isEnterable(int x, int y);

private:
    DataReader *DataMan;
};

#endif // __STATE_MANAGER_H__
