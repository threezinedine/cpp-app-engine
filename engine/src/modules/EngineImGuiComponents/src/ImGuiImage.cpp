#include <iostream>
#include <opencv2/opencv.hpp>
#include "EngineImGuiComponents/PreInclude.hpp"
#include "EngineImGuiComponents/ImGuiImage.hpp"

#define HERE() std::cout << "Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl
#define HERE_MSG(msg) std::cout << "Message: " << (msg) << " Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl
#define ERROR() CheckError(__FILE__, __LINE__)

#define SCALE (4)

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


namespace ntt
{
    ImGuiImage::ImGuiImage(Ref<Image> image)
        : haveImage_(false),
            width_(300), height_(200),
            image_(image)
    {

    }

    ImGuiImage::~ImGuiImage()
    {
        glDeleteTextures(1, &rendererId_);
    }

    void ImGuiImage::Init()
    {
        glGenTextures(1, &rendererId_);
        ERROR();
        glBindTexture(GL_TEXTURE_2D, rendererId_);
        ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        ERROR();
    }

    void ImGuiImage::SetImage(cv::Mat& image)
    {
        if (!image.empty())
        {
            GLenum internalFormat, format;

            cv::Mat displayImage;
            if (width_ == -1)
            {
                width_ = image.rows / SCALE;
                height_ = image.cols / SCALE;
            }
            cv::resize(image, displayImage, cv::Size(width_, height_));

            if (image.channels() == 3)
            {
                internalFormat = GL_RGB8;
                format = GL_RGB;
            }
            else 
            {
                internalFormat = GL_RGBA8;
                format = GL_RGBA;
            }
            
            glBindTexture(GL_TEXTURE_2D, rendererId_);
            ERROR();

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,  width_, height_, 
                    0, format, GL_UNSIGNED_BYTE, displayImage.ptr());

            ERROR();

            haveImage_ = true;
        }
    }

    void ImGuiImage::OnUpdate(ImGuiImageOptions opts)
    {
        if (!image_->IsEmpty())
        {
            SetImage(image_->Value());
            ImGui::Image(reinterpret_cast<void*>(rendererId_), ImVec2(opts.width, opts.height));
        }
    }

    void ImGuiImage::SetSize(int width, int height)
    {
        width_ = width;
        height_ = height;
    }
} // namespace ntt
