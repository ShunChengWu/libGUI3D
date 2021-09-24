//
// Created by sc on 8/23/20.
//

#ifndef GUI3D_BBoxDrawer_H
#define GUI3D_BBoxDrawer_H

#include <GUI3D/BoxDrawer.h>
namespace glUtil {
    class BBoxDrawer{
    public:
        BBoxDrawer();
        ~BBoxDrawer();

        void Init(){};

        void Draw(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& viewMatrix, BoxDrawer::Mode mode = BoxDrawer::Mode::Triangle);

        void Set(const Eigen::Vector3f &pos, const Eigen::Vector3f &dims, const Eigen::Matrix4f &T);

        void SetColor(const Eigen::Vector4f &c);

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    private:
        BoxDrawer mBoxDrawers[12];
    };
}

#endif //GUI3D_BBoxDrawer_H
