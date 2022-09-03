cbuffer b : register(b0)
{
	float4x4 test;
}

cbuffer t : register(b1)
{
	float a;
}

struct vsout
{
	float2 tc : TexCoords;
	float4 pos : SV_POSITION;
};


vsout main(float3 pos : POSITION,float3 grbage : norm,float2 tc : TexCoords)
{
	vsout ret;
	ret.pos = mul(test, float4(pos, 1.0f));
	ret.tc = tc;
	return ret;
}