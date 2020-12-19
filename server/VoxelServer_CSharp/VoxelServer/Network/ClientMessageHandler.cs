using ProtoBuf;
using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.Linq;
using System.Text;

namespace VoxelServer.Network
{
    class ClientMessageHandler
    {
        const int BUFFER_SIZE = 1024;
        const int HEAD_SIZE = 6;
        public byte[] buffer = new byte[BUFFER_SIZE];
        
        public int beginIndex = 0;
        int bodyLen = -1;//记录读出的bodylen。-1即为未读.每次处理完数据体后都要置-1                    
                         //bodyLen为数据体总长度
        Int16 packId = -1;
        public int leftSize
        {
            get
            {
                return BUFFER_SIZE-beginIndex;
            }
        }
        List<byte> incompleteBody=new List<byte>();
        //public byte[] incompleteBody;//用来存储之前接收但没接受全的数据体

        public void handleReceive(int dataLen)
        {
            int handledLen=0;//记录已经处理的数据长度。等价于下一步数据从哪开始.处理完数据就要+1
            while (handledLen!=dataLen)
            {
                if (incompleteBody.Count==0)//判断是否存在未接收完的数据体，不存在即先读取数据头（数据体长度int32）
                {
                    if (dataLen-handledLen < HEAD_SIZE)//判断长度是否达到int32，不到直接return，继续下一次接收。
                    {
                        beginIndex += dataLen - handledLen;
                        if (handledLen>0)
                        {
                            Array.Copy(buffer,0,buffer, handledLen, dataLen - handledLen);
                        }
                        return;
                    }
                    else
                    {
                        bodyLen = BitConverter.ToInt32(buffer, handledLen);
                        packId = BitConverter.ToInt16(buffer, handledLen+4);
                        handledLen += HEAD_SIZE;
                        if (bodyLen > dataLen - handledLen)//数据体长度大于未处理数据长度，把数据体存入incompleteBody
                        {
                            incompleteBody.AddRange(buffer.Skip(handledLen).Take(dataLen - handledLen));//存入incompleteBody

                            return;
                        }
                        else
                        {
                            //处理数据体
                            //Serializer.Deserialize
                            //处理完后
                            handledLen += bodyLen;
                            resetBodyLenAndPackId();
                        }
                    }
                }
                else
                {

                    int leftBodyLen = bodyLen - incompleteBody.Count;
                    if (leftBodyLen > dataLen)
                    {
                        incompleteBody.AddRange(buffer.Take(dataLen));//存入incompleteBody

                        return;
                    }
                    else
                    {
                        incompleteBody.AddRange(buffer.Take(leftBodyLen));//组合数据体

                        //处理数据体

                        //处理完后
                        handledLen += leftBodyLen;
                        resetBodyLenAndPackId();
                        incompleteBody.Clear();
                    }
                }
            }
        }
        private void resetBodyLenAndPackId()
        {
            bodyLen = -1;
            packId = -1;
        }
    }
}
