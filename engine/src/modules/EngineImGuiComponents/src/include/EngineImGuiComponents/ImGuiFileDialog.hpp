#pragma once

#include "EngineDataType/EngineDataType.hpp"


namespace ntt
{
    class FileDialog
    {
        public:
            FileDialog(Ref<String<256>> value);
            ~FileDialog();

        private:
            Ref<String<256>> value_;
    }; 
} // namespace ntt
