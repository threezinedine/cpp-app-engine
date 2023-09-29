#include "EngineDataType/DataStorage.hpp"
#include "Storage.hpp"

#include <iostream>
#define HERE() std::cout << "Line: " << __LINE__ << " - File: " << __FILE__ << std::endl;


namespace ntt
{
    DataStorage::DataStorage()
        : storage_(nullptr)
    {

    }

    DataStorage::DataStorage(std::string fileName)
    {
        Ref<IFileSystem> file = std::make_shared<RealFileSystem>(fileName);
        storage_ = std::make_shared<Storage>(file);
    }

    DataStorage::DataStorage(const char* fileName)
        : DataStorage(std::string(fileName))
    {

    }

    DataStorage::~DataStorage()
    {
        if (storage_ != nullptr)
        {
            storage_->Save();
        }
    }

    void DataStorage::SaveValue(const char* name, int value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<int>(name, value);
        }
    }

    void DataStorage::SaveValue(const char* name, float value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<float>(name, value);
        }
    }

    void DataStorage::SaveValue(const char* name, bool value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<bool>(name, value);
        }
    }

    void DataStorage::SaveValue(const char* name, std::string value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<std::string>(name, value);
        }
    }

    int DataStorage::GetValue(const char* name, int defaultValue)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<int>(name, defaultValue);
        }
        else 
        {
            return defaultValue;
        }
    }

    float DataStorage::GetValue(const char* name, float defaultValue)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<float>(name, defaultValue);
        }
        else 
        {
            return defaultValue;
        }
    }

    bool DataStorage::GetValue(const char* name)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<bool>(name, false);
        }
        else 
        {
            return false;
        }
    }

    std::string DataStorage::GetValue(const char* name, std::string defaultValue)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<std::string>(name, defaultValue);
        }
        else 
        {
            return defaultValue;
        }
    }

    void DataStorage::SaveValues(const char* name, std::vector<int> value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<std::vector<int>>(name, value);
            storage_->Save();
        }
    }

    void DataStorage::SaveValues(const char* name, std::vector<float> value)
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<std::vector<float>>(name, value);
            storage_->Save();
        }
    }

    std::vector<int> DataStorage::GetValues(const char* name, std::vector<int> defaultValue)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<std::vector<int>>(name, defaultValue);
        }
        else 
        {
            return defaultValue;
        }
    }

    std::vector<float> DataStorage::GetValues(const char* name, std::vector<float> defaultValue)
    {
        if (storage_ != nullptr)
        {
            return storage_->GetValue<std::vector<float>>(name, defaultValue);
        }
        else 
        {
            return defaultValue;
        }
    }
} // namespace ntt
