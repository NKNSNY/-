int seed = 100;

float RandomCreate(float2 texcoord , int seed)
{
	return frac(sin(dot(texcoord.xy , float2(12.9898 , 78.233)) + seed) * 43758.5453);
}

float4 PSmain(float2 texcoord : TEXCOORD) : SV_Target
{
	float value = RandomCreate(texcoord , seed);
	return float4(value , value , value , 1.0f);
}