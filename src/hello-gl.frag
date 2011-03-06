#version 110

uniform sampler2D tex;

void main()
{
    gl_FragColor = texture2D(tex, gl_TexCoord[0].st);
    //+ vec4(1.0, 0.0, 1.0, 0.5);
}

