
#include <iostream>
#include <memory>
#include <thread>
#include "brynet/base/AppStatus.hpp"
#include "brynet/base/Packet.hpp"
#include "brynet/net/EventLoop.hpp"
#include "brynet/net/SocketLibFunction.hpp"
#include "brynet/net/TcpConnection.hpp"

#include "_net.h"
#include "RecStatRecorder.h"

using namespace std;
using namespace brynet;
using namespace brynet::net;
using namespace brynet::base;
_net _g_net;

void netSysThread();

void _net::start()
{
    auto th = new thread(netSysThread); // new thread(netSysThread);
}
void netSysThread()
{
    cout << "NetSys thread started" << endl;
    //启动socket
    brynet::net::base::InitSocket();
    //创建线程的智能指针
    auto clientEventLoop = std::make_shared<EventLoop>();
    std::string ip = "127.0.0.1";
    int port = 6666;
    // int packetLen = 100;
    //链接到对应ip和port
    auto fd = brynet::net::base::Connect(false, ip, port);
    //socket设置发送尺寸和接收尺寸
    brynet::net::base::SocketSetSendSize(fd, 32 * 1024);
    brynet::net::base::SocketSetRecvSize(fd, 32 * 1024);
    //设置无延迟操作（不太理解）
    brynet::net::base::SocketNodelay(fd);

    //进入后的回调
    auto enterCallback = [](const TcpConnection::Ptr &dataSocket)
    {
        cout << "NetSys socket enterd" << endl;

        // static_assert(sizeof(dataSocket.get()) <= sizeof(int64_t), "ud's size must less int64");

        // auto HEAD_LEN = sizeof(uint32_t) + sizeof(uint16_t);

        // std::shared_ptr<BigPacket> sp = std::make_shared<BigPacket>(false);
        // sp->writeUINT32(HEAD_LEN + sizeof(int64_t) + packetLen);
        // sp->writeUINT16(1);
        // sp->writeINT64((int64_t)dataSocket.get());
        // sp->writeBinary(std::string(packetLen, '_'));

        // for (int i = 0; i < 1; ++i)
        // {
        //     dataSocket->send(sp->getData(), sp->getPos());
        // }

        //接收到数据后的回调
        dataSocket->setDataCallback([dataSocket](brynet::base::BasePacketReader &reader)
                                    {
                                        // cout << "NetSys data in" << endl;
                                        auto recStateRecorder = RecStatRecorder::getInstance();
                                        uint32_t bodyLen; //= recStateRecorder->getBodyLen();
                                        uint16_t msgId;   // = recStateRecorder->getMsgId();
                                        //检查之前是否有未接收完成的情况，如果有就继续之前的接收
                                        if (recStateRecorder->getCurState() == RecStatRecorder::RecStats_ReceivedHead)
                                        {
                                            bodyLen = recStateRecorder->getBodyLen();
                                            msgId = recStateRecorder->getMsgId();
                                            goto checkBodyComplete;
                                        }
                                        while (true)
                                        {
                                            //没有到一个包头的尺寸  包体长度四字节+数据类型二字节
                                            if (!reader.enough(6))
                                            {
                                                break;
                                            }
                                            auto buffer = reader.currentBuffer();
                                            bodyLen = reader.readUINT32(); //读取后位置也加1
                                            msgId = reader.readUINT16();

                                        checkBodyComplete:
                                            //没有到整个包体的尺寸
                                            if (!reader.enough(bodyLen))
                                            {
                                                recStateRecorder->bodyNotCompleteRec(bodyLen, msgId);
                                                break;
                                            }
                                            cout << "one pack" << endl;
                                            // TotalRecvSize += packetLen;
                                            // TotalRecvPacketNum++;

                                            // reader.readUINT16();
                                            // int64_t addr = reader.readINT64();

                                            // if (addr == (int64_t)(dataSocket.get()))
                                            // {
                                            //     dataSocket->send(buffer, packetLen);
                                            // }

                                            //添加读取整个包的变化，
                                            reader.addPos(bodyLen);

                                            reader.savePos();
                                            recStateRecorder->bodyCompleteRec();
                                        }
                                    });
        //断开链接的回调
        dataSocket->setDisConnectCallback([](const TcpConnection::Ptr &dataSocket)
                                          {
                                              (void)dataSocket;
                                              cout << "NetSys disconnected" << endl;
                                          });
    };
    auto tcpConnection = TcpConnection::Create(TcpSocket::Create(fd, false),
                                               1024 * 1024,
                                               enterCallback,
                                               clientEventLoop);
    while (true)
    {
        clientEventLoop->loop(10);

        if (app_kbhit())
        {
            cout << "NetSys stoped" << endl;
            break;
        }
    }
}