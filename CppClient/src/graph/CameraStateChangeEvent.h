#pragma once
//#include "event_sys/VF_EventListener.h"
//#include "event_sys/VF_EventPublisher.h"
#include "event_sys/VF_Event.h"
// #include ""
//namespace VoxelFrame
//{

VF_EventNamespaceBegin enum class CameraStateChangeType { Rotate
};
class CameraStateChange_EventPublisher;

class CameraStateChange_EventListener;

class CameraStateChange_EventListener
{
    ListenerClassBody(CameraStateChange);

public:
    virtual void CameraStateChange_ListenerCallback(Camera &cam, const CameraStateChangeType &stateChangeType) = 0;
};

class CameraStateChange_EventPublisher
{
    PublisherClassBody(CameraStateChange);

    void pub2All(Camera &cam, const CameraStateChangeType &stateChangeType)
    {
        for (auto &i : listeners)
        {
            i->CameraStateChange_ListenerCallback(cam, stateChangeType);
        }
    }
};

VF_EventNamespaceEnd