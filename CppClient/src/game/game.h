class Game;
class TCaller;
class TCallbackRegister;
#ifndef __GAME_H__
#define __GAME_H__

#include "base.h"
#include "chunk.h"
#include "chunk_manager.h"
#include "block.h"
#include "main_player.h"
#include "interface/IRegister.h"

using TCallbackFunc = void (*)(Game &game);
//////////////////////////////
class TCaller : IRegister
{
public:
    int T;
    std::vector<TCallbackFunc> callbacks;
    TCaller(int T) : T(T) {}
    void callAll(Game &game)
    {
        for (int i = 0; i < callbacks.size(); i++)
        {
            callbacks[i](game);
        }
    }
};
class Game : IRegister
{
    // private:
    std::vector<TCaller> TCallers;
    /* data */
public:
    void IRegister_regist() override;

    // datas
    std::shared_ptr<ChunkManager> chunkManager;
    std::shared_ptr<BlockManager> blockManager;
    std::shared_ptr<MainPlayer> mainPlayer;
    bool playing = false;

    uint64_t gameTick;
    // funcs

    void start();
    void loop();
    void registTCallback(int T, TCallbackFunc f);

    bool getControlling()
    {
        return controlling;
    }
    void setControlling(bool a)
    {
        controlling = a;
    }

private:
    bool controlling = false;
};

#endif // __GAME_H__