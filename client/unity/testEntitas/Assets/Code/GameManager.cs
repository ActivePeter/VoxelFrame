using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    private GameSystems gameSystems;
    // Use this for initialization

    void Awake()
    {
        gameSystems = new GameSystems(Contexts.sharedInstance);
    }

    void Start()
    {
        var playerEntity = Contexts.sharedInstance.game.CreateEntity();
        gameSystems.Initialize();
    }

    // Update is called once per frame
    void Update()
    {
        gameSystems.Execute();
        gameSystems.Cleanup();
    }

    void OnDestroy()
    {
        gameSystems.TearDown();
    }
}
