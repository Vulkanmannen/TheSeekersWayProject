uniform sampler2D texture;

void main (void)
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	float gray = pixel.r * 0.39 + pixel.g * 0.50 + pixel.b * 0.11;
	
	gl_FragColor = vec4(gray, gray, gray, pixel.a);
}