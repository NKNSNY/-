struct OUTPUT
{
    float4 pos : SV_POSITION;
};

cbuffer ConstBuffer
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
}


OUTPUT VSmain(float4 pos : POSITION)
{
    OUTPUT output;

    output.pos = mul(pos , world);
    output.pos = mul(output.pos , view);
    output.pos = mul(output.pos , proj);

    return output;
}