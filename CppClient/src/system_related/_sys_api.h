#pragma once
#include "SDL.h"
#include "vf_base.h"
// #define _sys_api_getTick SDL_GetTicks

//获取程序运行时间
inline uint64_t _sys_api_getTick()
{
    return (uint64_t)SDL_GetTicks();
}