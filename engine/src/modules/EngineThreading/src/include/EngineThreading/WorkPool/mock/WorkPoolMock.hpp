#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "EngineThreading/WorkPool/Pool.hpp"
#include "EngineCores/EngineCores.hpp"


class WorkPoolMock: public ntt::WorkPool
{
    public:
        WorkPoolMock(const char* name)
            : ntt::WorkPool(name)
        {

        }

        ~WorkPoolMock()
        {

        }

        MOCK_METHOD(void, StartImpl, (), (override));
        MOCK_METHOD(void, StopImpl, (), (override));


        static ntt::Ref<WorkPoolMock> CreateRef(const char* name)
        {
            return std::make_shared<WorkPoolMock>(name);
        }
};