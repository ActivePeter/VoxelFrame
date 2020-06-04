/* using UnityEngine;
using UnityEditor;
using System;
using System.Collections;
using UnityEditor.SceneManagement;

public class AutoSave : EditorWindow
{

   private bool autoSaveScene = true;
    private bool showMessage = true;
    private bool isStarted = false;
    private int intervalScene;
    private DateTime lastSaveTimeScene = DateTime.Now;

    private string projectPath = Application.dataPath;
    private string scenePath;
    bool saveable;
    

    

    
    void Update()
    {
        scenePath = EditorApplication.currentScene;
        if (autoSaveScene)
        {
            
            if (DateTime.Now.Ticks-lastSaveTimeScene.Ticks>150000000&&!EditorApplication.isPlaying)
            {
                saveScene();
            }
        }
        else
        {
            isStarted = false;
        }

    }

    void saveScene()
    {
        EditorApplication.SaveScene(scenePath);
        lastSaveTimeScene = DateTime.Now;
        isStarted = true;
            Debug.Log("AutoSave saved: " + scenePath + " on " + lastSaveTimeScene);
        
    }
}*/