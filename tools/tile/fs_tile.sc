$input v_color0, v_texcoord0

#include "../common/common.sh"
SAMPLER2D(u_tilemap,  0);
SAMPLER2D(u_tileset, 1);
uniform vec4 u_tilesetInfo;
uniform vec4 u_tilemapInfo;

void main()
{
	vec4 tileColor = texture2D(u_tilemap, v_texcoord0);

	vec2 spriteCoord = (tileColor.rg * 256.0) * (u_tilesetInfo.zw / u_tilesetInfo.xy);
	vec2 offset =  mod(v_texcoord0, (u_tilesetInfo.zw / u_tilesetInfo.xy));

	gl_FragColor = texture2D(u_tileset, spriteCoord + offset);
}
