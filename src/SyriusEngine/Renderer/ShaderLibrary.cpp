#include "../../../include/SyriusEngine/Renderer/ShaderLibrary.hpp"

namespace Syrius{

    ShaderLibrary::ShaderLibrary(ResourceView<Context> &context, const std::string &libraryPath):
    m_Context(context),
    m_Library(),
    m_LibraryPath(libraryPath){

    }

    ShaderLibrary::~ShaderLibrary() {

    }

    ShaderDesc &ShaderLibrary::getPackage(const std::string &name) {
        if (m_Library.find(name) == m_Library.end()){
            loadShader(name);
        }
        return m_Library[name];
    }

    void ShaderLibrary::loadShader(const std::string &name) {
        ShaderModuleDesc vsmDesc;
        vsmDesc.shaderType = SR_SHADER_VERTEX;
        vsmDesc.entryPoint = "main";
        vsmDesc.loadType = SR_LOAD_FROM_FILE;

        ShaderModuleDesc fsmDesc;
        fsmDesc.shaderType = SR_SHADER_FRAGMENT;
        fsmDesc.entryPoint = "main";
        fsmDesc.loadType = SR_LOAD_FROM_FILE;

        if (m_Context->getType() == SR_API_OPENGL){
            vsmDesc.codeType = SR_SHADER_CODE_GLSL;
            vsmDesc.code = m_LibraryPath + "GLSL/" + name + ".vert";
            fsmDesc.codeType = SR_SHADER_CODE_GLSL;
            fsmDesc.code = m_LibraryPath + "GLSL/" + name + ".frag";
        }
        else if (m_Context->getType() == SR_API_D3D11){
            vsmDesc.codeType = SR_SHADER_CODE_HLSL;
            vsmDesc.code = m_LibraryPath + "HLSL/" + name + ".vs";
            fsmDesc.codeType = SR_SHADER_CODE_HLSL;
            fsmDesc.code = m_LibraryPath + "HLSL/" + name + ".ps";
        }

        ShaderDesc package;
        package.vertexShader = m_Context->createShaderModule(vsmDesc);
        package.fragmentShader = m_Context->createShaderModule(fsmDesc);
        m_Library.insert({name, package});
    }
}
