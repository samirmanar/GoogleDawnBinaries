
struct Uniforms {
    modelMatrix: mat4x4f,
    viewMatrix: mat4x4f,
    projectionMatrix: mat4x4f,
    lightPos: vec3f,
    cameraPos: vec3f
};

@group(0) @binding(0) var<uniform> uniforms: Uniforms;

struct VertexInput {
    @location(0) position: vec3f,
    @location(1) color: vec3f,
    @location(2) normal: vec3f
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    @location(0) color: vec3f,
    @location(1) normal: vec3f,
    @location(2) fragPos: vec3f,
    @location(3) cameraPos: vec3f
};

@vertex
fn vs_main(in: VertexInput, @builtin(vertex_index) in_vertex_index: u32) -> VertexOutput {

    var out: VertexOutput;
    out.position = uniforms.projectionMatrix * uniforms.viewMatrix * uniforms.modelMatrix * vec4f(in.position, 1.0);
    out.fragPos = (uniforms.modelMatrix * vec4f(in.position, 1.0)).xyz;
    out.color = in.color;
    out.normal = (uniforms.modelMatrix * vec4f(in.normal, 1.0)).xyz;

    return out;
}

fn calcDiffuse(norm: vec3f, lightDir: vec3f) -> f32 {

    var diffuse = max(dot(norm, lightDir), 0.0);
    return diffuse;
}

fn calcSpecular(norm: vec3f, lightDir: vec3f, fragPos: vec3f) -> f32 {

    const specularStrength = 5.0;
    var viewDir = normalize(uniforms.cameraPos - fragPos);
    var reflectDir = reflect(-lightDir, norm);
    var spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    var specular = specularStrength * spec; 

    return specular;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {

    var norm = normalize(in.normal);
    var lightDir = normalize(uniforms.lightPos - in.fragPos);

    var diffuse = calcDiffuse(norm, lightDir);
    var specular = calcSpecular(norm, lightDir, in.fragPos);

    var result = (diffuse + specular) * in.color;
    return vec4f(result, 1.0);
}
