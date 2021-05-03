$input v_texcoord0

#include "../common/common.sh"
SAMPLER2D(u_sprite,  0);
SAMPLER2D(u_sprite1, 1);

void main()
{
	vec4 sprite1Color = texture2D(u_sprite1, v_texcoord0);
	gl_FragColor = texture2D(u_sprite, v_texcoord0) + sprite1Color;

	vec3 s1c = vec3(sprite1Color.x, sprite1Color.y, sprite1Color.z);
	s1c = s1c * sprite1Color.a;
	vec3 sc = vec3(gl_FragColor.x, gl_FragColor.y, gl_FragColor.z);
	sc = sc * (vec3(1.0,1.0,1.0) - sprite1Color.a);

	gl_FragColor = vec4(s1c + sc, 1.0);

}
