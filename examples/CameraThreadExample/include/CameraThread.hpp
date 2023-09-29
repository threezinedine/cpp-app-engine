#pragma once
#include "AppEngine/AppEngine.hpp"


namespace cv
{
    class Mat; 
    class VideoCapture;
} // namespace cv



class CameraThread: public ntt::Thread
{
    public:
        CameraThread();
        ~CameraThread();

        void StartImpl() override;
        void StopImpl() override;

        void OnRunImpl() override;
        
        void OnUpdateImpl(ntt::Timestep ts) override;

        static ntt::Ref<CameraThread> CreateRef()
        {
            return std::make_shared<CameraThread>();
        }

    private:
        ntt::Ref<ntt::Image> image_;
        ntt::Ref<cv::VideoCapture> cap_;
        ntt::TimeTrigger trigger_;
        ntt::TimeTrigger triggerMainThread_;
        ntt::Scope<ntt::ImGuiImage> imageDisplay_;
        bool haveImage_ = true;
};
