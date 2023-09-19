#pragma once
#include "PreInclude.hpp"


class DataStorageMocking: public ntt::DataStorage
{
    public:
        MOCK_METHOD(void, SaveInteger, (const char*, int), (override));
        MOCK_METHOD(int, GetInteger, (const char*, int), (override));

        MOCK_METHOD(void, SaveInteger2, (const char*, std::vector<int>), (override));
        MOCK_METHOD(std::vector<int>, GetInteger2, (const char*, std::vector<int>), (override));

        MOCK_METHOD(void, SaveInteger3, (const char*, std::vector<int>), (override));
        MOCK_METHOD(std::vector<int>, GetInteger3, (const char*, std::vector<int>), (override));

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

        void SetGetInteger2Return(const char* name, std::vector<int> value, std::vector<int> defaultValue)
        {
            ON_CALL(*this, GetInteger2(name, defaultValue))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetInteger2(name, defaultValue)).Times(testing::AnyNumber());
        }

        void IgnoreSetInteger2(const char* name)
        {
            EXPECT_CALL(*this, SaveInteger2(name, testing::_)).Times(testing::AnyNumber());
        }

        void SetGetInteger3Return(const char* name, std::vector<int> value, std::vector<int> defaultValue)
        {
            ON_CALL(*this, GetInteger3(name, defaultValue))
                .WillByDefault(testing::Return(value));

            EXPECT_CALL(*this, GetInteger3(name, defaultValue)).Times(testing::AnyNumber());
        }

        void IgnoreSetInteger3(const char* name)
        {
            EXPECT_CALL(*this, SaveInteger3(name, testing::_)).Times(testing::AnyNumber());
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