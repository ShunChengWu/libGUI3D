//
//  glUtils.hpp
//  DFGGUI
//
//  Created by Shun-Cheng Wu on 01/Jan/2019.
//

#ifndef glUtils_hpp
#define glUtils_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glShader.hpp"
#include "glMesh.hpp"

namespace glUtil {
    class Utils {
    public:
        // faces should have 6 paths: right, left, front, back, top, bottom
        static unsigned int loadCubemap(const std::vector<std::string> &faces);
        uint loadTexture(char const * path);
        static void save_screen( const char *spath );
        
    };
    
    class ShapeVertices {
    public:
        static std::vector<Vertex> skybox;
        static std::vector<Vertex> cube;
        static std::vector<Vertex> plane;
        static std::vector<Vertex> quad;
    };
    
    
    

    class SkyBox : public Model_base {
    public:
        SkyBox(const std::vector<std::string> &faces):mesh(NULL), textureId(0)
        {
            textureId = Utils().loadCubemap(faces);
        }
        
        ~SkyBox(){
            glDeleteTextures(1, &textureId);
        }
        void init(){
            mesh = new Mesh(ShapeVertices().skybox);
            mesh->addTexture("skybox", textureId, GL_TEXTURE_CUBE_MAP);
        }
        
        void setViewProjection(const glm::mat4 &view, const glm::mat4 &projection){
            if(shader == NULL){
                shader = new Shader();
                shader->compileShader(vertexShader, fragmentShader);
                hasOwnership = true;
            }
            shader->use();
            shader->set("view", view);
            shader->set("projection", projection);
        }
        
        void Draw(){
            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
            mesh->setShader(shader);
            mesh->Draw();
            glDepthFunc(GL_LESS); // set depth function back to default
        }
        
        unsigned int getTextureId(){ return textureId; }
    private:
        Mesh *mesh;
        unsigned int textureId;

        const char *vertexShader ="#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec3 TexCoords;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main(){\n"
        "TexCoords = aPos;\n"
        "vec4 pos = projection * view * vec4(aPos, 1.0);\n"
        "gl_Position = pos.xyww;}\n\0";
        const char *fragmentShader = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 TexCoords;\n"
        "uniform samplerCube skybox1;\n"
        "void main(){\n"
            "FragColor = texture(skybox1, TexCoords);\n"
        "}\0";

    };

}

#endif /* glUtils_hpp */
