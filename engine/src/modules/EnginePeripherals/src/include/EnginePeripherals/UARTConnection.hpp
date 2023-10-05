#pragma once
#include <string>
#include <windows.h>
#include <vector>
#include "EngineDataType/EngineDataType.hpp"
#include "EngineImGuiComponents/EngineImGuiComponents.hpp"


namespace ntt
{ 
    class Timestep;
    class DataStorage;

    enum SerialFrameResultStatus
    {
        SERIAL_RESULT_NONE,
        SERIAL_RESULT_OK,
        SERIAL_RESULT_RESPONSE_ERROR,
        SERIAL_RESULT_FAIL_TO_SETTING,
        SERIAL_RESULT_FAIL_TO_CONNECT,
        SERIAL_RESULT_FAIL_TO_SEND_DATA,
        SERIAL_RESULT_FAIL_TO_RECEIVE_DATA,
    };

    struct SerialFrameResult
    {
        SerialFrameResultStatus status;
        uint8_t errorCode;
    };

    class UARTConnection
    {
        public:
            UARTConnection(const std::string& name, const char* comPort = "COM7", int baudrate = 115200);
            virtual ~UARTConnection();

            bool IsConnected();
            SerialFrameResult Connect();
            void Disconnect();

            std::vector<uint8_t> SendRequets(std::vector<uint8_t> request, bool needRes = false);

            void OnUpdate(Timestep ts);
            const std::string& GetName() const { return name_; }

        private:
            std::string name_;
            // std::string comPort_;
            HANDLE hCom_;
            DCB serialParam_ = { 0 };
            COMMTIMEOUTS timeOut_ = { 0 };
            DWORD bytesRead;
            unsigned char buffer_[100];

            Ref<DataStorage> storage_; 
            Scope<Data<int>> baudrate_;
            Scope<String<5>> comPort_;
            Scope<ImGuiSelectableVector<std::string>> selectableVectorCom_;
            Scope<ImGuiSelectableVector<int>> selectableVectorBaudrate_;

            Ref<Bool> isConnected_;
    };
} // namespace ntt
