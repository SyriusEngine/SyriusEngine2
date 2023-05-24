#pragma once

#include "../../../../include/SyriusEngine/Renderer/Primitives.hpp"

namespace Syrius{

    class Pass;

    typedef enum NodeClass{
        NODE_CLASS_RENDER_PASS  = 0x01,
        NODE_CLASS_RESOURCE_PASS= 0x02,
    } NodeClass;

    typedef enum NodeType{
        NODE_CONSTANT_BUFFER    = 0x01,
        NODE_TEXTURE            = 0x02,
        NODE_FRAME_BUFFER       = 0x03,
        NODE_SHADER             = 0x04,
        NODE_SAMPLER            = 0x05,
    } NodeType;

    // instead of using a string, we use an enum to identify the pass type as it is faster to compare
    typedef enum PassType{
        CAMERA_DATA_PASS        = 0x01,
        LIGHT_DATA_PASS         = 0x02,
        PROJECTION_DATA_PASS    = 0x03,
        LIGHTING_PASS           = 0x04,
        SHADOW_PASS             = 0x05,
        GEOMETRY_PASS           = 0x06,
    } PassType;

    struct PassDesc{
        NodeClass nodeClass;
        NodeType nodeType;
        PassType passType;
        std::vector<PassType> dependencies;
        UID passID      = 0;
        Pass* pAddress  = nullptr;
    };

}