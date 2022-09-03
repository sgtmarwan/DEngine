
Texture2D tex : register(t0);
SamplerState smpl : register(s0);
float4 main(float2 tc : TexCoords) : SV_TARGET
{
	return tex.Sample(smpl, tc);
}