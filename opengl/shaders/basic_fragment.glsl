#version 330 core
    layout(location = 0) out vec4 color;
    void main()
    {
        vec4 result = vec4(gl_FragCoord.x/1920.0, gl_FragCoord.y/1080.0, gl_FragCoord.z, 1.0);
        result = vec4(result.x*2-1, result.y*2-1, result.z, 1.0);
        vec4 tan1 = dFdx(result);
        vec4 tan2 = dFdy(result);
        vec3 crossed = cross(vec3(tan1.xyz), vec3(tan2.xyz));
        vec3 normal = normalize(crossed);
        color = vec4(normal.xyz, 1.0);
    }