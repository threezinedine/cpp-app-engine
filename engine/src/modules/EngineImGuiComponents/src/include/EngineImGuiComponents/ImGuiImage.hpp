#pragma once
#include "EngineCores/EngineCores.hpp"


namespace cv
{
    class Mat; 
} // namespace cv



namespace ntt
{
    struct ImGuiImageOptions
    {
        int width = 300;
        int height = 100;
    };

    class ImGuiImage
    {
        public:
            ImGuiImage();
            ~ImGuiImage();

            void Init(int width = 300, int height = 200);

            void SetImage(cv::Mat& image);
            void OnUpdate(ImGuiImageOptions opts = ImGuiImageOptions());

            static Scope<ImGuiImage> CreateScope()
            {
                return std::make_unique<ImGuiImage>();
            }

        private:
            unsigned int rendererId_;
            unsigned int width_;
            unsigned int height_;
            bool haveImage_ = false;
    };
} // namespace ntt
