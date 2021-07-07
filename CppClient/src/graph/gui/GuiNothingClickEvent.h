#pragma once
#include "event_sys/VF_EventListener.h"
#include "event_sys/VF_EventPublisher.h"
// #include ""
namespace VoxelFrame
{
    class PublisherClass(GuiNothingClick);
    class ListenerClass(GuiNothingClick);

    class ListenerClass(GuiNothingClick)
    {
        ListenerClassBody(GuiNothingClick);

    public:
        virtual void ListenerCallback(GuiNothingClick)() = 0;
    };

    class PublisherClass(GuiNothingClick){
        PublisherClassBody(GuiNothingClick)

    };

}