#pragma once
#include "base/vf_base.h"
#include "VF_EventPublisher.h"

// #define ListenerClassHead2(x)
#define ListenerClass(x) x##EventListener //class ListenerClassHead2(x)
#define ListenerClassBody(x) \
public:                      \
    x##EventPublisher *listeningPublisher = NULL

#define ListenerCallback(x) x##ListenerCallback
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
