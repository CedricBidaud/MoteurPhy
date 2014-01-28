
#if defined(VERTEX)
layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

void main() {
	vTexCoord = aTexCoord;
	gl_Position = vec4(aVertexPosition, 0.f, 1.f);
}

#endif
/*
#if defined(GEOMETRY)

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vData
{
	vec2 uv;
    vec3 normal;
    vec3 position;
    float t;
}vertices[];

out fData
{
	vec2 uv;
    vec3 normal;
    vec3 position;
    float t;
}frag;

void main()
{
	int i;
	for (i = 0; i < gl_in.length(); ++i)
	{
		//gl_Position = gl_in[i].gl_Position;
		vec4 tempPos = gl_in[i].gl_Position;
		if(gl_PrimitiveIDIn % 2 == 0){
			// tempPos.x += 0.3*cos(vertices[i].t);
		}

		gl_Position = tempPos;

		frag.normal = vertices[i].normal;
		frag.position = vertices[i].position;
		frag.uv = vertices[i].uv;
		frag.t = vertices[i].t;
		EmitVertex();
	}
	EndPrimitive();
}

#endif
*/
#if defined(FRAGMENT)
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D Texture;

const float blurSizeH = 4.0 / 1024.0;
const float blurSizeV = 4.0 / 1024.0;

void main() {
	//~ fFragColor = vec3(vTexCoord.x, vTexCoord.y, 0.0);
	
	vec4 color = vec4(0.f);
	
	int blurSize = 5;
	int blurHalfSize = (blurSize - 1) / 2;
	
	for(int i = -blurHalfSize; i <= blurHalfSize; ++i){
		for(int j = -blurHalfSize; j <= blurHalfSize; ++j){
			
			color += texture( Texture, vec2(vTexCoord.x + i*blurSizeH, vTexCoord.y + j*blurSizeV) );
			
		}
	}
	fFragColor = color/(blurSize * blurSize);
}

#endif
