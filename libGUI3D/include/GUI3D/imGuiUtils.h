//
// Created by sc on 8/5/21.
//

#ifndef DFG_MULTICON_VISION_IMGUIUTILS_H
#define DFG_MULTICON_VISION_IMGUIUTILS_H
#include <imgui.h>
#include <vector>
#include <string>
namespace SC {
    static bool AddSelectionnMenu(const char **options, int size, int &type, const std::string &name){
        if(type >= size) type = size-1;
        int pre_type = type;
        ImGui::Text("%s", name.c_str());
        ImGui::SameLine();

        if (ImGui::Button(options[type]))
            ImGui::OpenPopup((name+"_popup").c_str());
        ImGui::SameLine();
        if (ImGui::BeginPopup((name+"_popup").c_str())) {
            for (int i = 0; i < size; i++)
                if (ImGui::Selectable(options[i])) type = i;
            ImGui::EndPopup();
        }
        return type != pre_type;
    }

}

#endif //DFG_MULTICON_VISION_IMGUIUTILS_H
