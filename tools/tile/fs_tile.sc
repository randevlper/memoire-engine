$input v_color0, v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
SAMPLER2D(u_tilemap,  0);
SAMPLER2D(u_tileset, 1);
uniform vec4 u_tileInfo;

void main()
{
	vec4 tile = texture2D(u_tilemap, v_texcoord0);
	vec2 offset = mod(v_texcoord0.xy, vec2((1.0/(u_tileInfo.x),(1.0/u_tileInfo.y)));

	gl_FragColor = texture2D(u_tileset, (tile.xy * u_tileInfo.xy) + offset);
}
