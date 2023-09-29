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

    class Image;

    class ImGuiImage
    {
        public:
            ImGuiImage(Ref<Image> image);
            ~ImGuiImage();

            void Init();

            void SetImage(cv::Mat& image);
            void OnUpdate(ImGuiImageOptions opts = ImGuiImageOptions());
            void SetSize(int width, int height);

            static Scope<ImGuiImage> CreateScope(Ref<Image> image)
            {
                return std::make_unique<ImGuiImage>(image);
            }

        private:
            unsigned int rendererId_;
            unsigned int width_ = -1;
            unsigned int height_ = -1;
            bool haveImage_ = false;
            Ref<Image> image_;
    };
} // namespace ntt
