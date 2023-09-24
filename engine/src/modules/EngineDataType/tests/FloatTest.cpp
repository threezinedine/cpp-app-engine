#include "PreInclude.hpp"
#include "EngineDataType/Data.hpp"


TEST_F(EngineDataTypeTest, FloatDataWillBeLoaded)
{
    storage_->SetGetValue("Speed", 4.0f, 0.0f);

    ntt::Data<float> speed("Speed", 0.0f, 0.0f, 10.0f, storage_);

    EXPECT_THAT(speed.Value(), testing::Eq(4));
}

TEST_F(EngineDataTypeTest, FloatDataWillBeSavedWhenBeDeleted)
{
    storage_->SetGetValue("Speed", 4.0f, 0.0f);

    {
        ntt::Data<float> speed("Speed", 0.0f, 0.0f, 10.0f, storage_);

        speed.SetValue(5.3f);
    }

    storage_->ExpectSaveValueFloatCall(1, "Speed", 5.3f);
}


TEST_F(EngineDataTypeTest, FloatDataToString)
{
    ntt::Data<float> speed("Speed", 3.4f);

    EXPECT_THAT(speed.ToString(), testing::StrEq("Speed: 3.4"));
}