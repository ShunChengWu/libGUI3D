//
// Created by sc on 8/23/20.
//

#ifndef GUI3D_IMAGEDRAWER_H
#define GUI3D_IMAGEDRAWER_H
//
//#ifdef COMPILE_WITH_EIGEN
//#include <Eigen/Core>
//#endif

#include "glShader.hpp"
#include <memory>

#ifdef COMPILE_WITH_EIGEN
#include <Eigen/Core>
#endif

namespace glUtil {
    class ImageDrawer {
    public:
        ~ImageDrawer();
        void Init(unsigned int textureWidth, unsigned int textureHeight, GLenum format = GL_RGBA);
        void Update(const unsigned char *data, int width, int height);
        void Draw();
#ifdef COMPILE_WITH_EIGEN
        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix);
#endif

        unsigned int GetTextureID() const {return textID;}
    private:
        GLenum mFormat;
        unsigned int VAO, VBO, textID;
        std::unique_ptr<glUtil::Shader> mShader;
        int m_width, m_height;
        bool bInited=false;
    };
    typedef std::shared_ptr<ImageDrawer> ImageDrawerPtr;
    [[maybe_unused]] static ImageDrawerPtr MakeImageDrawerPtr() {return std::make_shared<ImageDrawer>();}
}

#endif //GRAPHSLAM_IMAGEDRAWER_H
