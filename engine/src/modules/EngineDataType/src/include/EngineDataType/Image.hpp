#pragma once
#include <string>
#include <mutex>
#include "DataTypeBase.hpp"
#include "InputType.hpp"
#include "EngineImGuiComponents/ImGuiImage.hpp"
#include "EngineCores/EngineCores.hpp"
#include "LockableVarible.hpp"
#include <opencv2/opencv.hpp>


// namespace cv
// {
//     class Mat;
// };


namespace ntt
{
    struct ImageOptions
    {
        ImGuiImageOptions imgOptions;
    };

    class Image: public DataTypeBase, public LockableVariable
    {
        public:
            Image(const char* name, int width = 200, int height = 150);
            Image(const char* name, std::string filePath);
            ~Image();

            void Init();
            bool OnUpdate(Timestep ts, InputType type = NONE, void* args = nullptr) override;
            std::string ToString() const override;

            inline cv::Mat& Value() { return value_; }

            void SetValue(cv::Mat& value);

            bool FromFile(std::string filePath);

            inline void Lock() { mutex_.lock(); }
            inline void UnLock() { mutex_.unlock(); }

            void SetSize(int width, int heigth);
            inline int GetWidth() const { return width_; }
            inline int GetHeight() const { return height_; }

            inline bool IsEmpty() { return value_.empty(); }
            inline bool HasChanged() { return hasChanged_; }

        private:
            // Scope<ImGuiImage> imguiImage_;
            int width_;
            int height_;
            std::string filePath_;
            std::mutex mutex_;
            cv::Mat value_;
            bool hasChanged_ = false;
    };
} // namespace ntt
