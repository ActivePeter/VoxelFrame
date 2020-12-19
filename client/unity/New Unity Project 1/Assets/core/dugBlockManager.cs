using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dugBlockManager : MonoBehaviour {
    public static dugBlockManager dm;
    List<dugBlockSelfManager> dugBlocksWaitToRecover;
    bool recoverReached;
    public bool recovering;
	// Use this for initialization
    void Awake(){
        dm=this;
    }
	void Start () {
        
        dugBlocksWaitToRecover = new List<dugBlockSelfManager>();
        recovering = false;
        recoverReached = false;
	}
	
	// Update is called once per frame
	void Update () {
        if (!recovering)
        {
            if (dugBlocksWaitToRecover.Count != 0)
            {
                recovering = true;
                dugBlocksWaitToRecover[dugBlocksWaitToRecover.Count - 1].startRecover();
                dugBlocksWaitToRecover.RemoveAt(dugBlocksWaitToRecover.Count - 1);
            }
        }
		
	}
    public void AddRecover(dugBlockSelfManager r)
    {
        dugBlocksWaitToRecover.Add(r);
    }
    
    public void CreateDugCube(int bx,int by,int bz,uniKey blockID1,byte direction1){
        GameObject block1=BlockObjectCreator.CreateBlockObjectWithColiAndCenter(BlockAttacher.blockAttacher.GetBlock(blockID1));
        BlockAttacher.blockAttacher.blockDescriptionDic[blockID1].GetBlockDrawer(direction1).getBlockObjectRotate(block1);
        //GameObject block1c=block1.transform.GetChild(0).gameObject;
       // GameObject block1 = (GameObject)Instantiate(DugBlockModel);
        //block1.GetComponent<dugBlockSelfManager>().setTexture(blockID1);
        block1.transform.position = new Vector3(bx + 0.5F, by + 0.5f, bz + 0.5f);
        block1.transform.localScale = new Vector3(0.8F, 0.8f, 0.8f);
        block1.transform.SetParent(this.gameObject.transform);
        block1.AddComponent<Rigidbody>();
        block1.layer=11;
        block1.tag="DugBlock";
        block1.AddComponent<dugBlockSelfManager>();
        block1.GetComponent<dugBlockSelfManager>().Init(blockID1);
    }
}
