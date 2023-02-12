#pragma once

#include "Primitives.hpp"

namespace Syrius{

    class ShaderLibrary{
    public:
        ShaderLibrary(ResourceView<Context>& context, const std::string& libraryPath);

        ~ShaderLibrary();

        ShaderDesc& getPackage(const std::string& name);

    private:

        void loadShader(const std::string& name);

    private:
        std::string m_LibraryPath;
        ResourceView<Context>& m_Context;
        std::unordered_map<std::string, ShaderDesc> m_Library;
    };

}