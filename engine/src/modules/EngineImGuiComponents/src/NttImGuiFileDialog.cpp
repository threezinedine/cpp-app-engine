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

    void FileDialog::OnUpdate()
    {
        if (ImGui::Button("Choose a file")) 
        {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

                value_->SetValue(filePathName);
            }
            
            ImGuiFileDialog::Instance()->Close();
        }
    }
} // namespace ntt
