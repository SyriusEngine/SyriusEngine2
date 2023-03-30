#include "Builtins.hpp"

namespace Syrius{

    MeshDesc createCube(){
        MeshDesc cube;
        cube.vertices = {
                /// front
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// left
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// bottom
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// back
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// right
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// top
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        };
        cube.indices = {
                0, 3, 2,
                0, 2, 1,

                4, 7, 6,
                4, 6, 5,

                8, 11, 10,
                8, 10, 9,

                12, 15, 14,
                12, 14, 13,

                16, 19, 18,
                16, 18, 17,

                20, 23, 22,
                20, 22, 21
        };
        return cube;
    }


    Cube::Cube(RCP<PBRenderLayer> &renderLayer):
    MeshComponent(createCube(), renderLayer){

    }

    MeshDesc createSphere(uint32 rings, uint32 sectors){
        MeshDesc mesh;
        float const R = 1.0f/(float)(rings-1);
        float const S = 1.0f/(float)(sectors-1);
        uint32 r, s;

        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -M_PI_2 + M_PI * r * R );
                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

                mesh.vertices.push_back({{x, y, z}, {x, y, z}, {0.0f, 1.0f, 0.0f}, {s*S, r*R}});
            }

        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                mesh.indices.push_back(r * sectors + s);
                mesh.indices.push_back(r * sectors + (s+1));
                mesh.indices.push_back((r+1) * sectors + (s+1));

                mesh.indices.push_back(r * sectors + s);
                mesh.indices.push_back((r+1) * sectors + (s+1));
                mesh.indices.push_back((r+1) * sectors + s);
            }
        return mesh;
    }

    Sphere::Sphere(RCP<PBRenderLayer> &renderLayer, uint32 rings, uint32 sectors)
    : MeshComponent(createSphere(rings, sectors), renderLayer){

    }

    MeshDesc createQuad(){
        MeshDesc mesh;
        mesh.vertices = {
                { { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
                { {  0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
                { {  0.5f,  -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
                { { -0.5f,  -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
        };

        mesh.indices = {
                0, 3, 2,
                0, 2, 1
        };
        return mesh;
    }

    Quad::Quad(RCP<PBRenderLayer> &renderLayer) :
    MeshComponent(createQuad(), renderLayer) {

    }

    Quad::~Quad() = default;

    MeshDesc createTriangle(){
        MeshDesc mesh;
        mesh.vertices = {
                { { -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
                { {  0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
                { {  0.0f,  -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
        };

        mesh.indices = {
                0, 2, 1
        };
        return mesh;
    }

    Triangle::Triangle(RCP<PBRenderLayer> &renderLayer) :
    MeshComponent(createTriangle(), renderLayer) {

    }

    Triangle::~Triangle() {

    }

    MeshDesc createPyramid(){
        MeshDesc mesh;
        mesh.vertices = {
                { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
                { {  0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
                { {  -0.5f,  -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
                { {  -0.5f,  -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
                { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} },
        };

        mesh.indices = {
                0, 1, 2,
                0, 2, 3,
                0, 3, 4,
                0, 4, 1,
                1, 4, 3,
                1, 3, 2
        };
        return mesh;
    }

    Pyramid::Pyramid(RCP<PBRenderLayer> &renderLayer) :
    MeshComponent(createPyramid(), renderLayer) {

    }

    Pyramid::~Pyramid() = default;

    MeshDesc createTorus(uint32 rings, uint32 sectors){
        MeshDesc mesh;
        float const R = 1.0f/(float)(rings-1);
        float const S = 1.0f/(float)(sectors-1);
        uint32 r, s;

        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = (1 + 0.5f * cos(2*M_PI * r * R)) * sin(-M_PI_2 + M_PI * s * S);
                float const x = (1 + 0.5f * cos(2*M_PI * r * R)) * cos(2*M_PI * s * S);
                float const z = 0.5f * sin(2*M_PI * r * R);

                mesh.vertices.push_back({{x, y, z}, {x, y, z}, {0.0f, 1.0f, 0.0f}, {s*S, r*R}});
            }

        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                mesh.indices.push_back(r * sectors + s);
                mesh.indices.push_back(r * sectors + (s+1));
                mesh.indices.push_back((r+1) * sectors + (s+1));

                mesh.indices.push_back(r * sectors + s);
                mesh.indices.push_back((r+1) * sectors + (s+1));
                mesh.indices.push_back((r+1) * sectors + s);
            }
        return mesh;
    }

    Torus::Torus(RCP<PBRenderLayer> &renderLayer, uint32 rings, uint32 sectors):
    MeshComponent(createTorus(rings, sectors), renderLayer){

    }

    Torus::~Torus() = default;

    MeshDesc createCone(uint32 sectors){
        MeshDesc mesh;
        float const S = 1.0f/(float)(sectors-1);
        uint32 s;

        mesh.vertices.push_back({{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
        for(s = 0; s < sectors; s++) {
            float const x = cos(2*M_PI * s * S);
            float const z = sin(2*M_PI * s * S);

            mesh.vertices.push_back({{x, -0.5f, z}, {x, -0.5f, z}, {0.0f, 1.0f, 0.0f}, {s*S, 1.0f}});
        }

        for(s = 0; s < sectors-1; s++) {
            mesh.indices.push_back(0);
            mesh.indices.push_back(s+1);
            mesh.indices.push_back(s+2);
        }
        mesh.indices.push_back(0);
        mesh.indices.push_back(sectors);
        mesh.indices.push_back(1);
        return mesh;
    }

    Cone::Cone(RCP<PBRenderLayer> &renderLayer, uint32 rings):
    MeshComponent(createCone(rings), renderLayer){

    }

    Cone::~Cone() {

    }

}
