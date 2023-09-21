#pragma once
#include "PreInclude.hpp"
#include <cstring>
#include <any>
#include <iostream>


class DataStorageMocking: public ntt::DataStorage
{
    public:
        // -------------------- BEGIN ----------------------- 
        // Save value for int
        void SaveValue(const char* name, int value) override
        {
            saveValue_int_call_counts_++;
            saveValue_int_Name_ = name;
            saveValue_int_Value_ = value;
        }

        int saveValue_int_call_counts_ = 0;
        const char* saveValue_int_Name_;
        int saveValue_int_Value_;

        void ExpectSaveValueIntCall(int times, const char* expectName, int value)
        {
            EXPECT_THAT(saveValue_int_Name_, testing::StrEq(expectName));
            EXPECT_THAT(saveValue_int_call_counts_, testing::Eq(times));
            EXPECT_THAT(saveValue_int_Value_, testing::Eq(value));
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Save value for float
        void SaveValue(const char* name, float value) override
        {
            saveValue_float_call_counts_++;
            saveValue_float_Name_ = name;
            saveValue_float_Value_ = value;
        }
        int saveValue_float_call_counts_ = 0;
        const char* saveValue_float_Name_;
        float saveValue_float_Value_;

        void ExpectSaveValueFloatCall(int times, const char* expectName, float value)
        {
            EXPECT_THAT(saveValue_float_Name_, testing::StrEq(expectName));
            EXPECT_THAT(saveValue_float_call_counts_, testing::Eq(times));
            EXPECT_THAT(saveValue_float_Value_, testing::FloatEq(value));
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Save value for bool
        void SaveValue(const char* name, bool value) override
        {
            saveValue_bool_call_counts_++;
            saveValue_bool_Name_ = name;
            saveValue_bool_Value_ = value;
        }
        int saveValue_bool_call_counts_ = 0;
        const char* saveValue_bool_Name_;
        bool saveValue_bool_Value_;

        void ExpectSaveValueBoolCall(int times, const char* expectName, bool value)
        {
            EXPECT_THAT(saveValue_bool_Name_, testing::StrEq(expectName));
            EXPECT_THAT(saveValue_bool_call_counts_, testing::Eq(times));
            EXPECT_THAT(saveValue_bool_Value_, testing::Eq(value));
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Get value for int
        int GetValue(const char* name, int defaultValue) override
        {
            if(defaultValue == getValue_int_defaultValue)
            {
                return getValue_int_returnValue_;
            }
            else 
            {
                return 0;
            }
        }

        int getValue_int_returnValue_ = 0;
        int getValue_int_defaultValue = 0;

        void SetGetValue(const char* name, int value, int defaultValue)
        {
            getValue_int_returnValue_ = value;
            getValue_int_defaultValue = defaultValue;
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Get value for float
        float GetValue(const char* name, float defaultValue) override
        {
            if(defaultValue == getValue_float_defaultValue)
            {
                return getValue_float_returnValue_;
            }
            else 
            {
                return getValue_float_defaultValue;
            }
        }

        float getValue_float_returnValue_ = 0;
        float getValue_float_defaultValue = 0;

        void SetGetValue(const char* name, float value, float defaultValue)
        {
            getValue_float_returnValue_ = value;
            getValue_float_defaultValue = defaultValue;
        }
        // --------------------  END  ----------------------- 

        // -------------------- BEGIN ----------------------- 
        // Get value for bool
        bool GetValue(const char* name) override
        {
            return getValue_bool_returnValue_;
        }

        bool getValue_bool_returnValue_ = false;

        void SetGetValue(const char* name, bool value)
        {
            getValue_bool_returnValue_ = value;
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Save values for std::vector<int>
        void SaveValues(const char* name, std::vector<int> value) override
        {
            saveValues_int_call_counts_++;
            saveValues_int_Name_ = name;
            saveValues_int_Value_ = value;
        }

        int saveValues_int_call_counts_ = 0;
        const char* saveValues_int_Name_;
        std::vector<int> saveValues_int_Value_;

        void ExpectSaveValuesIntCall(int times, const char* expectName, std::vector<int> value)
        {
            EXPECT_THAT(saveValues_int_Name_, testing::StrEq(expectName));
            EXPECT_THAT(saveValues_int_call_counts_, testing::Eq(times));
            EXPECT_THAT(ntt::VectorsEqual<int>(
                value,
                saveValues_int_Value_
            ), testing::IsTrue());
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Save values for std::vector<float>
        void SaveValues(const char* name, std::vector<float> value) override
        {
            saveValues_float_call_counts_++;
            saveValues_float_Name_ = name;
            saveValues_float_Value_ = value;
        }
        int saveValues_float_call_counts_ = 0;
        const char* saveValues_float_Name_;
        std::vector<float> saveValues_float_Value_;

        void ExpectSaveValuesFloatCall(int times, const char* expectName, std::vector<float> value)
        {
            EXPECT_THAT(saveValues_float_Name_, testing::StrEq(expectName));
            EXPECT_THAT(saveValues_float_call_counts_, testing::Eq(times));
            EXPECT_THAT(ntt::VectorsEqual<float>(
                value,
                saveValues_float_Value_
            ), testing::IsTrue());
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Get values for std::vector<int>
        std::vector<int> GetValues(const char* name, std::vector<int> defaultValue) override
        {
            if(ntt::VectorsEqual<int>(
                    getValues_int_defaultValue,
                    defaultValue
                ))
            {
                return getValues_int_returnValue_;
            }
            else 
            {
                return {};
            }
        }

        std::vector<int> getValues_int_returnValue_ = { };
        // const char* getValues_int_ExpectedName;
        std::vector<int> getValues_int_defaultValue = { };

        void SetGetValues(const char* name, std::vector<int> value, std::vector<int> defaultValue)
        {
            getValues_int_returnValue_ = value;
            // getValues_int_ExpectedName = name;
            getValues_int_defaultValue = defaultValue;
        }
        // --------------------  END  ----------------------- 


        // -------------------- BEGIN ----------------------- 
        // Get values for std::vector<float>
        std::vector<float> GetValues(const char* name, std::vector<float> defaultValue) override
        {
            if(ntt::VectorsEqual<float>(
                    getValues_float_defaultValue,
                    defaultValue
                ))
            {
                return getValues_float_returnValue_;
            }
            else 
            {
                return {};
            }
        }

        std::vector<float> getValues_float_returnValue_ = { };
        // const char* getValues_float_ExpectedName;
        std::vector<float> getValues_float_defaultValue = { };

        void SetGetValues(const char* name, std::vector<float> value, std::vector<float> defaultValue)
        {
            getValues_float_returnValue_ = value;
            // getValues_float_ExpectedName = name;
            getValues_float_defaultValue = defaultValue;
        }

    static ntt::Ref<DataStorageMocking> CreateRef()
    {
        return std::make_shared<DataStorageMocking>();
    }
};


class EngineDataTypeTest: public testing::Test
{
    protected:
        void SetUp() override
        {
            storage_ = DataStorageMocking::CreateRef();
        }

        void TearDown() override
        {

        }

        ntt::Ref<DataStorageMocking> storage_;
};