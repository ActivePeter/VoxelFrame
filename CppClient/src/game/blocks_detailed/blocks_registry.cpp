#pragma once
// #include "game/blocks_base_type/up_side_bottom__block.h"
#include "game/block.h"
#include "app.h"
#include "game/blocks_uv_setter/up_side_bottom__block.h"

void registerBlockAll(BlockManager &bm)
{
    //air
    bm.addEmptyBlock(
        CommonBlockInfo());
    //grass
    bm.addBlock(
        CommonBlockInfo(
            std::static_pointer_cast<Base_BlockUVSetter>(
                std::make_shared<UP_Side_Bottom__BlockUVsetter>(
                    "grass_top",
                    "grass_side",
                    "grass_bottom"))));
    App::getInstance().graphPtr->_textureManagerPtr->registBlockFacesEnd();
}