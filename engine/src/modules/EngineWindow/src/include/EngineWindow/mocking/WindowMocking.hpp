#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "EngineCores/EngineCores.hpp"
#include "EngineWindow/Window.hpp"


class WindowMocking : public ntt::Window 
{
    public:
        MOCK_METHOD(void, Init, (), (override));
        MOCK_METHOD(void, ImGuiBackendInit, (), (override));
        MOCK_METHOD(void, OnUpdateBegin, (ntt::Timestep), (override));
        MOCK_METHOD(void, OnUpdateEnd, (ntt::Timestep), (override));
        MOCK_METHOD(void, Release, (), (override));
        MOCK_METHOD(void, ImGuiBackendRelease, (), (override));
        MOCK_METHOD(bool, ShouldClose, (), (override));

        void WindowShouldCloseAfter(int period)
        {
            testing::Sequence sequence;

            for (int i=0; i<period; i++)
            {
                EXPECT_CALL(*this, ShouldClose())
                                .InSequence(sequence)
                                .WillOnce(testing::Return(false));
            }

            EXPECT_CALL(*this, ShouldClose())
                            .InSequence(sequence)
                            .WillOnce(testing::Return(true));
        }

        void IgnoreMocking()
        {
            EXPECT_CALL(*this, Init()).Times(testing::AnyNumber());
            EXPECT_CALL(*this, ImGuiBackendInit()).Times(testing::AnyNumber());
            EXPECT_CALL(*this, OnUpdateBegin(testing::_)).Times(testing::AnyNumber());
            EXPECT_CALL(*this, OnUpdateEnd(testing::_)).Times(testing::AnyNumber());
            EXPECT_CALL(*this, Release()).Times(testing::AnyNumber());
            EXPECT_CALL(*this, ImGuiBackendRelease()).Times(testing::AnyNumber());
        }

        static ntt::Ref<WindowMocking> CreateRef()
        {
            return std::make_shared<WindowMocking>();
        }
};