#include "PreInclude.hpp"
#include "EngineDataType/Image.hpp"
#include <opencv2/opencv.hpp>


TEST_F(EngineDataTypeTest, ImageWithInitialization)
{
    ntt::Image img("Image");

    EXPECT_THAT(img.GetName(), "Image");
}

TEST_F(EngineDataTypeTest, RunOnUpdateWithoutException)
{
    ntt::Timestep ts;
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, ImageFromFileName)
{
    std::string imagePath = "./image-path.png";
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.FromFile(imagePath));
}

TEST_F(EngineDataTypeTest, ImageSetValue)
{
    cv::Mat mat;
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.SetValue(mat));
}