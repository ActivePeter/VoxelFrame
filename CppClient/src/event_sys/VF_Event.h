#pragma once

#define VF_EventNamespaceBegin \
namespace VoxelFrame{ \
namespace _Event{             \

#define VF_EventNamespaceEnd \
}}                           \

#include "VF_EventListener.h"
#include "VF_EventPublisher.h"