//
// Created by sc on 11/8/21.
//
#ifndef GUI3D_OBJECTDRAWERBASE_H
#define GUI3D_OBJECTDRAWERBASE_H
#include <GUI3D/glShader.hpp>
#include <memory>

namespace glUtil {
    class ObjectDrawerBase {
    public:
        ~ObjectDrawerBase()=default;
        virtual void Init() = 0;
        virtual void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix) = 0;
        virtual void SetModel(const Eigen::Matrix4f &model) {
            mShader->use();
            mShader->set("model",model);
        }
    protected:
        unsigned int VAO{}, VBO{}, EBO{};
        std::unique_ptr<glUtil::Shader> mShader;
    };
}
#endif //GUI3D_OBJECTDRAWERBASE_H
