// shaderc command line:
// shaderc -f cube/fs_cubes.sc --varyingdedf cube/varying.def.sc --type f -platform windows -p ps_4_0 -o cube/fs_cubes.bin -O 0 --debug

float3 instMul(float3 _vec, float3x3 _mtx) { return ( (_vec) * (_mtx) ); }
float3 instMul(float3x3 _mtx, float3 _vec) { return ( (_mtx) * (_vec) ); }
float4 instMul(float4 _vec, float4x4 _mtx) { return ( (_vec) * (_mtx) ); }
float4 instMul(float4x4 _mtx, float4 _vec) { return ( (_mtx) * (_vec) ); }
float rcp(float _a) { return 1.0/_a; }
float2 rcp(float2 _a) { return float2(1.0)/_a; }
float3 rcp(float3 _a) { return float3(1.0)/_a; }
float4 rcp(float4 _a) { return float4(1.0)/_a; }
float2 vec2_splat(float _x) { return float2(_x, _x); }
float3 vec3_splat(float _x) { return float3(_x, _x, _x); }
float4 vec4_splat(float _x) { return float4(_x, _x, _x, _x); }
float4x4 mtxFromRows(float4 _0, float4 _1, float4 _2, float4 _3)
{
return float4x4(_0, _1, _2, _3);
}
float4x4 mtxFromCols(float4 _0, float4 _1, float4 _2, float4 _3)
{
return transpose(float4x4(_0, _1, _2, _3) );
}
float3x3 mtxFromCols(float3 _0, float3 _1, float3 _2)
{
return transpose(float3x3(_0, _1, _2) );
}
uniform float4 u_viewRect;
uniform float4 u_viewTexel;
uniform float4x4 u_view;
uniform float4x4 u_invView;
uniform float4x4 u_proj;
uniform float4x4 u_invProj;
uniform float4x4 u_viewProj;
uniform float4x4 u_invViewProj;
uniform float4x4 u_model[32];
uniform float4x4 u_modelView;
uniform float4x4 u_modelViewProj;
uniform float4 u_alphaRef4;
void main( float4 gl_FragCoord : SV_POSITION , float4 v_color0 : COLOR0 , out float4 bgfx_FragData0 : SV_TARGET0 )
{
float4 bgfx_VoidFrag = vec4_splat(0.0);
bgfx_FragData0 = v_color0;
}
