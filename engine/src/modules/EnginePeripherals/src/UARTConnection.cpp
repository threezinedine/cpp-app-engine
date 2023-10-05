#include "EnginePeripherals/PreInclude.hpp"
#include "EnginePeripherals/UARTConnection.hpp"
#include "EngineThreading/EngineThreading.hpp"
#include "EngineDataType/EngineDataType.hpp"


namespace ntt
{
    UARTConnection::UARTConnection(const std::string& name, const char* comPort, int baudrate)
        : name_(name)
    {
        isConnected_ = std::make_shared<ntt::Bool>("Is Connected", false);

        storage_ = ntt::DataStorage::CreateRef("./uart-connection.json");
        baudrate_ = std::make_unique<ntt::Data<int>>("Baud rate", baudrate, 0, 1000000, storage_);
        comPort_ = std::make_unique<ntt::String<5>>("COM Port", comPort, storage_);

        selectableVectorBaudrate_ = std::make_unique<ntt::ImGuiSelectableVector<int>>(
            std::vector<std::pair<std::string, int>>
            {
                { std::string("115200"), 115200 },
                { std::string("9600"), 9600 },
            },
            [this]() -> int
            {
                return baudrate_->Value();
            },
            [this](int value)
            {
                baudrate_->SetValue(value);
            }
        );

        selectableVectorCom_ = std::make_unique<ntt::ImGuiSelectableVector<std::string>>(
            std::vector<std::pair<std::string, std::string>>
            {
                { std::string("COM13"), std::string("COM13") },
                { std::string("COM12"), std::string("COM12") },
                { std::string("COM11"), std::string("COM11") },
                { std::string("COM10"), std::string("COM10") },
                { std::string("COM9"), std::string("COM9") },
                { std::string("COM8"), std::string("COM8") },
                { std::string("COM7"), std::string("COM7") },
                { std::string("COM6"), std::string("COM6") },
                { std::string("COM5"), std::string("COM5") },
            },
            [this]() -> std::string 
            {
                return comPort_->Value();
            },
            [this](std::string value)
            {
                comPort_->SetValue(value);
            }
        );

    }


    UARTConnection::~UARTConnection()
    {
        if (isConnected_->Value())
        {
            Disconnect();
        }
    }

    bool UARTConnection::IsConnected()
    {
        ntt::Lock lock(isConnected_);
        return isConnected_->Value();
    }

    SerialFrameResult UARTConnection::Connect()
    {
        hCom_ = CreateFile(comPort_->Value().c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hCom_ == INVALID_HANDLE_VALUE) {
            return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
        }

        serialParam_.DCBlength = sizeof(serialParam_);
        if (!GetCommState(hCom_, &serialParam_)) {
            CloseHandle(hCom_);
            return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
        }

        serialParam_.BaudRate = baudrate_->Value();   // Baud rate
        serialParam_.ByteSize = 8;           // Data bits
        serialParam_.StopBits = ONESTOPBIT;  // Stop bits
        serialParam_.Parity = NOPARITY;      // Parity

        timeOut_.ReadIntervalTimeout = 50;
        timeOut_.ReadTotalTimeoutConstant = 50;
        timeOut_.ReadTotalTimeoutMultiplier = 10;
        timeOut_.WriteTotalTimeoutConstant = 50;
        timeOut_.WriteTotalTimeoutMultiplier = 10;
        SetCommTimeouts(hCom_, &timeOut_);
        if (!SetCommTimeouts(hCom_, &timeOut_)) {
            DWORD errorCode = GetLastError();
            switch (errorCode) {
                case ERROR_ACCESS_DENIED:
                    std::cout << "Access denied. Make sure the port is not already open." << std::endl;
                    break;
                case ERROR_FILE_NOT_FOUND:
                    std::cout << "Port not found. Check the port name." << std::endl;
                    break;
                default:
                    std::cout << "Failed to set UART timeouts. Error code: " << errorCode << std::endl;
                    break;
            }
            CloseHandle(hCom_);
            return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
        }

        ntt::Lock lock(isConnected_);
        isConnected_->SetValue(false);
        return { SERIAL_RESULT_OK, 0 };
    }

    void UARTConnection::Disconnect()
    {
        ntt::Lock lock(isConnected_);
        CloseHandle(hCom_);
        isConnected_->SetValue(false);
    }


    std::vector<uint8_t> UARTConnection::SendRequets(std::vector<uint8_t> request, bool needRes)
    {
        uint8_t* sendData = new uint8_t[request.size()];
        DWORD bytesWritten;

        for (int i=0; i<request.size(); i++)
        {
            sendData[i] = request[i];
            std::cout << "0x" << std::setw(2) << std::setfill('0') 
                    << std::hex << static_cast<unsigned int>(request[i]) << " ";
        }
        std::cout << std::endl;

        if (!WriteFile(hCom_, sendData, sendData[2], &bytesWritten, NULL)) {
            std::cout << "Cannot Send Data" << std::endl;
            Disconnect();
            return {  };
        }

        delete sendData;
        if (needRes)
        {
            std::vector<uint8_t> response;
            PurgeComm(hCom_, PURGE_RXCLEAR);

            if (!ReadFile(hCom_, buffer_, sizeof(buffer_), &bytesRead, NULL)) {
                std::cerr << "Failed to read response" << std::endl;
                Disconnect();
                return {  };
            }

            std::cout << "Receive" << std::endl;
            for (int i=0; i<buffer_[2]; i++)
            {
                std::cout << " 0x";
                std::cout << std::hex << std::setw(2)
                    << std::setfill('0') << static_cast<unsigned int>(buffer_[i]);
                response.push_back(buffer_[i]);
            }
            std::cout << std::endl;

            return response;
        }

        return {  };
    }

    void UARTConnection::OnUpdate(ntt::Timestep ts) 
    {
        if (ImGui::TreeNode("UART Configuration"))
        {
            ImGui::Text("Select Com");
            selectableVectorCom_->OnUpdate();
            ImGui::Text("Select baudrate");
            selectableVectorBaudrate_->OnUpdate();
            ImGui::Separator();
            if (ImGui::Button("Connect"))
            {
                Connect();
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect"))
            {
                Disconnect();
            }
            ImGui::Separator();
            ImGui::TreePop();
        }
    }
} // namespace ntt
