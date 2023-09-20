#include "PreInclude.hpp"


TEST_F(EngineDataTypeTest, GivenAnIntegerValueIsCreatedWithThenItHasTheImguiRender)
{
    ntt::Data<int> value("Scores");

    EXPECT_THAT(value.Value(), testing::Eq(0));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithDefaultValueThenItHasDefaultValue)
{
    ntt::Data<int> value("Scores", 5);

    EXPECT_THAT(value.Value(), testing::Eq(5));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerThenItCanRunOnUpdate)
{
    ntt::Data<int> value("Scores");
    ntt::Timestep ts;

    EXPECT_NO_THROW(value.OnUpdate(ts, ntt::NONE));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerThenItHasGetName)
{
    ntt::Data<int> value("Scores");

    EXPECT_THAT(value.GetName(), testing::StrEq("Scores"));
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithDefaultMinMax)
{
    ntt::Data<int> value("Scores", 0, 0, 100);
}

TEST_F(EngineDataTypeTest, IntegerConstructorWithDefaultValueExceedTheLimits)
{
    ntt::Data<int> value("Scores", 0, 10, 100);

    EXPECT_THAT(value.Value(), 10);
}

TEST_F(EngineDataTypeTest, GivenAnIntegerWithStorageThenBeSavedWhenDeleted)
{
    storage_->SetGetValue("Speed", 2, 4);

    ntt::Data<int> value("Scores", 4, 0, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(2));
}

TEST_F(EngineDataTypeTest, TestIntegerChange)
{
    ntt::Data<int> value("Scores", 4);
    value.SetValue(3);

    EXPECT_THAT(value.Value(), testing::Eq(3));
}

TEST_F(EngineDataTypeTest, TestIntegerChangeValueLessThanMin)
{
    ntt::Data<int> value("Scores", 10, 10, 100);
    value.SetValue(3);

    EXPECT_THAT(value.Value(), testing::Eq(10));
}

TEST_F(EngineDataTypeTest, SaveValueWhenBeDeleted)
{
    storage_->SetGetValue("Scores", 2, 4);

    {
        ntt::Data<int> value("Scores", 4, 0, 100, storage_);
        value.SetValue(3);
    }

    storage_->ExpectSaveValueIntCall(1, "Scores", 3);
}

TEST_F(EngineDataTypeTest, GetDataWithExceedTheLimits)
{
    storage_->SetGetValue("Scores", 101, 4);

    ntt::Data<int> value("Scores", 4, 0, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(100));
}

TEST_F(EngineDataTypeTest, GetDataWithLessThanTheLimit)
{
    storage_->SetGetValue("Scores", 3, 10);

    ntt::Data<int> value("Scores", 10, 10, 100, storage_);

    EXPECT_THAT(value.Value(), testing::Eq(10));
}