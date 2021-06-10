#pragma once
#include "base.h"
#include "chunk.h"
#include "block.h"
#include "main_player.h"
struct ChunkKey;
class Chunk;
class ChunkManager;
class BlockManager;
//////////////////////////////

class Game
{
    // private:

    /* data */
public:
    // datas
    std::shared_ptr<ChunkManager> chunkManager;
    std::shared_ptr<BlockManager> blockManager;
    std::shared_ptr<MainPlayer> mainPlayer;
    // funcs

    void start();
};
