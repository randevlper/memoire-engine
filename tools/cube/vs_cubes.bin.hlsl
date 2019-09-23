// shaderc command line:
// shaderc -f cube/vs_cubes.sc --varyingdedf cube/varying.def.sc --type v -platform windows -p ps_4_0 -o cube/vs_cubes.bin -O 3 --debug

struct Output
{
float4 gl_Position : SV_POSITION;
float4 v_color0 : COLOR0;
};
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
uniform float4x4 u_modelViewProj;
Output main( float4 a_color0 : COLOR0 , float3 a_position : POSITION) { Output _varying_; _varying_.v_color0 = float4(1.0, 0.0, 0.0, 1.0);;
{
_varying_.gl_Position = ( (u_modelViewProj) * (float4(a_position, 1.0) ) );
_varying_.v_color0 = a_color0;
} return _varying_;
}
