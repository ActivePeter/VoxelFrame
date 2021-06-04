#pragma once
#include "base.h"
#include "chunk.h"
#include "block.h"

struct ChunkKey;
class Chunk;
class ChunkManager;
//////////////////////////////

class Game
{
    // private:

    /* data */
public:
    // datas
    std::shared_ptr<ChunkManager> chunkManager;
    std::shared_ptr<BlockManager> blockManager;
    // funcs

    void start();
};
