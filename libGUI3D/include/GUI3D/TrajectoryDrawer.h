//
// Created by sc on 8/24/20.
//

#ifndef GUI3D_TRAJECTORYDRAWER_H
#define GUI3D_TRAJECTORYDRAWER_H

#include <GUI3D/glShader.hpp>
#include <memory>
#include <vector>
#ifdef COMPILE_WITH_EIGEN
#include <Eigen/Core>
#endif
namespace glUtil {
    class TrajectoryDrawer{
    public:
        TrajectoryDrawer();
        ~TrajectoryDrawer();
        void Init();
        void Add(glm::vec3 point, float interval=0.002);
        void SetColor(glm::vec4 color);
        void Draw(glm::mat4 proj, glm::mat4 view);
#ifdef COMPILE_WITH_EIGEN
        void Add(const Eigen::Vector3f &point, float interval=0.002);
        void SetColor(const Eigen::Vector4f &color);
        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix);
#endif
        void Clear();
    private:
        std::vector<glm::vec3> mvTrajectories;
        unsigned int VAO, VBO, EBO;
        float mScale = 0.2f;
        std::unique_ptr<glUtil::Shader> mShader;
        bool bInited=false;
        size_t mBufferSize = 1e3;
        glm::vec4 mColor;
        void UpdateBuffer(size_t newSize, bool force = false);
    };
}

#endif //GUI3D_TRAJECTORYDRAWER_H
