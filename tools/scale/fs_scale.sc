$input v_texcoord0

#include "../common/common.sh"
SAMPLER2D(u_sprite,  0);

void main()
{
	gl_FragColor = texture2D(u_sprite, v_texcoord0);
}
