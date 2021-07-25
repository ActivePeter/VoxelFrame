namespace VoxelFrame {
    namespace _Game {
        class Game;

        class TCaller;

        class TCallbackRegister;
    }
}
#ifndef __GAME_H__
#define __GAME_H__

#include "base/vf_base.h"
#include "chunk/chunk.h"
#include "chunk/chunk_manager.h"

#include "block/block.h"
#include "main_player.h"
#include "interface/IRegister.h"

#include "interfaces/IUpdaterBeforePhysic.h"
#include "interfaces/IUpdaterAfterPhysic.h"

#include "graph/gui/GuiNothingClickEvent.h"

// #include "paecs/paecs.h"
namespace VoxelFrame {
    namespace _Game {
        using TCallbackFunc = void (*)(Game &game);

        //////////////////////////////
        class TCaller : IRegister {
        public:
            int T;
            std::vector<TCallbackFunc> callbacks;

            TCaller(int T) : T(T) {}

            void callAll(Game &game) {
                for (int i = 0; i < callbacks.size(); i++) {
                    callbacks[i](game);

                    //this->callAll()��

                }
            }
        };

        class Game
                : IRegister,
                  public VF::_Event::GuiNothingClick_EventListener {
            ////////////////////////////////////////////
            //     GuiNothingClickEventListener
        public:
            void GuiNothingClick_ListenerCallback() override;

            // private:
            std::vector<TCaller> TCallers;
            /* data */
        public:
            void IRegister_regist() override;

            // datas
            std::shared_ptr<_Chunk::Manager> chunkManager;
            std::shared_ptr<_Block::Manager> blockManager;
            std::shared_ptr<MainPlayer> mainPlayer;

            paecs::SysGroup beforePhysicSysGroup;
            paecs::SysGroup afterPhysicSysGroup;

            /**
     * all the interfaces after physic will add themselves to this vector
    */
            std::deque<IUpdaterAfterPhysic *> iUpdaterAfterPhysics;
            std::deque<IUpdaterBeforePhysic *> iUpdaterBeforePhysics;

            bool playing = false;

            uint64_t gameTick;
            // funcs

            void start();

            void loop();

            void registTCallback(int T, TCallbackFunc f);

            //bool getControlling() {
            //    return controlling;
            //}

            //void setControlling(bool a) {
            //    controlling = a;

            //    //                this.
            //}

        private:
            //bool controlling = false;
        };
    }
}
#endif // __GAME_H__