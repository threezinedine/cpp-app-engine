#include "PreInclude.hpp"


// TEST_F(EngineDataTypeTest, DISABLED_FloatValuesAreLoaded)
// {
//     storage_->SetGetFloatsReturn("Velocity", { 1.2f, 1.2f }, { 0, 0 });
//     storage_->IgnoreSetFloats("Velocity");

//     ntt::Array<float, 2> velocity("Velocity", { 0, 0 }, 0, 10, storage_);

//     EXPECT_THAT(velocity.Value(), testing::ElementsAreArray(std::vector<float>{1.2f, 1.2f}));
// }