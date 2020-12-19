using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ray : MonoBehaviour
{
    private GameObject po, ball, co, bbt;
    public Shader alphaShader;
    public GameObject Selector,previewOfBlockInHand;
    selectorController selCtrl;
    GUIMainController gmctrl;
    public GameObject DugBlockModel;
    private TerrainManager terraManager;
    private int x, y, z;
    private Vector3 wantedPosition;
    public static trigger trig;

    public bool buildAble,triggerStaying;
    public static ray _ray;
    void Start()
    {
        _ray=this;
        terraManager = GameObject.Find("Map").GetComponent<TerrainManager>();

        po = GameObject.Find("po2");
        ball = GameObject.Find("ball");
        co = GameObject.Find("CubeCo");
        bbt = GameObject.Find("BuildBlockTrigger");
        bbt.GetComponent<trigger>().ray = this;
        selCtrl=Selector.GetComponent<selectorController>();
        gmctrl=GUIMainController.gmctrl;
    }
    private int GetBlockPlace(float pos, float hitP, int xyz)
    {
        if (Mathf.Abs(Mathf.RoundToInt(hitP) - hitP) < 0.00002)
        {

            if (pos - hitP < 0)
            {
                if (xyz == 1)
                {
                    y = z = 0;
                    x = -1;
                }
                else if (xyz == 2)
                {
                    x = z = 0;
                    y = -1;
                }
                else
                {
                    x = y = 0;
                    z = -1;
                }
                return Mathf.RoundToInt(hitP);
            }
            else
            {
                if (xyz == 1)
                {
                    y = z = 0;
                    x = 1;
                }
                else if (xyz == 2)
                {
                    x = z = 0;
                    y = 1;
                }
                else
                {
                    y = x = 0;
                    z = 1;
                }
                return Mathf.RoundToInt(hitP) - 1;
            }
        }
        else
        {
            return (int)Mathf.Floor(hitP);
        }
    }
    bool poStep;
    Vector3 preLocalPosTarg;
    public void loadShapeIcon1(Shapes shape1){

    }
    void smoothSelect(int bx, int by, int bz)
    {
        wantedPosition.x = bx;

        wantedPosition.z = bz;//Vector3.forward*distance;   

        wantedPosition.y = by;// + heightAbovePlayer;wantedPosition;//
        Material poMat=po.transform.GetChild(0).GetComponent<Renderer>().material;
        Material preMat;
        if(Vector3.Distance(wantedPosition,po.transform.position)<0.00001){
            float poAlpha=MyTools.FloatInUpdateWithFixedTimeAndSetToFinalWithSpeed(poMat.GetFloat("_AlphaScale"),0.38f,5);
            poMat.SetFloat("_AlphaScale",poAlpha);
            
        }else{
            float poAlpha=MyTools.FloatInUpdateWithFixedTimeAndSetToFinalWithSpeed(poMat.GetFloat("_AlphaScale"),0f,50);
            poMat.SetFloat("_AlphaScale",poAlpha);
            
            if(poMat.GetFloat("_AlphaScale")==0){
                po.transform.position=wantedPosition;
            }
        }
        if (previewOfBlockInHand != null)
        {
            
            //ItemAttacher.itemAttacher.itemDic[selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID].getBlockDecription().GetBlockDrawer(selCtrl.indexOfDirection).getBlockObjectRotate(previewOfBlockInHand);
            preMat = previewOfBlockInHand.GetComponent<Renderer>().material;
            if (buildAble)
            {
                if (Vector3.Distance(previewOfBlockInHand.transform.position, wantedPosition + new Vector3(x + 0.5f, y + 0.5f, z + 0.5f)) < 0.00001)
                {
                    //Debug.Log(previewOfBlockInHand.transform.position+" ||||| "+(wantedPosition + new Vector3(x + 0.01f, y + 0.01f, z + 0.01f)));
                    float preAlpha = MyTools.FloatInUpdateWithFixedTimeAndSetToFinalWithSpeed(preMat.GetFloat("_AlphaScale"), 0.38f, 5);
                    preMat.SetFloat("_AlphaScale", preAlpha);
                }
                else
                {
                    //Debug.Log(previewOfBlockInHand.transform.position+" || "+(wantedPosition+ new Vector3(x + 0.01f, y + 0.01f, z + 0.01f)));
                    float preAlpha = MyTools.FloatInUpdateWithFixedTimeAndSetToFinalWithSpeed(preMat.GetFloat("_AlphaScale"), 0f, 50);
                    preMat.SetFloat("_AlphaScale", preAlpha);
                    if (preMat.GetFloat("_AlphaScale") == 0)
                    {
                        previewOfBlockInHand.transform.position = po.transform.position+new Vector3(x + 0.5f, y + 0.5f, z + 0.5f);
                    }
                }
                //preMat.SetFloat("_AlphaScale",poAlpha);
            }
            else
            {
                preMat.SetFloat("_AlphaScale", MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(preMat.GetFloat("_AlphaScale"), 0));
            }// = previewOfBlockInHand.GetComponent<Renderer>().material;//if(previewOfBlockInHand.active==true) previewOfBlockInHand.SetActive(false);
        }
        //po.transform.position=MyTools.MoveInUpdateWithFixedTime(po.transform.position,wantedPosition);//Vector3.Lerp(,0.3f);
            //po.transform.position = new Vector3(currentX, currentY, currentZ);
    }
    private IEnumerator CreateDugCube(int bx,int by,int bz,uniKey blockID1,byte rotation1)
    {
        yield return new WaitForSeconds(0.2f);
        dugBlockManager.dm.CreateDugCube(bx,by,bz,blockID1,rotation1);
    }
    public void Build(Vector3 to){
        terraManager.BuildBlock(Mathf.FloorToInt(to.x), Mathf.FloorToInt(to.y), Mathf.FloorToInt(to.z), MyTools.Unikey(1,0), 0);
    }
    void Update()
    {
        if (Input.GetMouseButton(1))
        {
            timeCountUp += Time.deltaTime;

            if (timeCountUp > 1.5f)
            {
               // Debug.Log("opened");
                if(gmctrl.CurrentGui==GUIMainController.Guis.noGui){
                    if(selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item == null){
                        gmctrl.StartMiniTip("手中需要持有物品");
                    }else{
                        gmctrl.CurrentGui = GUIMainController.Guis.RightLongPressGUI;
                        gmctrl.OpenGUI(gmctrl.CurrentGui);
                    }
                    
                }
            }
            else
            {
               // Debug.Log(timeCountUp);
                
            }
        }
        
        RaycastHit hit;
        RaycastHit hitf;
        Vector3 fwd = transform.TransformDirection(Vector3.forward);//获取摄像头向前的方向
        if (Physics.Raycast(transform.position, fwd, out hitf, Mathf.Infinity, 1 << 9))
        {
            //Debug.Log(111);
            GetBlockPlace(transform.position.x, hitf.point.x, 1);
            GetBlockPlace(transform.position.y, hitf.point.y, 2);
            GetBlockPlace(transform.position.z, hitf.point.z, 3);
        }
        //
        if (Physics.Raycast(transform.position, fwd, out hit, Mathf.Infinity, 1 << 8))
        {   
            if (!po.activeSelf)
            {
                po.SetActive(true);
            }
            //poMat.SetFloat("_AlphaScale",MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(poMat.GetFloat("_AlphaScale"),0.618f));
            
            Debug.DrawLine(transform.position, hit.point, Color.red);//scene视图中绘制射线
            int bx, by, bz;
            bx = GetBlockPlace(transform.position.x, hit.point.x, 1);
            by = GetBlockPlace(transform.position.y, hit.point.y, 2);
            bz = GetBlockPlace(transform.position.z, hit.point.z, 3);
            bbt.transform.localPosition = new Vector3(x, y, z);
            co.transform.position = new Vector3(bx + 0.5F, by + 0.5f, bz + 0.5f);
            //po.transform.position = new Vector3(bx + 0.5F, by + 0.5f, bz + 0.5f);

            
            //ball.transform.position = hit.point;
            uniKey itemIDSelected;
            //Debug.Log((ushort)selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponentInChildren<uiItem>().Item.ID);
            Material mat;
            
            if (buildAble)
            {
                if (selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item != null)
                {
                    //获取itemID
                    itemIDSelected = selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID;
                    if (previewOfBlockInHand == null || previewOfBlockInHand.name != "方块预览"+itemIDSelected.id1+":"+itemIDSelected.id2)
                    {
                        Destroy(previewOfBlockInHand);
                        previewOfBlockInHand = Instantiate<GameObject>(ItemAttacher.itemAttacher.itemDic[itemIDSelected].getBlockDecription().GetIconObject());
                        //ItemAttacher.itemAttacher.itemDic[itemIDSelected].getBlockDecription().GetBlockDrawer(selCtrl.indexOfDirection).getBlockObjectRotate(previewOfBlockInHand);
                        Destroy(previewOfBlockInHand.transform.GetChild(0).gameObject);
                        previewOfBlockInHand.GetComponent<Renderer>().material.shader = alphaShader;
                        //previewOfBlockInHand.transform.SetParent(po.transform);
                        previewOfBlockInHand.transform.localScale=new Vector3(0.98f,0.98f,0.98f);

                        
                        //previewOfBlockInHand.transform.localPosition =new Vector3(x+0.01f, y+0.01f, z+0.01f);//Vector3.Lerp(previewOfBlockInHand.transform.localPosition, new Vector3(x+0.01f, y+0.01f, z+0.01f), 0.3f);
                        previewOfBlockInHand.name = "方块预览"+itemIDSelected.id1+":"+itemIDSelected.id2;
                        selCtrl.rotateObjectIfExist();
                        Debug.Log("LoadingDone");
                    }
                }else Destroy(previewOfBlockInHand);
            }
            smoothSelect( bx,  by,  bz);
            /*else {
                
                if(previewOfBlockInHand!=null){
                    previewOfBlockInHand.transform.localPosition = MyTools.MoveInUpdateWithFixedTime(previewOfBlockInHand.transform.localPosition, new Vector3(x+0.01f, y+0.01f, z+0.01f));
                    mat = previewOfBlockInHand.GetComponent<Renderer>().material;
                    mat.SetFloat("_AlphaScale",MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(mat.GetFloat("_AlphaScale"),0));//if(previewOfBlockInHand.active==true) previewOfBlockInHand.SetActive(false);
                }
            }*/

            if (gmctrl.CurrentGui == GUIMainController.Guis.noGui)
            {
                if (Input.GetMouseButtonDown(0))
                {
                    Debug.Log(new Vector3(bx + 0.5F, by + 1f, bz + 0.5f));
                    byte direction = terraManager.GetBlockRotation(bx,by,bz);
                    uniKey blockID = terraManager.BuildBlock(bx, by, bz, BlockAttacher.GetEmptyBlock(), 80);//记下方块类型，以便，产生掉落块

                    StartCoroutine(CreateDugCube(bx, by, bz, blockID,direction));
                }

                else if (Input.GetMouseButtonUp(1))
                {

                    if (timeCountUp < 1 && timeCountUp > 0.00001)
                    {
                        if (buildAble)
                        {
                            if (selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item == null)
                            {
                                Debug.Log("empty item");
                            }
                            else
                            {
                                itemIDSelected = selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponent<mouseOnGrid>().item.GetComponent<uiItem>().itemID;
                                
                                terraManager.BuildBlock(bx + x, by + y, bz + z, itemIDSelected, selCtrl.indexOfDirection);
                                selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponentInChildren<uiItem>().MinusCountAndReturnSurplus(1);
                                //terraManager.BuildBlock()
                                /*if (BlockIDSelected == 1)
                                {
                                    terraManager.BuildBlock(bx + x, by + y, bz + z, 1, 80);
                                    selCtrl.dockController.gridInDock[selCtrl.indexOfChosen].GetComponentInChildren<uiItem>().MinusCountAndReturnSurplus(1);
                                }
                                else if (selCtrl.indexOfChosen == 1)
                                {
                                    //terraManager.BuildBlock(bx + x, by + y, bz + z, 2, (sb.indexOfDirection));
                                }*/
                            }
                        }
                    }


                }
                else if (Input.GetMouseButtonDown(2))
                {
                    //terraManager.SetTerrain(10, 10, 10, 5);
                }
                else
                {
                    //没有碰撞时

                }
            }
        }
        else{
            Material poMat = po.transform.GetChild(0).GetComponent<Renderer>().material;
            poMat.SetFloat("_AlphaScale", MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(poMat.GetFloat("_AlphaScale"), 0f));
            if (previewOfBlockInHand != null)
            {
                Material mat;
                //previewOfBlockInHand.transform.
                previewOfBlockInHand.transform.position =new Vector3(x + 0.5f, y + 0.5f, z + 0.5f);
                //previewOfBlockInHand.transform.localPosition = MyTools.MoveInUpdateWithFixedTime(previewOfBlockInHand.transform.localPosition, new Vector3(x + 0.01f, y + 0.01f, z + 0.01f));
                mat = previewOfBlockInHand.GetComponent<Renderer>().material;
                mat.SetFloat("_AlphaScale", MyTools.FloatInUpdateWithFixedTimeAndSetToFinal(mat.GetFloat("_AlphaScale"), 0));//if(previewOfBlockInHand.active==true) previewOfBlockInHand.SetActive(false);
            }
            /*if (po.active)
            {
                po.SetActive(false);
            }*/
        }

        if (Input.GetMouseButtonUp(1))
        {
            timeCountUp = 0;
        }
    }
    float timeCountUp;
}
