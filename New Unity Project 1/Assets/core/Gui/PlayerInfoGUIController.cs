using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerInfoGUIController : MonoBehaviour {
	public GameObject nameGUI,bloodGUI;
	
	PlayerInfo playerInfo;
	// Use this for initialization
	void Start () {
		playerInfo=new PlayerInfo("pa");
		nameGUI.GetComponent<Text>().text=playerInfo.name;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
