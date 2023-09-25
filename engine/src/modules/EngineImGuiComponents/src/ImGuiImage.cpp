#include <opencv2/opencv.hpp>
#include "EngineImGuiComponents/PreInclude.hpp"
#include "EngineImGuiComponents/ImGuiImage.hpp"

#define HERE() std::cout << "Line: " << __LINE__ << std::endl << "File: " << __FILE__ << std::endl
#define ERROR() CheckError(__FILE__, __LINE__)

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
    ImGuiImage::ImGuiImage()
        : haveImage_(false)
    {

    }

    ImGuiImage::~ImGuiImage()
    {
        glDeleteTextures(1, &rendererId_);
    }

    void ImGuiImage::Init(int width, int height)
    {
        width_ = width;
        height_ = height;
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, height, width, 
                0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        ERROR();
    }

    void ImGuiImage::SetImage(cv::Mat& image)
    {
        if (!image.empty())
        {
            cv::Mat disImage;
            cv::resize(image, disImage, cv::Size(width_, height_));

            glBindTexture(GL_TEXTURE_2D, rendererId_);

            ERROR();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  width_, height_, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, disImage.ptr());
            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  image.cols, image.rows, 
            //         0, GL_RGB, GL_UNSIGNED_BYTE, image.ptr());
            // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,  image.cols, image.rows, 
            //         GL_RGB, GL_UNSIGNED_BYTE, image.ptr());

            ERROR();

            haveImage_ = true;
        }
    }

    void ImGuiImage::OnUpdate(ImGuiImageOptions opts)
    {
        if (haveImage_)
        {
            ImGui::Image(reinterpret_cast<void*>(rendererId_), ImVec2(opts.width, opts.height));
        }
    }
} // namespace ntt
