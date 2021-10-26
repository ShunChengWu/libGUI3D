//
// Created by sc on 10/26/21.
//
#include <GUI3D/EllipsoidDrawer.h>

using namespace glUtil;

EllipsoidDrawer::EllipsoidDrawer():
color(0,1,1,1),stacks(8),slices(16){

}

EllipsoidDrawer::~EllipsoidDrawer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void EllipsoidDrawer::Draw(const Eigen::Matrix4f &projection, const Eigen::Matrix4f &viewMatrix) const {
    mShader->use();
    mShader->set("color", color);
    mShader->set("view",viewMatrix);
    mShader->set("projection",projection);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_LINES,     (slices * stacks + slices) * 6, GL_UNSIGNED_INT, nullptr);
//        glDrawElements(GL_TRIANGLES, (slices * stacks + slices) * 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void EllipsoidDrawer::SetStacks(int n) {stacks=n;}

void EllipsoidDrawer::SetSlices(int n) {slices=n;}

int EllipsoidDrawer::GetStacks() const {return stacks;}

int EllipsoidDrawer::GetSlices() const {return slices;}

void EllipsoidDrawer::Init() {
    /*shader*/
    const std::string vsShader = "#version 330\n"
                                 "layout(location = 0) in vec3 position;\n"
                                 //                                     "layout(location = 1) in vec3 normal;\n"
                                 //                                     "layout(location = 2) in vec2 texture;\n"
                                 "uniform mat4 model;\n"
                                 "uniform mat4 view;\n"
                                 "uniform mat4 projection;\n"
                                 "void main() {\n"
                                 "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                 "}";

    const std::string fsShader = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "uniform vec4 color;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    FragColor = color;   \n"
                                 "}";
    mShader = std::make_unique<glUtil::Shader>(vsShader,fsShader);
    mShader->use();
    mShader->set("model", glm::mat4(1.f));
    mShader->set("color", color);

    Generate();
}

void EllipsoidDrawer::SetModel(const Eigen::Matrix4f &model) {
    mShader->use();
    mShader->set("model",model);
}

void EllipsoidDrawer::Generate() {
    std::vector<glm::vec3> positions;
//        normals.clear();
//        textureCoords.clear();

    Eigen::Vector3f p;
    //Eigen::Vector3f n;
    for(int i = 0; i <= stacks; ++i) {

        // V texture coordinate.
//            float V = i / (float)stacks;
//            float phi = V * M_PI;
        float V = i / (float)stacks;
        float phi = V * M_PI - M_PI/2.0;

        for( int j = 0; j <= slices; ++j) {

            // U texture coordinate.
            float U = j / (float)slices;
            float theta = U * 2.0f * M_PI;

//                p.x() = /*dims.x() **/ cos(theta) * sin(phi);
//                p.y() = /*dims.y() **/ cos(phi);
//                p.z() = /*dims.z() **/ sin(theta) * sin(phi);

            p.x() = cos(phi) * cos(theta);
            p.y() = cos(phi) * sin(theta);
            p.z() = sin(phi);


//                p += center;
//                p = T.topLeftCorner<3,3>() * p + T.topRightCorner<3,1>();

//                n = (T.topLeftCorner<3,3>() * p).normalized();

            positions.emplace_back( p.x(), p.y(), p.z());
//                normals.push_back( glm::vec3(n.x(), n.y(), n.z()) );
//                textureCoords.push_back( glm::vec2(U, V) );

        }

    }

    // Now generate the index buffer
    std::vector<GLuint> indicies;

    int noPerSlice = slices + 1;

    for(int i=0; i < stacks; ++i) {

        for (int j=0; j < slices; ++j) {

            int start_i = (i * noPerSlice) + j;

            indicies.push_back( start_i );
            indicies.push_back( start_i + noPerSlice + 1 );
            indicies.push_back( start_i + noPerSlice );

            indicies.push_back( start_i + noPerSlice + 1 );
            indicies.push_back( start_i );
            indicies.push_back( start_i + 1 );

        }
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

//        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, nullptr);
//        glEnableVertexAttribArray(2);
//
//        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
//        glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), textureCoords.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
//        glEnableVertexAttribArray(8);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void EllipsoidDrawer::SetColor(const Eigen::Vector4f &c) {
    color = c;
}

