//
// Created by sc on 8/23/20.
//

#ifndef GUI3D_EllipsoidDrawer_H
#define GUI3D_EllipsoidDrawer_H

#include <GUI3D/glShader.hpp>
#include <memory>

namespace glUtil {
/**
 * modified from
 * https://stackoverflow.com/questions/60686457/issue-in-drawing-ellipsoid-with-opengl
 * better implementation
 * http://www.songho.ca/opengl/gl_sphere.html
 *
 */
    class EllipsoidDrawer {
    public:
        EllipsoidDrawer();
        ~EllipsoidDrawer();
        void Draw(const Eigen::Matrix4f &projection,
                  const Eigen::Matrix4f &viewMatrix) const;

        void SetStacks(int n);

        void SetSlices(int n);

        [[nodiscard]] int GetStacks() const;

        [[nodiscard]] int GetSlices() const;

        void Init();

        void SetModel(const Eigen::Matrix4f &model);

        void SetColor(const Eigen::Vector4f &c);
    private:
        unsigned int VAO{}, VBO{}, EBO{};
        std::unique_ptr<glUtil::Shader> mShader;
        Eigen::Vector4f color;
        int stacks;
        int slices;

        void Generate();
    };
}

#endif //GUI3D_EllipsoidDrawer_H
