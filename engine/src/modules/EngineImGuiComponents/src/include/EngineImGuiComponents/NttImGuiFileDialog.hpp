#pragma once

#include "EngineCores/EngineCores.hpp"

namespace ntt
{
    class StringDataType;

    class FileDialog
    {
        public:
            FileDialog(StringDataType* value);

            ~FileDialog();

            void OnUpdate();

            static Scope<FileDialog> CreateScope(StringDataType* value)
            {
                return std::make_unique<FileDialog>(value);
            }

        private:
            StringDataType* value_;
    }; 
} // namespace ntt
