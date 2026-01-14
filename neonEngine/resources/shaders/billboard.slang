
cbuffer Uniforms
{
    float4x4 viewMatrix;
    float4x4 projMatrix;
    int windowWidth;
    int windowHeight;
    int gizmoCount;
    float4 gizmoPositions[64];
};

RWTexture2D<float4> sceneColorTexture;

Texture2D<float4> gizmoTexture;
SamplerState gizmoSampler;

float4 circle(float2 uv, float2 pos, float rad, float3 color)
{
	float d = length(pos - uv) - rad;
	float t = clamp(d, 0.0, 1.0);
	return float4(color, 1.0 - t);
}


[shader("compute")]
[numthreads(16, 16, 1)]
void computeMain(uint2 dispatchThreadID: SV_DispatchThreadID)
{
    uint2 coord = dispatchThreadID.xy;
    float ndcX = ((float(coord.x) + 0.5) / float(windowWidth)) * 2.0 - 1.0;
    float ndcY = 1.0 - ((float(coord.y) + 0.5) / float(windowHeight)) * 2.0;
    float aspect = float(windowWidth) / float(windowHeight);
    float2 ndcCoord = float2(-ndcX * aspect, ndcY);

    for (int i = 0; i < gizmoCount; ++i)
    {
        float3 gizmoPos = gizmoPositions[i].xyz;
        float4 worldPos = float4(gizmoPos, 1.0);
        float4 viewPos  = mul(viewMatrix, worldPos);
        float4 clipPos = mul(projMatrix, viewPos);
        float2 ndcCenter = (clipPos.xy / clipPos.w);

        float2 rectHalfSize = float2(0.07, 0.07);

        float2 delta = ndcCoord - ndcCenter;
        if (abs(delta.x) <= rectHalfSize.x && abs(delta.y) <= rectHalfSize.y)
        {
            float3 original = sceneColorTexture[coord].xyz;
            float2 uv = (delta + rectHalfSize) / (rectHalfSize * 2.0);

            float4 newColor = gizmoTexture.Sample(gizmoSampler, uv);
            sceneColorTexture[coord] = float4(lerp(original, newColor.xyz, newColor.a), 1.0);
            return;
        }
    }
}
