using UnityEngine;
using System.Collections;

public class playerControl: MonoBehaviour
{
    public float sensitivityY = 2.0f;
    public float sensitivityX = 2.0f;
    //上下最大视角（Y视角）
    float minmumY = -15f;
    float maxmunY = 15f;
    float rotationY = 0f;
    float rotationX = 0f;
    
    public GameObject mc;
    private TerrainManager terraManager;
    private CharacterController cc;
    private Vector3 moveDirection = Vector3.zero;
    //人物当前行走的方向状态
    public int state = 0;
    //人物移动速度
    public float moveSpeed;
    private float g;
    private int countForGroundCheck;
    float jumpSpeed;

    //初始化人物位置
    
    // Use this for initialization
    void Start()
    {
        moveSpeed=6;
        cc = GetComponent<CharacterController>();
        rr = GetComponent<Rigidbody>();
        terraManager = GameObject.Find("Map").GetComponent<TerrainManager>();
        mc = GameObject.Find("mc");
        g = 0.7f;
        jumpSpeed = 0.3f;
        minmumY = -90f;
        maxmunY = 90f;
    }
    // Update is called once per frame
    CursorLockMode wantedMode;

    public Rigidbody rr;


    // Apply requested cursor state
    void SetCursorState()
    {
        Cursor.lockState = wantedMode;
        // Hide cursor when locking
        Cursor.visible = (CursorLockMode.Locked != wantedMode);
    }
    
    void OnGUI()
    {
        GUILayout.BeginVertical();
        // Release cursor on escape keypress
        if (Input.GetKeyDown(KeyCode.Escape))
            Cursor.lockState = wantedMode = CursorLockMode.None;

        switch (Cursor.lockState)
        {
            case CursorLockMode.None:
                GUILayout.Label("Cursor is normal");
                if (GUILayout.Button("Lock cursor"))
                    wantedMode = CursorLockMode.Locked;
                if (GUILayout.Button("Confine cursor"))
                    wantedMode = CursorLockMode.Confined;
                break;
            case CursorLockMode.Confined:
                GUILayout.Label("Cursor is confined");
                if (GUILayout.Button("Lock cursor"))
                    wantedMode = CursorLockMode.Locked;
                if (GUILayout.Button("Release cursor"))
                    wantedMode = CursorLockMode.None;
                break;
            case CursorLockMode.Locked:
                GUILayout.Label("Cursor is locked");
                if (GUILayout.Button("Unlock cursor"))
                    wantedMode = CursorLockMode.None;
                if (GUILayout.Button("Confine cursor"))
                    wantedMode = CursorLockMode.Confined;
                break;
        }

        GUILayout.EndVertical();

        SetCursorState();
    }
    IEnumerator setCurChunkPos()
    {
        yield return new WaitForSeconds(3);
        terraManager.CurCx = Mathf.FloorToInt(this.transform.position.x) >> 4;
        terraManager.CurCy = Mathf.FloorToInt(this.transform.position.y) >> 4;
        terraManager.CurCz = Mathf.FloorToInt(this.transform.position.z) >> 4;
        terraManager.cpx = this.transform.position.x;
        terraManager.cpy = this.transform.position.y;
        terraManager.cpz = this.transform.position.z;
    }
    
    void Update()
    {
        StartCoroutine(setCurChunkPos());
        rotationX += Input.GetAxis("Mouse X") * sensitivityX;
        this.gameObject.transform.eulerAngles = new Vector3(0, rotationX, 0);
        
        //Debug.Log(mc.transform.localEulerAngles);
        //根据鼠标移动的快慢（增量），获取相机上下移动的角度（处理Y）
        rotationY += Input.GetAxis("Mouse Y") * sensitivityY;
        //角度限制，rotationY小于min返回min  大于max 返回max  否则返回value
        rotationY = MyTools.Clamp(rotationY, maxmunY, minmumY);

        //设置摄像机角度
        mc.transform.localEulerAngles = new Vector3(-rotationY, 0, 0);
        //获取控制的方向， 上下左右，
        
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");

        if (cc.isGrounded)
        {
            moveDirection = new Vector3(h, 0, v);
            moveDirection = transform.TransformDirection(moveDirection);
            moveDirection *= moveSpeed*Time.deltaTime;
            
            if (Input.GetButton("Jump"))
            {
                
                moveDirection.y = jumpSpeed;
            }
        }



        //moveDirection.y = 5;

        //
        moveDirection.y -= g * Time.deltaTime;
        cc.Move(moveDirection);
        
    }
    
    
}