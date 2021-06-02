//
// Created by sc on 1/24/21.
//

#ifndef GUI3D_IMGUI_IMGUIIMGRENDER_H
#define GUI3D_IMGUI_IMGUIIMGRENDER_H
#include <opencv2/core.hpp>
#include "glImageRenderer.h"
#include "ImageDrawer.h"
#include <memory>

namespace ImGui{
    class ImGUI_ImageRenderWrapper_static {
    public:
        static void ShowImage(int width, int height, const glUtil::ImageDrawer* imageDrawer ){
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 pos = ImGui::GetCursorScreenPos();
            auto tex_id = reinterpret_cast<ImTextureID>(imageDrawer->GetTextureID());
            ImGui::Image(tex_id, ImVec2(width,height),
                         ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                float region_sz = 32.0f;
                float region_x = io.MousePos.x - pos.x - region_sz * 0.5f; if (region_x < 0.0f) region_x = 0.0f; else if (region_x > width - region_sz) region_x = width - region_sz;
                float region_y = io.MousePos.y - pos.y - region_sz * 0.5f; if (region_y < 0.0f) region_y = 0.0f; else if (region_y > height - region_sz) region_y = height - region_sz;
                float zoom = 4.0f;
                ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
                ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
                float factor_x = float(width);// / float(textureBuffer_->noDims.x) * textureBuffer_->noDims.x;
                float factor_y = float(height);// / float(textureBuffer_->noDims.y) *textureBuffer_->noDims.y;
                ImVec2 uv0 = ImVec2((region_x) / factor_x, (region_y) / factor_y);
                ImVec2 uv1 = ImVec2((region_x + region_sz) / factor_x, (region_y + region_sz) / factor_y);
                ImGui::Image(tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
                ImGui::EndTooltip();
            }
        }
    private:
    };
}

#endif //DFG_MULTICON_VISION_IMGUIIMGRENDER_H
