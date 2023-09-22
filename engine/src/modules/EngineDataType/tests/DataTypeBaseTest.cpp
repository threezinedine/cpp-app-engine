#include "PreInclude.hpp"
#include "EngineDataType/DataTypeBase.hpp"


class DataTypeDerived: public ntt::DataTypeBase<int>
{
    public:
        DataTypeDerived(const char* name)
            : ntt::DataTypeBase<int>(name, 0)
        {

        }

        DataTypeDerived(const char* name, int defaultValue)
            : ntt::DataTypeBase<int>(name, defaultValue)
        {
            Initialize();
        }

        DataTypeDerived(const char* name, ntt::Ref<ntt::DataStorage> storage)
            : ntt::DataTypeBase<int>(name, 0, storage)
        {
            Initialize();
        }

        ~DataTypeDerived()
        {

        }

        void OnUpdate(ntt::Timestep ts, ntt::InputType type) override
        {

        }

        void SetValue(int value) override
        {
            value_ = value;
        }
};


TEST_F(EngineDataTypeTest, DataTypeBaseHasTheGetName)
{
    DataTypeDerived data("Hello");

    EXPECT_THAT(data.GetName(), testing::StrEq("Hello"));
}

TEST_F(EngineDataTypeTest, DataTypeBaseHasTheDefaultValueIsZero)
{
    DataTypeDerived data("Hello");

    EXPECT_THAT(data.Value(), testing::Eq(0));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedHasTheConstructorWithDefaultValueAsParam)
{
    DataTypeDerived data("Hello", 3);

    EXPECT_THAT(data.Value(), testing::Eq(3));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedWillHaveTheVirtualMethodForOnUpdate)
{
    ntt::Timestep ts;
    DataTypeDerived data("Hello");

    EXPECT_NO_THROW(data.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedWithVirtualFuncSetValue)
{
    DataTypeDerived data("Hello");

    data.SetValue(4);

    EXPECT_THAT(data.Value(), testing::Eq(4));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedWithStorage)
{
    storage_->SetGetValue("Hello", 3, 0);

    DataTypeDerived data("Hello", storage_);

    EXPECT_THAT(data.Value(), testing::Eq(3));
}

TEST_F(EngineDataTypeTest, DataTypeDerivedBeSavedWhenBeDeleted)
{
    storage_->SetGetValue("Hello", 3, 0);

    {
        DataTypeDerived data("Hello", storage_);
        data.SetValue(10);
    }

    storage_->ExpectSaveValueIntCall(1, "Hello", 10);
}