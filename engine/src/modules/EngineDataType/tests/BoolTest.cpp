#include "PreInclude.hpp"
#include "EngineDataType/Bool.hpp"


TEST_F(EngineDataTypeTest, BoolIsInitialize)
{
    ntt::Bool valid("Valid");
    ntt::Timestep ts;

    EXPECT_THAT(valid.Value(), testing::IsFalse());
    EXPECT_THAT(valid.GetName(), testing::StrEq("Valid"));
    EXPECT_NO_THROW(valid.OnUpdate(ts, ntt::NONE));
    EXPECT_THAT(valid.ToString(), testing::StrEq("Valid: false"));
}

TEST_F(EngineDataTypeTest, BoolWithDefaultValue)
{
    ntt::Bool valid("Valid", true);

    EXPECT_THAT(valid.Value(), testing::IsTrue());
    EXPECT_THAT(valid.ToString(), testing::StrEq("Valid: true"));
}

TEST_F(EngineDataTypeTest, BoolWithStorageReturnsTrue)
{
    storage_->SetGetValue("Valid", true);

    ntt::Bool valid("Valid", storage_);

    EXPECT_THAT(valid.Value(), testing::IsTrue());
}

TEST_F(EngineDataTypeTest, BoolWithStorageReturnsFalse)
{
    storage_->SetGetValue("Valid", false);

    ntt::Bool valid("Valid", storage_);

    EXPECT_THAT(valid.Value(), testing::IsFalse());
}

TEST_F(EngineDataTypeTest, BoolSetValueMethod)
{
    ntt::Bool valid("Valid");

    valid.SetValue(true);

    EXPECT_THAT(valid.Value(), testing::IsTrue());
}

TEST_F(EngineDataTypeTest, BoolBeSavedWhenBeDeleted)
{
    storage_->SetGetValue("Valid", false);

    {
        ntt::Bool valid("Valid", storage_);

        valid.SetValue(true);
    }

    storage_->ExpectSaveValueBoolCall(1, "Valid", true);
}