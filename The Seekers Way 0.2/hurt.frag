uniform sampler2D texture;

void main (void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	gl_FragColor = vec4(pixel.r, pixel.g * 0.4, pixel.b * 0.4, pixel.a);
}