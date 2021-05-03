$input v_texcoord0

#include "../common/common.sh"
SAMPLER2D(u_sprite,  0);
SAMPLER2D(u_sprite1, 1);

void main()
{
	gl_FragColor = texture2D(u_sprite1, v_texcoord0);
	gl_FragColor = mix(texture2D(u_sprite, v_texcoord0), gl_FragColor, gl_FragColor.a);
}
