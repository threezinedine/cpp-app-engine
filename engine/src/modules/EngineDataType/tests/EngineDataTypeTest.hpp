#pragma once
#include "PreInclude.hpp"


class DataStorageMocking: public ntt::DataStorage
{
    public:
        MOCK_METHOD(void, SaveInteger, (const char*, int), (override));
        MOCK_METHOD(int, GetInteger, (const char*, int), (override));

        MOCK_METHOD(void, SaveIntegers, (const char*, std::vector<int>), (override));
        MOCK_METHOD(std::vector<int>, GetIntegers, (const char*, std::vector<int>), (override));

        MOCK_METHOD(void, SaveFloat, (const char*, float), (override));
        MOCK_METHOD(float, GetFloat, (const char*, float), (override));

        static ntt::Ref<DataStorageMocking> CreateRef()
        {
            return std::make_shared<DataStorageMocking>();
        }

        void SetGetIntegerReturn(const char* name, int value, int defaultValue = 0)
        {
            ON_CALL(*this, GetInteger(name, defaultValue))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetInteger(name, defaultValue)).Times(testing::AnyNumber());
        }

        void IgnoreSetInteger(const char* name)
        {
            EXPECT_CALL(*this, SaveInteger(name, testing::_)).Times(testing::AnyNumber());
        }

        void SetGetIntegersReturn(const char* name, std::vector<int> value, std::vector<int> defaultValue)
        {
            ON_CALL(*this, GetIntegers(name, defaultValue))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetIntegers(name, defaultValue)).Times(testing::AnyNumber());
        }

        void IgnoreSetIntegers(const char* name)
        {
            EXPECT_CALL(*this, SaveIntegers(name, testing::_)).Times(testing::AnyNumber());
        }

        void SetGetFloatReturn(const char* name, float value, float defaultValue = 0)
        {
            ON_CALL(*this, GetFloat(name, defaultValue))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetFloat(name, defaultValue)).Times(testing::AnyNumber());
        }

        void IgnoreSetFloat(const char* name)
        {
            EXPECT_CALL(*this, SaveFloat(name, testing::_)).Times(testing::AnyNumber());
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