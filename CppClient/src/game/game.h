#include "base.h"
#include "chunk.h"
#include "block.h"
#include "main_player.h"
class Game;

#ifndef __GAME_H__
#define __GAME_H__

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

#endif // __GAME_H__