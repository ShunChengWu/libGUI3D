//
// Created by sc on 8/23/20.
//

#include <GUI3D/BBoxDrawer.h>

using namespace glUtil;


BBoxDrawer::BBoxDrawer() {
    for (auto &boxDrawer : mBoxDrawers) boxDrawer.Init();
}


BBoxDrawer::~BBoxDrawer(){
}

void BBoxDrawer::Draw(
        const Eigen::Matrix4f &projection,
        const Eigen::Matrix4f &viewMatrix,
        BoxDrawer::Mode mode) {
    for (auto &drawer:mBoxDrawers) {
        drawer.SetMode(mode);
        drawer.Draw(projection,viewMatrix);
    }
}

void BBoxDrawer::Set(const Eigen::Vector3f &pos, const Eigen::Vector3f &dims, const Eigen::Matrix4f &T) {
    float width = 0.01;
    Eigen::Vector3f base[12] = {
            {dims[0],width,width},
            {dims[0],width,width},
            {dims[0],width,width},
            {dims[0],width,width},
            {width,dims[1]+width,width},//plus width to fill the nonoverlapping region
            {width,dims[1]+width,width},//plus width to fill the nonoverlapping region
            {width,dims[1]+width,width},//plus width to fill the nonoverlapping region
            {width,dims[1]+width,width},//plus width to fill the nonoverlapping region
            {width,width,dims[2]},
            {width,width,dims[2]},
            {width,width,dims[2]},
            {width,width,dims[2]}
    };
    Eigen::Vector3f signs[12] = {
            {0,-1,-1},
            {0,-1,1},
            {0,1,-1},
            {0,1,1},
            {-1,0,-1},
            {-1,0,1},
            {1,0,-1},
            {1,0,1},
            {-1,-1,0},
            {-1,1,0},
            {1,-1,0},
            {1,1,0},
    };

    for (size_t i=0;i<12;++i) {
        Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
        model.diagonal().head<3>() = base[i];
        Eigen::Vector3f tmp = dims.array() * signs[i].array();
        model.topRightCorner<3,1>() = 0.5*tmp;
        model.topRightCorner<3,1>() += pos;
        model = T*model;
        mBoxDrawers[i].SetModel(model);
    }
}

void BBoxDrawer::SetColor(const Eigen::Vector4f &c) {
    for (auto &boxDrawer : mBoxDrawers) boxDrawer.SetColor(c);
}
