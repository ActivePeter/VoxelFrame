#pragma once

#define ChunkSize 64
#include "graph/Mesh.h"
#include "graph/interface/MeshBuilder.h"

struct ChunkKeyStruct
{
    int x;
    int y;
    int z;
    /* data */
    ChunkKeyStruct();
    ChunkKeyStruct(int x, int y, int z);
};

class Chunk : MeshBuilder
{
private:
    int blockData[ChunkSize * ChunkSize * ChunkSize]; //protobuf需要直接解析到的目标位置
    ChunkKeyStruct chunkId;                           //构造函数中进行初始化
    Mesh mesh;
    /* data */
public:
    void buildMesh();
    void fillTest();
    Chunk(int x, int y, int z);
    ~Chunk();
};
