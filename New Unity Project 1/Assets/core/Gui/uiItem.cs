using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class uiItem : MonoBehaviour,ICanvasRaycastFilter
{
    public GameObject countTextModel;
    GameObject CountText;
    private static Transform canvasTra;
    private Transform nowParent;//一般来说，物品是格子的子物体，nowParent记录的是当前物品属于哪个格子  
    bool picked;
    private bool isRaycastLocationValid = true;//默认射线不能穿透物品  

    public Sprite icon;
    public uniKey itemID;
    public int itemsCount;
    int maxCount;
    private void Start()
    {
    }
    public bool ifIsFullSet(){
        return !(itemsCount<maxCount);
    }
    public void FirstSetInfo(uniKey itemID1,int count1)//根据itemID加载材质
    {
        itemsCount=count1;
        itemID=itemID1;
        
        CountText=(GameObject)Instantiate(countTextModel);
        CountText.transform.SetParent(gameObject.transform);
        CountText.transform.localPosition = Vector3.zero;
        CountText.GetComponent<Text>().text=itemsCount.ToString();
        
        this.GetComponent<RawImage>().texture=ItemAttacher.itemAttacher.itemDic[itemID1].getBlockDecription().GetIcon();
        maxCount=64;
        //CountText.transform.position=gameObject.transform.position;
        // throw new NotImplementedException();
    }
    public int AddCountAndReturnSurplus(int count){
        if(count+itemsCount>maxCount){
            Debug.Log("itemcount1："+itemsCount);
            int fastsave=itemsCount;
            itemsCount=maxCount;
            CountText.GetComponent<Text>().text=itemsCount.ToString();
            return count+fastsave-maxCount;
        }else{
            itemsCount+=count;
            CountText.GetComponent<Text>().text=itemsCount.ToString();
            return 0;
        }
        
    }
    public void AddCount(int count){
        itemsCount+=count;
        CountText.GetComponent<Text>().text=itemsCount.ToString();
    }
    public int MinusCountAndReturnSurplus(int count){
        if(itemsCount-count<0){
            itemsCount=0;
            CountText.GetComponent<Text>().text=itemsCount.ToString();
            return count-itemsCount;
        }else{
            
            itemsCount-=count;
            if(itemsCount==0) Destroy(gameObject);
            CountText.GetComponent<Text>().text=itemsCount.ToString();
            return 0;
        }
    }
            /*if (go.tag.Equals("Grid"))//放置到空格子  
            {
                SetParentAndPosition(transform, go.transform);
            }
            else if (go.tag.Equals("Item"))//交换位置，注意可能需要把物品下的子物体的Raycast Target关掉  
            {
                SetParentAndPosition(transform, go.transform.parent);
                SetParentAndPosition(go.transform, nowParent);
            }*/
        
    public bool IsRaycastLocationValid(Vector2 sp, Camera eventCamera)
    {
        return false;
    }
    
}
