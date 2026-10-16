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

    //VS_OUTPUT input = (VS_OUTPUT)0;

    // input
    float ambientStrength = 0.6f;
    float3 lightPos = float3(10.0f, 10.0f, 10.0f);

    float3 lightColor = float3(1.0f, 1.0f, 1.0f);
    float3 ObjectColor = float3(0.1f, 0.1f, 0.1f);

    float3 norm = input.pos;
    float3 lightDir = input.pos - lightPos;

    // ambient
    float3 ambient = ambientStrength * lightColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    float3 diffuse = diff * lightColor;

    // result
    float4 result = (ambient + diffuse) * ObjectColor;
    //float4 result = ambient;

    return float4(ambient, 1.0f);
}
