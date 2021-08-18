//
// Created by sc on 8/9/21.
//

#include <GUI3D/meshDrawer.h>
using namespace glUtil;

std::string vsShader = "#version 330 core\n"
                       "layout (location = 0) in vec3 aPos;\n"
                       "layout (location = 1) in vec3 aNormal;"
                       "layout (location = 2) in vec3 aColor;"
                       "out vec3 FragPos;\n"
                       "out vec3 Normal;\n"
                       "out vec3 Color;\n"
                       "uniform mat4 model;\n"
                       "uniform mat4 view;\n"
                       "uniform mat4 projection;\n"
                       "uniform vec3 lightPos;\n"
                       "void main()\n"
                       "{\n"
                       "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
                       "    Normal = mat3(view) * aNormal;\n"
                       "    Color = aColor;\n"
                       "    gl_Position = projection * view * vec4(FragPos, 1.0);\n"
                       "}\n";
std::string fsShader= "#version 330 core\n"
                      "out vec4 FragColor;\n"
                      "in vec3 Normal;\n"
                      "in vec3 Color;\n"
                      "in vec3 FragPos;\n"
                      "uniform float diffuse_strength;\n"
                      "void main()\n"
                      "{\n"
                      "    vec3 up_axis = vec3(0.0, 0.0, 1);\n"
                      "    vec3 norm = normalize(Normal);\n"
                      "    float diffuse = abs(dot(norm, up_axis));\n"
                      "    FragColor.xyz = Color*(1-diffuse_strength) + Color*diffuse_strength*diffuse;\n"
                      "    FragColor.w=1;"
                      "} ";


MeshDrawer::MeshDrawer() :mPointBufferSize(1e3),mIndicesBufferSize(1e3) {

}

void MeshDrawer::Init() {
    /*init shader*/
    mShader = std::make_unique<glUtil::Shader>(vsShader,fsShader);
    mShader->use();
    Eigen::Matrix4f modelmat = Eigen::Matrix4f::Identity();
    mShader->set("model",modelmat);
    mShader->set("diffuse_strength",mDiffuseStrength);
    /*init buffer*/
    updateIndicesBuffer(mIndicesBufferSize);
    updateVertexBuffer(mPointBufferSize);
}

void MeshDrawer::Update(std::vector<Eigen::Vector3f> *points, std::vector<Eigen::Vector3f> *colors,
                        std::vector<Eigen::Vector3f> *normals, std::vector<Eigen::Vector3<unsigned int>> *indices) {
    mTotalPoints = points->size();
    mTotalIndices = indices->size() * 3;

    /*check update buffer*/
    updateVertexBuffer(mTotalPoints);
    updateIndicesBuffer(mTotalIndices);

    /*bind buffer objects*/
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /*copy vetex data*/
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    mTotalPoints * 3 * sizeof(GLfloat), points->data());
    glBufferSubData(GL_ARRAY_BUFFER, mPointBufferSize * 3 * sizeof(GLfloat),
                    mTotalPoints * 3 * sizeof(GLfloat), normals->data());
    glBufferSubData(GL_ARRAY_BUFFER, mPointBufferSize * 6 * sizeof(GLfloat),
                    mTotalPoints * 3 * sizeof(GLfloat), colors->data());

    /*copy indice data*/
    if(mTotalIndices){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
                        mTotalIndices * sizeof(unsigned int), indices->data());
    }

    /*back to default*/
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshDrawer::Draw(const Eigen::Matrix4f &projection, const Eigen::Matrix4f &viewMatrix) {
    mShader->use();
    mShader->set("projection", projection);
    mShader->set("view", viewMatrix);
    mShader->set("diffuse_strength",mDiffuseStrength);
    // draw mesh
    glBindVertexArray(VAO);
    if(mTotalIndices)
        glDrawElements(GL_TRIANGLES, mTotalIndices, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, mTotalPoints);

    // always good practice to set everything back to defaults once configured.
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void MeshDrawer::updateIndicesBuffer(size_t newSize, bool force) {
    if(mIndicesBufferSize > newSize && !force) return;

    /*delete old one if exist*/
    if(mIndicesBufferSize > 0) glDeleteBuffers(1, &EBO);
    mIndicesBufferSize = (std::floor(newSize / 1e6) + 1) * 1e6;

    /*generate buffer*/
    glGenBuffers(1, &EBO);
    /*bind*/
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    /*allocate*/
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  mIndicesBufferSize * sizeof(unsigned int ), nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    /*back to default*/
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshDrawer::updateVertexBuffer(size_t newSize, bool force) {
    if (mPointBufferSize > newSize && !force) return;
    if(mPointBufferSize > 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    /*set new size*/
    mPointBufferSize = (std::floor(newSize / 1e6) + 1) * 1e6;

    uint numStride = 9;
    size_t totalSize = mPointBufferSize * numStride;
    /*generate buffer*/
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    /*bind*/
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*allocate*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * totalSize, nullptr, GL_DYNAMIC_DRAW);
    /*allocate each field*/
    /*point*/
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    /*normal*/
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (void *) (mPointBufferSize * 3 * sizeof(GLfloat)));
    /*color*/
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (void *) (mPointBufferSize * 6 * sizeof(GLfloat)));
    /*bind to default buffer*/
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshDrawer::Reset() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
