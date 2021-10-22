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
	gl_FragColor = texture2D(u_sprite, v_texcoord0);
	gl_FragColor = vec4(u_color.x, u_color.y, u_color.z, gl_FragColor.w);
}
