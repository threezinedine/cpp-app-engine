#pragma once
#include <vector>
#include <functional>


namespace ntt
{
    template <typename T>
    class ImGuiSelectableVector
    {
        public:
            ImGuiSelectableVector(std::vector<std::pair<std::string, T>> vect,
                    std::function<T()>getter, std::function<void(T)> setter)
                : vect_(vect), getter_(getter), setter_(setter)
            {

            }

            ~ImGuiSelectableVector()
            {

            }

            void OnUpdate()
            {
                for (auto element: vect_)
                {
                    if (ImGui::Selectable(element.first.c_str(), getter_() == element.second))
                    {
                        setter_(element.second);
                    }
                }
            }

        private:
            std::vector<std::pair<std::string, T>> vect_;
            std::function<T()> getter_;
            std::function<void(T)> setter_;
    }; 
} // namespace ntt
