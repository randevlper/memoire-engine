$input v_texcoord0

#include "../common/common.sh"
SAMPLER2D(s_sprite,  0);
uniform vec4 u_color;

void main()
{
	gl_FragColor = u_color;
}
