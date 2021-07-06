#pragma once
#include "vf_base.h"
#include "VF_EventListener.h"

// #define PublisherClassHead2(x)
#define PublisherClass(x) x##EventPublisher //class PublisherClassHead2(x)
#define PublisherClassBody(x)                     \
public:                                           \
    std::vector<ListenerClass(x) *> listeners;    \
    void addListener(ListenerClass(x) * listener) \
    {                                             \
        if (!listener->listeningPublisher)        \
        {                                         \
            listeners.push_back(listener);        \
            listener->listeningPublisher = this;  \
        }                                         \
    }

// namespace VoxelFrame
// {
//     // class EventPublisher;
//     class EventPublisher
//     {
//     };

// }
