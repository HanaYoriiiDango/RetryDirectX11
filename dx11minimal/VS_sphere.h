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

    float3 pos = float3(
        rad * sin(p.y) * cos(p.x),
        rad * cos(p.y) + 5.0,
        rad * sin(p.y) * sin(p.x)
    );

    return pos;
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

    float4 pos = float4(p, -2.0, 5);
    pos.y += col * 2;
    pos.x += row * 2;
    pos.xy -= (float)n - 1;

    pos.xyz = Sphere(pos);

    output.vpos = pos;
    output.vnorm = float4(normalize(pos.xyz), 0.0f);

    output.pos = mul(pos, mul(view[0], proj[0]));
    output.uv = float2(1, -1) * p / 2. + .5;

    return output;
}
