#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EngineCores/EngineCores.hpp"


class WindowMocking : public ntt::Window 
{
    public:
        MOCK_METHOD0(Init, void());
        MOCK_METHOD(void, OnUpdate, (ntt::Timestep), (override));
        MOCK_METHOD0(Release, void());

        static ntt::Ref<WindowMocking> CreateRef()
        {
            return std::make_shared<WindowMocking>();
        }
};