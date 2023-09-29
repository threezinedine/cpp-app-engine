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
    ntt::Ref<ntt::Image> img = std::make_shared<ntt::Image>("Image");
    ntt::ImGuiImage imgDisplay(img);

    EXPECT_NO_THROW(imgDisplay.OnUpdate());
}

TEST_F(EngineDataTypeTest, ImageSetWidthAndHeight)
{
    ntt::Image img("Image");

    img.SetSize(400, 300);

    EXPECT_THAT(img.GetWidth(), testing::Eq(400));
    EXPECT_THAT(img.GetHeight(), testing::Eq(300));
}

TEST_F(EngineDataTypeTest, ImageFromFileName)
{
    std::string imagePath = "./image-path.png";
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.FromFile(imagePath));
}

TEST_F(EngineDataTypeTest, ImageIsEmptyIsTrueAtDefault)
{
    ntt::Image img("Image");
    EXPECT_THAT(img.IsEmpty(), testing::IsTrue());
}

TEST_F(EngineDataTypeTest, ImageSetValue)
{
    cv::Mat mat;
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.SetValue(mat));
    // EXPECT_THAT(img.IsEmpty(), testing::IsFalse());
}

TEST_F(EngineDataTypeTest, ImageHasChangeFunctionReturnFalseAtDefault)
{
    ntt::Image img("Image");

    EXPECT_THAT(img.HasChanged(), testing::IsFalse());
}

TEST_F(EngineDataTypeTest, ImageDataIsTheLockableVariable)
{
    cv::Mat mat;
    ntt::Image img("Image");

    EXPECT_NO_THROW(img.Lock());
    EXPECT_NO_THROW(img.UnLock());
}