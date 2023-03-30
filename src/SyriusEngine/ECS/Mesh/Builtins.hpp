#pragma once

#include "MeshComponent.hpp"

namespace Syrius{

    class Cube: public MeshComponent{
    public:
        explicit Cube(RCP<PBRenderLayer>& renderLayer);

        ~Cube() override = default;

    };
    
    class Sphere: public MeshComponent{
    public:
        Sphere(RCP<PBRenderLayer>& renderLayer, uint32 rings, uint32 sectors);

        ~Sphere() override = default;
    };

    class Quad: public MeshComponent{
    public:
        explicit Quad(RCP<PBRenderLayer>& renderLayer);

        ~Quad() override;
    };

    class Triangle: public MeshComponent{
    public:
        explicit Triangle(RCP<PBRenderLayer>& renderLayer);

        ~Triangle() override;
    };

    class Pyramid: public MeshComponent{
    public:
        explicit Pyramid(RCP<PBRenderLayer>& renderLayer);

        ~Pyramid() override;
    };

    class Torus: public MeshComponent{
    public:
        Torus(RCP<PBRenderLayer>& renderLayer, uint32 rings, uint32 sectors);

        ~Torus() override;
    };

    class Cone: public MeshComponent{
    public:
        Cone(RCP<PBRenderLayer>& renderLayer, uint32 rings);

        ~Cone() override;
    };
}