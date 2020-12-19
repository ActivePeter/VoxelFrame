// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/NewShader" {
    Properties {
        _MainTex ("Base (RGB)", 2D) = "white" {}
		
    }
    SubShader
    {
        pass
        {
        
        CGPROGRAM
        #pragma vertex vert
        #pragma fragment frag
        #include "unitycg.cginc"
        sampler2D _MainTex;
        struct v2f
        {
        float4 pos : SV_POSITION ;
        float2 ModeUV: TEXCOORD0;
        };
        v2f vert(appdata_base v)
        {
        v2f o;
        o.pos=UnityObjectToClipPos(v.vertex);  //将模型顶点坐标转换到视图坐标矩阵中
        o.ModeUV=v.texcoord;   //获取模型的UV坐标
        return o;
        }
        fixed4 frag(v2f i):COLOR
        {
        fixed4 col;
		
		col=(0,1,1,0);
        if(i.ModeUV.x>_x1&&i.ModeUV.y>_y1-_r&&i.ModeUV.x<_x2&&i.ModeUV.y<_y2+_r){

        /*col=tex2D(_MainTex,i.ModeUV);  
		col=col*1.1;//根据模型UV坐标获取贴图相对应的颜色
        }else if(i.ModeUV.x>_x1-_r&&i.ModeUV.y>_y1&&i.ModeUV.x<_x2+_r&&i.ModeUV.y<_y2){
		col=tex2D(_MainTex,i.ModeUV); 
		col=col*1.1;
		}else if((i.ModeUV.x-_x1)*(i.ModeUV.x-_x1)+(i.ModeUV.y-_y1)*(i.ModeUV.y-_y1)<_r*_r||(i.ModeUV.x-_x1)*(i.ModeUV.x-_x1)+(i.ModeUV.y-_y2)*(i.ModeUV.y-_y2)<_r*_r||(i.ModeUV.x-_x2)*(i.ModeUV.x-_x2)+(i.ModeUV.y-_y1)*(i.ModeUV.y-_y1)<_r*_r||(i.ModeUV.x-_x2)*(i.ModeUV.x-_x2)+(i.ModeUV.y-_y2)*(i.ModeUV.y-_y2)<_r*_r){
		col=tex2D(_MainTex,i.ModeUV); 
		col=col*1.1;
		}else if(i.ModeUV.x>(_x1-edge)&&i.ModeUV.y>(_y1-edge)-_r&&i.ModeUV.x<(_x2+edge)&&i.ModeUV.y<(_y2+edge)+_r){
        col=tex2D(_MainTex,i.ModeUV);   
		col=col*0.8;//根据模型UV坐标获取贴图相对应的颜色
        }else if(i.ModeUV.x>(_x1-edge)-_r&&i.ModeUV.y>(_y1-edge)&&i.ModeUV.x<(_x2+edge)+_r&&i.ModeUV.y<(_y2+edge)){
		col=tex2D(_MainTex,i.ModeUV); 
		col=col*0.8;
		}else if((i.ModeUV.x-(_x1-edge))*(i.ModeUV.x-(_x1-edge))+(i.ModeUV.y-(_y1-edge))*(i.ModeUV.y-(_y1-edge))<_r*_r||(i.ModeUV.x-(_x1-edge))*(i.ModeUV.x-(_x1-edge))+(i.ModeUV.y-(_y2+edge))*(i.ModeUV.y-(_y2+edge))<_r*_r||(i.ModeUV.x-(_x2+edge))*(i.ModeUV.x-(_x2+edge))+(i.ModeUV.y-(_y1-edge))*(i.ModeUV.y-(_y1-edge))<_r*_r||(i.ModeUV.x-(_x2+edge))*(i.ModeUV.x-(_x2+edge))+(i.ModeUV.y-(_y2+edge))*(i.ModeUV.y-(_y2+edge))<_r*_r){
		col=tex2D(_MainTex,i.ModeUV);  
		col=col*0.8;
		}else{
		discard;
		}*/
		
        return col;        
        }
        ENDCG
        
        }
    }
}  