$input a_position, a_texcoord0
$output v_texcoord0

#include "../common/common.sh"

void main()
{
	
	gl_Position = vec4(a_position, 1.0) - vec4(u_model[0][3][0], u_model[0][3][1], 0, 0);
	v_texcoord0 = a_texcoord0;
}
