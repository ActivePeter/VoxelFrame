#pragma once

/**
 * only used for singleton
 *   ecs should be the first choice
 * */
class IUpdaterAfterPhysic
{
private:
    /* data */
public:
    virtual void updateAfterPhysic() {}
};
