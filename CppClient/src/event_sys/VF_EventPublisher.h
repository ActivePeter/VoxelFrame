#pragma once
#include "vf_base.h"
#include "VF_EventListener.h"

// #define PublisherClassHead2(x)
#define PublisherClass(x) x##EventPublisher //class PublisherClassHead2(x)
#define PublisherClassBody(x)                                       \
public:                                                             \
    std::vector<ListenerClass(x) *> listeners;                      \
    template <class T>                                              \
    void addListener(T *listener)                                   \
    {                                                               \
        ListenerClass(x) *Ilistener = (ListenerClass(x) *)listener; \
        if (!Ilistener->listeningPublisher)                         \
        {                                                           \
            listeners.push_back(Ilistener);                         \
            Ilistener->listeningPublisher = this;                   \
        }                                                           \
    }

// namespace VoxelFrame                                             \
// {                                                                \
//     // class EventPublisher;                                     \
//     class EventPublisher                                         \
//     {                                                            \
//     };

// }
