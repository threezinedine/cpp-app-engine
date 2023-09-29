#include "EngineThreading/PreInclude.hpp"
#include "EngineThreading/Thread.hpp"
#include <imgui.h>


#include <glfw/glfw3.h>
#define HERE() std::cout << "Here" << std::endl;
#define IS_RUNNING() std::cout << ( IsRunning() ? "running" : "no" ) << std::endl;
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
    Thread::Thread(const char* name)
        : name_(name)
    {

    }

    void Thread::Start()
    {
        SetRunning(true);

        StartImpl();
        thread_ = std::make_unique<std::thread>(&Thread::MainLoop, this);
    }

    void Thread::Stop()
    {
        SetRunning(false);
        StopImpl();
        thread_->join();
    }

    void Thread::OnRun()
    {
        OnRunImpl();
    }

    void Thread::OnUpdate(Timestep ts, bool testing)
    {
        if (!testing)
        {
            ImGui::Begin(GetName());
        }

        OnUpdateImpl(ts);

        if (!testing)
        {
            ImGui::End();
        }
    }

    long long Thread::MainLoop()
    {
        // ntt::Time time("Thread main loop");
        long long result = 0;

        while (IsRunning())
        {
            OnRun();
            result ++;
        }

        return result;
    }

    bool Thread::IsRunning() const 
    { 
        return isRunning_; 
    }

    void Thread::SetRunning(bool running)
    {
        isRunning_ = running;
    }
} // namespace ntt
