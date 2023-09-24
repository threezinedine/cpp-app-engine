#pragma once
#include <string>
#include "DataTypeBase.hpp"
#include "InputType.hpp"


namespace cv
{
    class Mat;
};


namespace ntt
{
    class Image: public DataTypeBase
    {
        public:
            Image(const char* name);
            ~Image();

            void OnUpdate(Timestep ts, InputType type = NONE, void* args = nullptr) override;
            std::string ToString() const override;

            void SetValue(cv::Mat& value);
    };
} // namespace ntt
