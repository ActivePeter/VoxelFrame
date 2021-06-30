#pragma once

/**
 * only used for singleton
 *   ecs should be the first choice
 * */
class IUpdaterBeforePhysic
{
private:
    /* data */
public:
    virtual void updaterBeforePhysic() {}
};
