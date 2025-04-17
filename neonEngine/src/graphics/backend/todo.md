Here’s a minimal C++ workflow for taking GLSL, running it through shaderc to produce SPIR‑V, then using SPIRV‑Cross to turn that into HLSL, and finally calling D3DCompile to get a Direct3D 11 shader blob. Note that shaderc itself only emits SPIR‑V—it doesn’t directly produce D3D11 bytecode.

1. Compile GLSL → SPIR‑V with shaderc
   cpp
   Copy
   Edit
   #include <shaderc/shaderc.hpp>

// …

shaderc::Compiler compiler;
shaderc::CompileOptions options;
// (optionally tweak options, e.g. include paths, optimization level, target env, etc.)
shaderc::SpvCompilationResult module =
compiler.CompileGlslToSpv(glsl_source,
shaderc_glsl_vertex_shader,
"shader.vert",
options);

if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
std::cerr << "GLSL→SPIR‑V error: "
<< module.GetErrorMessage() << "\n";
// handle error...
}

std::vector<uint32_t> spirv(module.cbegin(), module.cend());
GitHub

2. Cross‑compile SPIR‑V → HLSL with SPIRV‑Cross
   cpp
   Copy
   Edit
   #include <spirv_cross/spirv_cross.hpp>
   #include <spirv_cross/spirv_hlsl.hpp>

// …

spirv_cross::CompilerHLSL hlsl_compiler(spirv);
spirv_cross::CompilerHLSL::Options hlsl_opts;
hlsl_opts.shader_model = 50;  // target shader model 5.0
hlsl_compiler.set_hlsl_options(hlsl_opts);

std::string hlsl_source = hlsl_compiler.compile();
// hlsl_source now holds HLSL code suitable for D3DCompile
GitHub
best-of-web.builder.io

3. Compile HLSL → D3D11 shader bytecode
   cpp
   Copy
   Edit
   #include <d3dcompiler.h>
   // Link against d3dcompiler.lib

ID3DBlob* blob = nullptr;
HRESULT hr = D3DCompile(
hlsl_source.c_str(),
hlsl_source.size(),
"shader.hlsl",      // optional source name for errors
nullptr, nullptr,   // macros and include handler
"main",             // entry point
"vs_5_0",           // profile (e.g., vs_5_0, ps_5_0)
0, 0,
&blob,
nullptr);

if (FAILED(hr)) {
// inspect error blob or HRESULT
}
Microsoft Learn

Notes & references

Shaderc’s examples (e.g. online‑compile sample) show the basic GLSL→SPIR‑V API but don’t cover D3D targets
GitHub
.

SPIRV‑Cross is the de‑facto way to emit HLSL from SPIR‑V before feeding into D3DCompile
GitHub
.

See the d3rpp/spirv-example repo for a complete end‑to‑end demo