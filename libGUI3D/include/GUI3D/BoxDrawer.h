//
// Created by sc on 8/23/20.
//

#ifndef GUI3D_BoxDrawer_H
#define GUI3D_BoxDrawer_H

#include <GUI3D/glShader.hpp>
#include <memory>

namespace glUtil {
    class BoxDrawer{
    public:
        BoxDrawer()=default;
        ~BoxDrawer();

        enum Mode {
            Line, Triangle
        };

        void Init();
//        void Update(const unsigned char *data, int width, int height);
        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix, Mode mode = Triangle);
        void SetModel(const Eigen::Matrix4f &model);
        void SetColor(const Eigen::Vector4f &c) {
            this->color = c;
        }
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        unsigned int VAO{}, VBO{}, EBO{};
        std::unique_ptr<glUtil::Shader> mShader;
        bool bInited=false;
        Eigen::Vector4f color {0,1,1,1};
    };
}

#endif //GUI3D_BoxDrawer_H
