#pragma once
#include "base/vf_base.h"
//#include "VF_EventPublisher.h"
//#include "VF_EventListner.h"
#include "VF_Event.h"
// #define ListenerClassHead2(x)
#define ListenerClass(x) x##_EventListener //class ListenerClassHead2(x)
#define ListenerClassBody(x) \
public:                      \
    x##_EventPublisher *listeningPublisher = NULL

#define ListenerCallback(x) x##_ListenerCallback
// namespace VoxelFrame
// {
//     // class EventPublisher;
//     class EventListener
//     {
//     private:
//         // EventPublisher *listeningPublisher = 0;
//         /* data */
//     public:
//     };

// }
