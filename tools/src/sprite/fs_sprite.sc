$input v_color0, v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
SAMPLER2D(u_sprite,  0);
uniform vec4 u_color;

void main()
{
	gl_FragColor = mul(texture2D(u_sprite, v_texcoord0), u_color);
}
