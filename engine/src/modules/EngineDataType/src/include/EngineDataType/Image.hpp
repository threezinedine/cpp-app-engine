#pragma once
#include <string>
#include "DataTypeBase.hpp"
#include "InputType.hpp"
#include "EngineImGuiComponents/ImGuiImage.hpp"
#include "EngineCores/EngineCores.hpp"


namespace cv
{
    class Mat;
};


namespace ntt
{
    struct ImageOptions
    {
        ImGuiImageOptions imgOptions;
    };

    class Image: public DataTypeBase
    {
        public:
            Image(const char* name, int width = 200, int height = 150);
            Image(const char* name, std::string filePath);
            ~Image();

            void Init();
            bool OnUpdate(Timestep ts, InputType type = NONE, void* args = nullptr) override;
            std::string ToString() const override;

            void SetValue(cv::Mat& value);

            bool FromFile(std::string filePath);

        private:
            Scope<ImGuiImage> imguiImage_;
            int width_;
            int height_;
            std::string filePath_;
    };
} // namespace ntt
