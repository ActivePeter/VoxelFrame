#pragma once
#include "event_sys/VF_EventListener.h"
#include "event_sys/VF_EventPublisher.h"
// #include ""
namespace VoxelFrame
{
    class PublisherClass(MouseMove);
    class ListenerClass(MouseMove);

    class ListenerClass(MouseMove)
    {
        ListenerClassBody(MouseMove);

    public:
        virtual void ListenerCallback(MouseMove)(int x, int y, int dx, int dy) = 0;
    };

    class PublisherClass(MouseMove){
        PublisherClassBody(MouseMove)

    };

}