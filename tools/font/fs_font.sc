$input v_color0, v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
SAMPLER2D(s_sprite,  0);

void main()
{
	gl_FragColor = texture2D(s_sprite, v_texcoord0);
}
