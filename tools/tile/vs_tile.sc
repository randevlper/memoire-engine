$input a_position, a_color0, a_texcoord0
$output v_color0, v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_pos;

void main()
{
	gl_Position = vec4(u_pos.xy,0,0) + mul(u_modelViewProj, vec4(a_position, 1.0));
	v_color0 = a_color0;
	v_texcoord0 = a_texcoord0;
}
