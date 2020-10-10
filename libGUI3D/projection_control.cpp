#include "projection_control.hpp"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace SC;

ProjectionControl::ProjectionControl(unsigned int windowWidth, unsigned int windowHeight)
:
fovy(45.0f),
bShowUI(false),
near(0.001f),
far(50.0f),
width_(windowWidth),height_(windowHeight),
projection_mode(0),
width(10.0f)
{}

ProjectionControl::~ProjectionControl() = default;

glm::mat4 ProjectionControl::projection_matrix() const {
    double aspect_ratio = float(width_)/float(height_);
    glm::mat4 proj;
    if(projection_mode == 0) {
        proj = glm::perspective<float>(glm::radians(fovy),
                                       (float) width_ /
                                       (float) height_, near, far);
    } else {
        proj = glm::ortho<float>(-width/2.f,width/2.f,-width/2.f/aspect_ratio, width/2.f/aspect_ratio, near,far);
    }
    return proj;
//  return Eigen::Map<Eigen::Matrix4f>(glm::value_ptr(proj));
}

void ProjectionControl::show() {
    bShowUI = true;
}

void ProjectionControl::draw_ui() {
  if(!bShowUI) {
    return;
  }

  ImGui::Begin("projection control", &bShowUI, ImGuiWindowFlags_AlwaysAutoResize);
  const char* modes[] = { "PERSPECTIVE", "ORTHOGONAL" };
  ImGui::Combo("Mode", &projection_mode, modes, IM_ARRAYSIZE(modes));
  if(projection_mode == 0){
    ImGui::DragFloat("FOV", &fovy, 0.1f, 1.0f, 180.0f);
  } else {
    ImGui::DragFloat("Width", &width, 0.1f, 1.0f, 1000.0f);
  }

  ImGui::DragFloat("Near", &near, 1.0f, 0.1f, far);
  ImGui::DragFloat("Far", &far, 1.0f, near, 10000.0f);

  ImGui::End();
}