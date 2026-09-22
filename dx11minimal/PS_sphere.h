cbuffer global : register(b5)
{
    float4 gConst[32];
};

cbuffer frame : register(b4)
{
    float4 time;
    float4 aspect;
};

cbuffer camera : register(b3)
{
    float4x4 world[2];
    float4x4 view[2];
    float4x4 proj[2];
};

cbuffer drawMat : register(b2)
{
    float4x4 model;
    float hilight;
};

cbuffer params : register(b1)
{
    float r, g, b;
};

cbuffer driverP : register(b1)
{
    float4 drawConst[32];

};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 vpos : POSITION0;
    float4 wpos : POSITION1;
    float4 vnorm : NORMAL1;
    float2 uv : TEXCOORD0;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
    float ambientStrength = 0.6f;
    
    float3 lightColor = float3(1.0f, 1.0f, 1.0f);

    float3 ObjectColor = float3(0.1f, 0.1f, 0.1f);

    float3 ambient = ambientStrength * lightColor;
    float3 result = ambient * ObjectColor;
    

    return float4(result, 1.); // white
}
