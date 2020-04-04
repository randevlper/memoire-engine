$input v_color0, v_texcoord0

#include "../common/common.sh"
SAMPLER2D(u_tilemap,  0);
SAMPLER2D(u_tileset, 1);
uniform vec4 u_tilesetInfo;
uniform vec4 u_tilemapInfo;

void main()
{
	vec4 tileColor = texture2D(u_tilemap, v_texcoord0);
	vec2 spriteCoord = (tileColor.rg * 256.0) * (u_tilesetInfo.z / u_tilesetInfo.x);
	float difX = (u_tilemapInfo.z / u_tilemapInfo.x) / (u_tilesetInfo.z / u_tilesetInfo.x);
	float difY = (u_tilemapInfo.w / u_tilemapInfo.y) / (u_tilesetInfo.w / u_tilesetInfo.y);
	vec2 offset = vec2(0.0,0.0);
	offset.x = mod(v_texcoord0.x / difX, (u_tilesetInfo.z / u_tilesetInfo.x));
	offset.y = mod(v_texcoord0.y / difY, (u_tilesetInfo.w / u_tilesetInfo.y));

	gl_FragColor = texture2D(u_tileset, spriteCoord + offset);
}
