#include "RecStatRecorder.h"

RecStatRecorder::RecStatRecorder(/* args */)
{
}

RecStatRecorder::~RecStatRecorder()
{
}

void RecStatRecorder::bodyNotCompleteRec(uint32_t bodyLen1, uint16_t msgId1)
{
    this->bodyLen = bodyLen1;
    this->msgId = msgId1;
    this->curState = RecStats_ReceivedHead;
}

void RecStatRecorder::bodyCompleteRec()
{
    this->curState = RecStats_NoHead;
}
RecStatRecorder *RecStatRecorder::getInstance()
{
    static RecStatRecorder rsr;
    return &rsr;
}
RecStatRecorder::RecStats RecStatRecorder::getCurState()
{
    return this->curState;
}
uint16_t RecStatRecorder::getMsgId()
{
    return this->msgId;
}

uint32_t RecStatRecorder::getBodyLen()
{
    return this->bodyLen;
}