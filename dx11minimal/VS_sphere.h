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

cbuffer drawerV : register (b0)
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

float3 Sphere(float2 p) {
    float rad = 3;
    float n = (float)drawConst[0];

    p.x = (p.x / n) * 2.0 * 3.141592653589793;
    p.y = (p.y / n) * 3.141592653589793;

    return float3(
        rad * sin(p.y) * cos(p.x),
        rad * cos(p.y),          
        rad * sin(p.y) * sin(p.x)
    );
}

VS_OUTPUT VS(uint vID : SV_VertexID)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    uint n = drawConst[0];
    uint instanceID = vID / 6;
    float row = instanceID % n;
    float col = instanceID / n;

    float2 quad[6] = { -1, -1, 1, -1, -1, 1, 1, -1, 1, 1, -1, 1 };
    float2 p = quad[vID % 6];

    float2 uv = (p / 2.0 + 0.5);

    float3 pos = Sphere(float2(row + uv.x, col + uv.y));

    output.vpos = float4(pos, 1);
    output.wpos = mul(float4(pos, 1), drawMat.model);
    output.vnorm = float4(normalize(pos), 0);
    output.pos = mul(output.wpos, mul(view[0], proj[0]));
   
    output.uv = float2(1, -1) * p / 2. + .5;

    return output;
}
