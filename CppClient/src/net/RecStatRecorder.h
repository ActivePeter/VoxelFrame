#pragma once

#include "stdint.h"

class RecStatRecorder
{
public:
    enum RecStats
    {
        RecStats_ReceivedHead,
        RecStats_NoHead
    };
    void bodyNotCompleteRec(uint32_t, uint16_t);
    void bodyCompleteRec();
    static RecStatRecorder *getInstance();
    RecStats getCurState();
    uint16_t getMsgId();
    uint32_t getBodyLen();

private:
    RecStats curState = RecStats_NoHead;
    /* data */
    uint32_t bodyLen;
    uint16_t msgId;
    RecStatRecorder(/* args */);
    ~RecStatRecorder();

    // public:
};
