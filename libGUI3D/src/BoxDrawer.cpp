//
// Created by sc on 8/23/20.
//

#include <GUI3D/BoxDrawer.h>

using namespace glUtil;

BoxDrawer::~BoxDrawer(){
    if(bInited) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
    }
}

void BoxDrawer::Init() {
    const std::string vsShader = "#version 330\n"
                                 "layout(location = 0) in vec3 position;\n"
                                 "layout(location = 1) in vec3 aNormal;\n"
                                 "uniform mat4 model;\n"
                                 "uniform mat4 view;\n"
                                 "uniform mat4 projection;\n"
                                 "out vec3 Normal;\n"
                                 "out vec3 FragPos;\n"
                                 "void main() {\n"
                                 "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                 "    FragPos = vec3(view * model * vec4(position,1.0));\n"
                                 "    Normal = mat3(transpose(inverse(view * model))) * aNormal;\n"
                                 "}";

    const std::string fsShader = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "in vec3 Normal;\n"
                                 "in vec3 FragPos;\n"
                                 "uniform vec4 color;\n"
                                 "void main()\n"
                                 "{\n"
//                                 "    vec3 viewDir = normalize(-FragPos);\n"
                                 "    vec3 viewDir = vec3(0,0,1);\n"
                                 "    vec3 normal = normalize(Normal);\n"
                                 "    float diffuse = abs(dot(normal, viewDir));\n"
                                 "    vec4 color_ = 0.1*color+0.9*color*diffuse;\n"
                                 "    color_.w=1;\n"
//                                 "    color_.xyz =Normal;\n"
                                 "    FragColor = color_;   \n"
                                 "}";
    /**
     *           3              7
     *           |             |
     *           |             |
     * z         |y           | 6
     * | 1       /2      5    /
     * |       /         |   /
     * |     /           |  /
     * |   /             | /
     * | /              | /
     * ----------------- x
     * 0               4
     *
     */
    unsigned int indices[] = {0,1,3,0,3,2, //left
                              1,5,7,1,7,3, //top
                              5,4,6,5,6,7, //right
                              4,0,2,4,2,6, //down
                              2,3,7,2,7,6, //front
                              5,1,0,5,0,4}; // back
    const float size = 1.f;
    float vertices[] = {-0.5f * size, -0.5f * size, -0.5f * size,
                        -0.5f * size, -0.5f * size, 0.5f * size,
                        -0.5f * size, 0.5f * size, -0.5f * size,
                        -0.5f * size, 0.5f * size, 0.5f * size,
                        0.5f * size, -0.5f * size, -0.5f * size,
                        0.5f * size, -0.5f * size, 0.5f * size,
                        0.5f * size, 0.5f * size, -0.5f * size,
                        0.5f * size, 0.5f * size, 0.5f * size,
    };
//    float vertices[] = {-0.5f * size, -0.5f * size, -0.5f * size, -1,-1,-1,
//                        -0.5f * size, -0.5f * size, 0.5f * size, -1,-1,1,
//                        -0.5f * size, 0.5f * size, -0.5f * size, -1,1,-1,
//                        -0.5f * size, 0.5f * size, 0.5f * size, -1,1,1,
//                        0.5f * size, -0.5f * size, -0.5f * size, 1,-1,-1,
//                        0.5f * size, -0.5f * size, 0.5f * size, 1,-1,1,
//                        0.5f * size, 0.5f * size, -0.5f * size, 1,1,-1,
//                        0.5f * size, 0.5f * size, 0.5f * size, 1,1,1
//    };

    float normals[] = {
            -1,0,0, // left
            0,0,1,//top
            1,0,0,//right
            0,0,-1,//down
            0,1,0,//front
            0,-1,0//back
    };

    std::vector<float> data;
    int idx_normal = 0;
    for (size_t i=0;i<36;++i) {
        int idx = indices[i];
        if ( (i) % 6 == 0 && i>0 ) idx_normal+=1;
        for (size_t j=0;j<3;++j) {
            data.push_back( vertices[idx*3+j] );
        }
        for (size_t j=0;j<3;++j) {
            data.push_back(normals[idx_normal * 3 + j]);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),  (GLvoid*) (3 * sizeof(GLfloat)));
    glBindVertexArray(0);


    // Init shader
    mShader = std::make_unique<glUtil::Shader>(vsShader,fsShader);
    mShader->use();
    mShader->set("color", color);
    mShader->set("model", glm::mat4(1.f));
    bInited=true;
}

void BoxDrawer::SetModel(const Eigen::Matrix4f &model) {
    mShader->use();
    mShader->set("model",model);
}

BoxDrawer::BoxDrawer(): mMode(Triangle) {

}

void BoxDrawer::Draw(
        const Eigen::Matrix4f &projection,
        const Eigen::Matrix4f &viewMatrix) {
    assert(bInited);
    mShader->use();
    mShader->set("color", color);
    mShader->set("view",viewMatrix);
    mShader->set("projection",projection);
    glBindVertexArray(VAO);
    glLineWidth(3);
    switch(mMode){
        case Line:
            glDrawArrays(GL_LINES,0, 36);
//            glDrawElements(GL_LINES, 36, GL_UNSIGNED_INT, 0);
            break;
        case Triangle:
            glDrawArrays(GL_TRIANGLES,0, 36);
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            break;
    }
    glLineWidth(1);
}

void BoxDrawer::SetMode(Mode mode) {
    mMode = mode;
}