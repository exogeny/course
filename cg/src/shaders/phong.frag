varying vec3 normal;
varying vec3 lightVec;
varying vec3 viewVec;

void main() {
    vec3 Nn = normalize(normal);
    vec3 Vn = normalize(viewVec);
    vec3 Ln = normalize(lightVec);
    vec3 Hn = normalize(Vn+Ln);
    vec4 sceneColor;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
    
    if (gl_FrontFacing) { // front face
        sceneColor = gl_FrontLightModelProduct.sceneColor;
        ambient = gl_FrontLightProduct[0].ambient;
        diffuse = gl_FrontLightProduct[0].diffuse;
        specular = gl_FrontLightProduct[0].specular;
        shininess = gl_FrontMaterial.shininess;
    } else { // back face
        Nn = -Nn;
        sceneColor = gl_BackLightModelProduct.sceneColor;
        ambient = gl_BackLightProduct[0].ambient;
        diffuse = gl_BackLightProduct[0].diffuse;
        specular = gl_BackLightProduct[0].specular;
        shininess = gl_BackMaterial.shininess;
    }
    float LdotN = dot(Ln, Nn);
    float HdotN = max(dot(Hn, Nn), 0.0) * step(0.0, LdotN);
    LdotN = max(LdotN, 0.0);
    float spot;
    if (gl_LightSource[0].spotCutoff>90.0) spot = 1.0;
    else {
	    spot = dot(-Ln, normalize(gl_LightSource[0].spotDirection));
	    if (spot<gl_LightSource[0].spotCosCutoff) spot=0.0;
	    else spot = pow(spot, gl_LightSource[0].spotExponent);
    }    
    
    
    vec4 color = ambient + diffuse*LdotN + specular*pow(HdotN, shininess);
    color *= spot;
    color += sceneColor;
    
    color.w = 1.0;
    gl_FragColor = color;

}
