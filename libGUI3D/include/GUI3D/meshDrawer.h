//
// Created by sc on 8/9/21.
//

#ifndef GUI3D_MESHDRAWER_H
#define GUI3D_MESHDRAWER_H
#include <GUI3D/glShader.hpp>
#include <memory>
namespace glUtil {
    class MeshDrawer {
    public:
        MeshDrawer();;

        void Init();

        void SetDiffuseStrength(float value) {
            mDiffuseStrength = value;
        }

        void Update(std::vector<Eigen::Vector3f> *points,
                    std::vector<Eigen::Vector3f> *colors,
                    std::vector<Eigen::Vector3f> *normals,
                    std::vector<Eigen::Vector3<unsigned int>> *indices);

        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix);

    private:
        size_t mPointBufferSize, mIndicesBufferSize;
        unsigned int VAO{}, VBO{}, EBO{};
        std::unique_ptr<glUtil::Shader> mShader{};
        size_t mTotalPoints{}, mTotalIndices{};
        float mDiffuseStrength = 0.5;

        void updateIndicesBuffer(size_t newSize, bool force= false);

        void updateVertexBuffer(size_t newSize, bool force = false);

        void Reset();

    };
    typedef std::shared_ptr<MeshDrawer> MeshDrawerPtr;
    static inline MeshDrawerPtr MakeMeshDrawerPtr(){
        return std::make_shared<MeshDrawer>();
    }
}

#endif //GUI3D_MESHDRAWER_H
