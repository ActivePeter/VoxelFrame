#pragma once
//#include "event_sys/VF_EventListener.h"
//#include "event_sys/VF_EventPublisher.h"
#include "event_sys/VF_Event.h"
// #include ""
//namespace VoxelFrame
//{
VF_EventNamespaceBegin
        class GuiNothingClick_EventPublisher;

        class GuiNothingClick_EventListener;

        class GuiNothingClick_EventListener {
        ListenerClassBody(GuiNothingClick);

        public:
            virtual void GuiNothingClick_ListenerCallback() = 0;
        };

        class GuiNothingClick_EventPublisher {
        PublisherClassBody(GuiNothingClick);

            void pub2All() {
                for (auto &i : listeners) {
                    i->GuiNothingClick_ListenerCallback();
                }
            }
        };

VF_EventNamespaceEnd