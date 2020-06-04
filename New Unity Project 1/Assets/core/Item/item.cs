using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class item {

    BlockDescription Block;

    GameObject itemIconObject;
	RenderTexture itemIcon;

    public item(BlockDescription Block1){
        Block=Block1;
        Block.SetItem(this);        
    }
    public BlockDescription getBlockDecription(){
        return Block;
    }
    
}
