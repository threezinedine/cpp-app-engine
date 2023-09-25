#include "EngineImGuiComponents/PreInclude.hpp"
#include "EngineImGuiComponents/NttImGuiFileDialog.hpp"
#include <ImGuiFileDialog.h>


namespace ntt
{
    FileDialog::FileDialog(StringDataType* value)
        : value_(value)
    {

    }

    FileDialog::~FileDialog()
    {

    }

    bool FileDialog::OnUpdate(FileDialogOptions options)
    {
        bool result = false;

        if (ImGui::Button("Choose a file")) 
        {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "ChooseFileDlgKey", 
                    options.title, 
                    options.types.c_str(), 
                    options.path);
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                value_->SetValue(filePathName);
                result = true;
            }
            
            ImGuiFileDialog::Instance()->Close();
        }

        return result;
    }
} // namespace ntt
