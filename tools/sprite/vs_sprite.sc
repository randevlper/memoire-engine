$input a_position, a_color0, a_texcoord0
$output v_color0, v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
uniform mat3 s_world;

void main()
{
	mat4 m = mul(mat4(s_world), u_modelViewProj);
	gl_Position = mul(m, vec4(a_position, 1.0));
	v_color0 = a_color0;
	v_texcoord0 = a_texcoord0;
}
