using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
public class MyTools{

	public static Vector2[] calcuUV(int index) //return UV MESSAGE by index in texture
    {
        int y = index / 2;
        int x = index % 2;

        return new Vector2[] {
            new Vector2((float)1/2*x,(float)1/2*y),
            new Vector2((float)1/2*(x+1),(float)1/2*y),
            new Vector2((float)1/2*x,(float)1/2*(y+1)),
            new Vector2((float)1/2*(x+1),(float)1/2*(y+1))
        };
    }
    public static float Clamp(float value, float max, float min)//return NUMBER in range
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    public static Quaternion RotateInUpdateWithFixedTime(Quaternion from,float x,float y,float z){
        Quaternion toRotation=Quaternion.Euler(x,y,z)*Quaternion.identity;
        
        return Quaternion.Slerp(from,toRotation,Time.deltaTime*5);
    }
    public static Vector3 MoveInUpdateWithFixedTime(Vector3 from, Vector3 to)
    {
        return Vector3.Lerp(from, to, 15 * Time.deltaTime);
    }
    public static float FloatInUpdateWithFixedTimeAndSetToFinal(float from,float to){
        if(Mathf.Abs(from-to)>0.00001){
            return Mathf.Lerp(from,to,Time.deltaTime*10);
        }else
        {
            return to;
        }
    }
    public static float FloatInUpdateWithFixedTimeAndSetToFinalWithSpeed(float from,float to,float Speed){
        if(Mathf.Abs(from-to)>0.00001){
            return Mathf.Lerp(from,to,Time.deltaTime*Speed);
        }else
        {
            return to;
        }
    }
    public static bool floatCursoryEqual(float a,float b){
        return Mathf.Abs(a-b)<0.001;
    }
    public static Color GetColor(int r,int g,int b,int a){
        return new Color(r/255f,g/255f,b/255f,a/255f);
    }
    public static uniKey Unikey(int id1,int id2){
        uniKey u;
        u.id1=id1;
        u.id2=id2;

        return u;
    }
    static int gcd(int a, int b)//最大公约数 
    {
        if (a < b) { a = a + b; b = a - b; a = a - b; }
        return (a % b == 0) ? b : gcd(a % b, b);
    }

    public static int lcm(int a, int b)
    {
        return a * b / gcd(a, b);
    }
}
