#include <iostream>
#include "CameraThread.hpp"
#include <opencv2/opencv.hpp>

#define HERE() std::cout << "Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl
#define ERROR() CheckError(__FILE__, __LINE__)

#define SCALE (4)
#include <glfw/glfw3.h>

static int count = 0;

static void CheckError(const char* file, int line)
{
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                std::cerr << "OpenGL Error (Enum) at " << file << ":" << line << ": GL_INVALID_ENUM" << std::endl;
                break;
            case GL_INVALID_VALUE:
                std::cerr << "OpenGL Error (Value) at " << file << ":" << line << ": GL_INVALID_VALUE" << std::endl;
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "OpenGL Error (Operation) at " << file << ":" << line << ": GL_INVALID_OPERATION" << std::endl;
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "OpenGL Error (Memory) at " << file << ":" << line << ": GL_OUT_OF_MEMORY" << std::endl;
                break;
            default:
                std::cerr << "OpenGL Error (Unknown) at " << file << ":" << line << ": Unknown error" << std::endl;
                break;
        }
    }
}


CameraThread::CameraThread()
    : ntt::Thread("Camera Thread")
{
    image_ = std::make_shared<ntt::Image>("Camera");
    imageDisplay_ = std::make_unique<ntt::ImGuiImage>(image_);
    storage_ = ntt::DataStorage::CreateRef("camera-thread.json");
    imageSize_ = std::make_unique<ntt::Array<int, 2>>(
                "Image Size", std::vector<int>{ 300, 250 }, 100, 1000, storage_);
}


CameraThread::~CameraThread()
{

}

void CameraThread::StartImpl()
{
    imageDisplay_->Init();
    cap_ = std::make_shared<cv::VideoCapture>(1);
    // cap_ = std::make_shared<cv::VideoCapture>("C:/Users/Acer/C_Language/C++/GameEngine/VisionProject/color-detect.mp4");

    if (!cap_->isOpened())
    {
        exit(-1);
    }

    trigger_.Reset();
    image_->Init();
}

void CameraThread::StopImpl()
{
    cap_->release();
    cv::destroyAllWindows();
}


void CameraThread::OnRunImpl()
{
    if (trigger_.IsTrigger(60))
    {
        ntt::Lock lock(image_);
        cv::Mat frame;

        *cap_ >> frame;

        if (!frame.empty())
        {
            image_->SetValue(frame);
        }
    }
}


void CameraThread::OnUpdateImpl(ntt::Timestep ts)
{
    ntt::Lock lock(image_);

    imageSize_->OnUpdate(ts, ntt::SLIDER);

    if (!image_->IsEmpty())
    {
        imageDisplay_->OnUpdate({ imageSize_->Value()[0], imageSize_->Value()[1] });
    }
    ERROR();
}
