#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Image.hpp"
#include <opencv2/opencv.hpp>

#define HERE() std::cout << "Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl


namespace ntt
{
    Image::Image(const char* name, int width, int height)
        : DataTypeBase(name), width_(width), height_(height)
    {
        imguiImage_ = std::make_unique<ImGuiImage>();
    } 

    Image::~Image()
    {

    }

    void Image::Init()
    {
        imguiImage_->Init(width_, height_);
    }

    bool Image::OnUpdate(Timestep ts, InputType type, void* args)
    {
        ImageOptions* options;
        if (args != nullptr)
        {
            options = static_cast<ImageOptions*>(args);
        }
        
        switch (type)
        {
            case IMAGE:
                if (args != nullptr)
                {
                    imguiImage_->OnUpdate(options->imgOptions);
                }
                else 
                {
                    imguiImage_->OnUpdate();
                }
                break;
            
            default:
                break;
        }
        return false;
    }

    std::string Image::ToString() const 
    {
        return GetName();
    }

    void Image::SetValue(cv::Mat& value)
    {
        imguiImage_->SetImage(value);
    }

    bool Image::FromFile(std::string filePath)
    {
        if (FileExists(filePath))
        {
            cv::Mat image = cv::imread(filePath);
            if (image.empty())
            {
                return false;
            }
            else 
            {
                cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

                SetValue(image);
                return true;
            }
        }

        return false;
    }
} // namespace ntt
