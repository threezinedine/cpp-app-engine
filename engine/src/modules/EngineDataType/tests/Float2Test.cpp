#include "PreInclude.hpp"


TEST_F(EngineDataTypeTest, FloatValuesAreLoaded)
{
    storage_->SetGetValues("Velocity", std::vector<float>{ 1.2f, 1.2f }, { 0.0f, 0.0f });

    ntt::Array<float, 2> velocity("Velocity", { 0, 0 }, 0, 10, storage_);

    EXPECT_THAT(velocity.Value(), testing::ElementsAreArray(std::vector<float>{1.2f, 1.2f}));
}

TEST_F(EngineDataTypeTest, FloatValuesToString)
{
    ntt::Array<float, 2> velocity("Velocity", std::vector<float>{ 1.4f, 1.4f });

    EXPECT_THAT(velocity.ToString(), "Velocity: (1.4, 1.4)");
}