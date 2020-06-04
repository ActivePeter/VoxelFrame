﻿
//颜色可以调版单色透明Shader


Shader "浅墨Shader编程/Volume13/2.ColorChangeAlpha"
{
	//------------------------------------【属性值】------------------------------------
	Properties
	{
		//颜色值
		_ColorWithAlpha("ColorWithAlpha", Color) = (0.9, 0.1, 0.1, 0.5)
	}

		//------------------------------------【唯一的子着色器】------------------------------------
		SubShader
	{
		//设置Queue为透明，在所有非透明几何体绘制之后再进行绘制
		Tags{ "Queue" = "Transparent" }

		//--------------------------------唯一的通道-------------------------------
		Pass
	{
		//不写入深度缓冲,为了不遮挡住其他物体
		ZWrite Off

		//选取Alpha混合方式
		Blend  SrcAlpha SrcAlpha
		//Blend SrcAlpha OneMinusSrcAlpha

		//===========开启CG着色器语言编写模块============
		CGPROGRAM

		//编译指令:告知编译器顶点和片段着色函数的名称
#pragma vertex vert 
#pragma fragment frag

		//变量声明
		uniform float4 _ColorWithAlpha;

	//--------------------------------【顶点着色函数】-----------------------------
	// 输入：POSITION语义（坐标位置）
	// 输出：SV_POSITION语义（像素位置）
	//---------------------------------------------------------------------------------
	float4 vert(float4 vertexPos : POSITION) : SV_POSITION
	{
		//坐标系变换
		//输出的顶点位置（像素位置）为模型视图投影矩阵乘以顶点位置，也就是将三维空间中的坐标投影到了二维窗口
		return mul(UNITY_MATRIX_MVP, vertexPos);
	}

		//--------------------------------【片段着色函数】-----------------------------
		// 输入：无
		// 输出：COLOR语义（颜色值）
		//---------------------------------------------------------------------------------
		float4 frag(void) : COLOR
	{
		//返回自定义的RGBA颜色
		return _ColorWithAlpha;
	}

		//===========结束CG着色器语言编写模块===========
		ENDCG
	}
	}
}