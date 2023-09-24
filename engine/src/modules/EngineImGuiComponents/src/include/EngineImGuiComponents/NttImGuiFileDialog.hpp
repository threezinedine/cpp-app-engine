#pragma once

#include <string>
#include "EngineCores/EngineCores.hpp"

namespace ntt
{
    class StringDataType;
    
    struct FileDialogOptions
    {
        std::string types = "*";
        std::string title = "Choose File";
    };

    class FileDialog
    {
        public:
            FileDialog(StringDataType* value);

            ~FileDialog();

            void OnUpdate(FileDialogOptions options = FileDialogOptions());

            static Scope<FileDialog> CreateScope(StringDataType* value)
            {
                return std::make_unique<FileDialog>(value);
            }

        private:
            StringDataType* value_;
    }; 
} // namespace ntt
