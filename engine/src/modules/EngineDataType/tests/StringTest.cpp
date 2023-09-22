#include "PreInclude.hpp"


TEST_F(EngineDataTypeTest, InitializeStringData)
{
    ntt::String str("String");

    EXPECT_THAT(str.Value(), testing::StrEq(""));
}

TEST_F(EngineDataTypeTest, GetNameOfTheData)
{
    ntt::String str("String");

    EXPECT_THAT(str.GetName(), testing::StrEq("String"));
}

TEST_F(EngineDataTypeTest, InitializeWithDefaultVaulue)
{
    std::string defaultString = "default string";
    ntt::String str("String", defaultString);

    EXPECT_THAT(str.Value(), testing::StrEq(defaultString));
}

TEST_F(EngineDataTypeTest, StringWithOnUpdateMethod)
{
    ntt::Timestep ts;
    ntt::String str("String");

    EXPECT_NO_THROW(str.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, StringInitiailizeWithStorage)
{
    storage_->SetGetValue("String", "storage string", "");

    ntt::String str("String", storage_);

    EXPECT_THAT(str.Value(), testing::StrEq("storage string"));
}

TEST_F(EngineDataTypeTest, StringSetValueMethod)
{
    ntt::String str("String");

    str.SetValue("Hello World");

    EXPECT_THAT(str.Value(), testing::StrEq("Hello World"));
}

TEST_F(EngineDataTypeTest, StringBeSavedWhenBeDeleted)
{
    storage_->SetGetValue("String", "storage string", "");

    {
        ntt::String str("String", storage_);

        str.SetValue("test");
    }

    storage_->ExpectSaveValueStringCall(1, "String", "test");
}