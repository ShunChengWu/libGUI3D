//
// Created by sc on 8/24/20.
//

#ifndef GUI3D_TRAJECTORYDRAWER_H
#define GUI3D_TRAJECTORYDRAWER_H

#include <GUI3D/glShader.hpp>
#include <memory>
#include <vector>
namespace glUtil {
    class TrajectoryDrawer{
    public:
        ~TrajectoryDrawer();
        void Init();
        void Add(glm::vec3 point, float interval=0.002);
        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix);
    private:
        std::vector<glm::vec3> mvTrajectories;
        unsigned int VAO, VBO, EBO;
        float mScale = 0.2f;
        std::unique_ptr<glUtil::Shader> mShader;
        bool bInited=false;
        size_t mBufferSize = 1e3;

        void UpdateBuffer(size_t newSize, bool force = false);
    };
}

#endif //GUI3D_TRAJECTORYDRAWER_H
