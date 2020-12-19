using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInfo{
	float blood,exp;
	float fullBlood=10;
	public string name;

	public PlayerInfo(string name1){
		name=name1;
		exp=0;
		blood=fullBlood;
	}
}