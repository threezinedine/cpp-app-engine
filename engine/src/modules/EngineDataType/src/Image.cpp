#include "EngineDataType/PreInclude.hpp"
#include "EngineDataType/Image.hpp"
#include <opencv2/opencv.hpp>


namespace ntt
{
    Image::Image(const char* name)
        : DataTypeBase(name)
    {

    } 

    Image::~Image()
    {

    }

    void Image::OnUpdate(Timestep ts, InputType type, void* args)
    {

    }

    std::string Image::ToString() const 
    {
        return GetName();
    }

    void Image::SetValue(cv::Mat& value)
    {

    }
} // namespace ntt
