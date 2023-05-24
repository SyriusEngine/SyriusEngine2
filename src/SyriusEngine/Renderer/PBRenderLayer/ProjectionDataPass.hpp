#pragma once

#include "ResourcePass.hpp"

namespace Syrius{

    struct ProjectionDesc{
        float m_Width   = 1280.0f;
        float m_Height  = 720.0f;
        float m_Xpos    = 0.0f;
        float m_Ypos    = 0.0f;
        float m_Fov     = 45.0f;
        float m_Near    = 0.1f;
        float m_Far     = 100.0f;
    };

    class ProjectionDataPass : public ResourcePass{
    public:
        ProjectionDataPass(ResourceView<Context>& context, const ProjectionDesc& desc);

        ~ProjectionDataPass() override;

        void onResize(uint32 width, uint32 height);

        void setPosition(int32 xpos, int32 ypos);

        void setFOV(float fov);

        void setDepth(float near, float far);

    private:

        void setProjectionData();

    private:
        ProjectionDesc m_ProjectionDesc;

    };

}
