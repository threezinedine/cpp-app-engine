#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "EngineCores/EngineCores.hpp"


namespace ntt
{
    class Storage;

    class DataStorage
    {
        public:
            DataStorage();
            DataStorage(const char* file);
            DataStorage(std::string file);
            ~DataStorage();

            virtual void SaveValue(const char* name, int value);
            virtual void SaveValue(const char* name, float value);
            virtual void SaveValue(const char* name, bool value);
            virtual void SaveValue(const char* name, std::string value);

            virtual int GetValue(const char* name, int defaultValue);
            virtual float GetValue(const char* name, float defaultValue);
            virtual bool GetValue(const char* name);
            virtual std::string GetValue(const char* name, std::string defaultValue);

            virtual void SaveValues(const char* name, std::vector<int> value);
            virtual void SaveValues(const char* name, std::vector<float> value);

            virtual std::vector<int> GetValues(const char* name, std::vector<int> defaultValue);
            virtual std::vector<float> GetValues(const char* name, std::vector<float> defaultValue);

            static Scope<DataStorage> CreateScope(const char* fileName)
            {
                return std::make_unique<DataStorage>(fileName);
            }

            static Scope<DataStorage> CreateScope(std::string fileName)
            {
                return std::make_unique<DataStorage>(fileName);
            }

            static Ref<DataStorage> CreateRef(const char* fileName)
            {
                return std::make_shared<DataStorage>(fileName);
            }

            static Ref<DataStorage> CreateRef(std::string fileName)
            {
                return std::make_shared<DataStorage>(fileName);
            }

        private:
            Ref<Storage> storage_;
    };
} // namespace ntt
