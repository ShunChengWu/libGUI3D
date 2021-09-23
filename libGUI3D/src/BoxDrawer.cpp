//
// Created by sc on 8/23/20.
//

#include <GUI3D/BoxDrawer.h>

using namespace glUtil;

BoxDrawer::~BoxDrawer(){
    if(bInited) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}

void BoxDrawer::Init() {
    const std::string vsShader = "#version 330\n"
                                 "layout(location = 0) in vec3 position;\n"
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

    unsigned int indices[] = {0,1,3,0,3,2,
                              1,5,7,1,7,3,
                              5,4,6,5,6,7,
                              4,0,2,4,2,6,
                              2,3,7,2,7,6,
                              5,1,0,5,0,4};
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
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    // Lines
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
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
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glLineWidth(1);
}