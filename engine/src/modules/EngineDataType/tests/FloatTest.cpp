#include "PreInclude.hpp"

TEST_F(EngineDataTypeTest, FloatDataWillBeLoaded)
{
    storage_->SetGetFloatReturn("Speed", 4, 0);
    storage_->IgnoreSetFloat("Speed");

    ntt::Data<float> speed("Speed", 0, 0, 10, storage_);

    EXPECT_THAT(speed.Value(), testing::Eq(4));
}

TEST_F(EngineDataTypeTest, FloatDataWillBeSavedWhenBeDeleted)
{
    storage_->SetGetFloatReturn("Speed", 4, 0);

    EXPECT_CALL(*storage_, SaveFloat("Speed", 5)).Times(1);

    {
        ntt::Data<float> speed("Speed", 0, 0, 10, storage_);

        speed.SetValue(5);
    }
}