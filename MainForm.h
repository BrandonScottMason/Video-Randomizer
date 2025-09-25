#pragma once
#include <msclr/marshal_cppstd.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <random>

namespace fs = std::filesystem;

namespace VRand
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for MainForm
    /// </summary>
    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
            m_videoFiles = new std::vector<fs::directory_entry>();
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::Button^ btn_fileRoot;
    private: System::Windows::Forms::Label^ lbl_fileRoot;
    private: System::Windows::Forms::TextBox^ txt_fileRoot;



    private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
    private: System::Windows::Forms::ListView^ lstVw_files;


    protected:

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container ^components;
        System::Windows::Forms::ColumnHeader^ columnHeader1;

        /// <summary>
        /// List of nearly all video file extensions
        ///    Copied from: https://gist.github.com/aaomidi/0a3b5c9bd563c9e012518b495410dc0e
        /// </summary>
        static array<System::String^>^ m_supportedVideoFileExtensions = gcnew array<System::String^>(38){
            "webm", "mkv", "flv", "vob", "ogv", "ogg", "rrc","gifv", "mng", "mov",
            "avi", "qt", "wmv", "yuv", "rm", "asf", "amv", "mp4", "m4p", "m4v",
            "mpg", "mp2", "mpeg", "mpe", "mpv", "m4v", "svi", "3gp", "3g2", "mxf",
            "roq", "nsv", "flv", "f4v", "f4p", "f4a", "f4b", "mod" };
    private: System::Windows::Forms::ColumnHeader^ columnHeader2;
    private: System::Windows::Forms::Button^ btn_randomize;

        /// <summary>
        /// Container for adding new items to the list view
        /// </summary>
        System::Windows::Forms::ListViewItem^ m_listViewItem;
    private: AxAXVLC::AxVLCPlugin2^ axVLCPlugin21;
    private: System::Windows::Forms::Button^ btn_playAll;



    private: System::Windows::Forms::Button^ btn_stop;
    private: System::Windows::Forms::Button^ btn_prev;
    private: System::Windows::Forms::Button^ btn_next;



        /// <summary>
        ///    Directory Entries that the List View is displaying
        /// </summary>
        std::vector<fs::directory_entry>* m_videoFiles;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->btn_fileRoot = (gcnew System::Windows::Forms::Button());
            this->lbl_fileRoot = (gcnew System::Windows::Forms::Label());
            this->txt_fileRoot = (gcnew System::Windows::Forms::TextBox());
            this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
            this->lstVw_files = (gcnew System::Windows::Forms::ListView());
            this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
            this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
            this->btn_randomize = (gcnew System::Windows::Forms::Button());
            this->axVLCPlugin21 = (gcnew AxAXVLC::AxVLCPlugin2());
            this->btn_playAll = (gcnew System::Windows::Forms::Button());
            this->btn_stop = (gcnew System::Windows::Forms::Button());
            this->btn_prev = (gcnew System::Windows::Forms::Button());
            this->btn_next = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axVLCPlugin21))->BeginInit();
            this->SuspendLayout();
            // 
            // btn_fileRoot
            // 
            this->btn_fileRoot->Location = System::Drawing::Point(717, 4);
            this->btn_fileRoot->Name = L"btn_fileRoot";
            this->btn_fileRoot->Size = System::Drawing::Size(35, 22);
            this->btn_fileRoot->TabIndex = 0;
            this->btn_fileRoot->Text = L"...";
            this->btn_fileRoot->UseVisualStyleBackColor = true;
            this->btn_fileRoot->Click += gcnew System::EventHandler(this, &MainForm::btn_fileRoot_Click);
            // 
            // lbl_fileRoot
            // 
            this->lbl_fileRoot->AutoSize = true;
            this->lbl_fileRoot->Location = System::Drawing::Point(12, 9);
            this->lbl_fileRoot->Name = L"lbl_fileRoot";
            this->lbl_fileRoot->Size = System::Drawing::Size(92, 13);
            this->lbl_fileRoot->TabIndex = 1;
            this->lbl_fileRoot->Text = L"Root Video Folder";
            // 
            // txt_fileRoot
            // 
            this->txt_fileRoot->Location = System::Drawing::Point(110, 6);
            this->txt_fileRoot->Name = L"txt_fileRoot";
            this->txt_fileRoot->Size = System::Drawing::Size(601, 20);
            this->txt_fileRoot->TabIndex = 2;
            // 
            // lstVw_files
            // 
            this->lstVw_files->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left));
            this->lstVw_files->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
                this->columnHeader1,
                    this->columnHeader2
            });
            this->lstVw_files->HideSelection = false;
            this->lstVw_files->Location = System::Drawing::Point(12, 32);
            this->lstVw_files->Name = L"lstVw_files";
            this->lstVw_files->Size = System::Drawing::Size(740, 374);
            this->lstVw_files->TabIndex = 6;
            this->lstVw_files->UseCompatibleStateImageBehavior = false;
            this->lstVw_files->View = System::Windows::Forms::View::Details;
            // 
            // columnHeader1
            // 
            this->columnHeader1->Text = L"File Name";
            this->columnHeader1->Width = 300;
            // 
            // columnHeader2
            // 
            this->columnHeader2->Text = L"Path";
            this->columnHeader2->Width = 435;
            // 
            // btn_randomize
            // 
            this->btn_randomize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_randomize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_randomize->Location = System::Drawing::Point(12, 412);
            this->btn_randomize->Name = L"btn_randomize";
            this->btn_randomize->Size = System::Drawing::Size(115, 42);
            this->btn_randomize->TabIndex = 7;
            this->btn_randomize->Text = L"Randomize List";
            this->btn_randomize->UseVisualStyleBackColor = true;
            this->btn_randomize->Click += gcnew System::EventHandler(this, &MainForm::btn_randomize_Click);
            // 
            // axVLCPlugin21
            // 
            this->axVLCPlugin21->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->axVLCPlugin21->Enabled = true;
            this->axVLCPlugin21->Location = System::Drawing::Point(758, 4);
            this->axVLCPlugin21->Name = L"axVLCPlugin21";
            this->axVLCPlugin21->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axVLCPlugin21.OcxState")));
            this->axVLCPlugin21->Size = System::Drawing::Size(740, 450);
            this->axVLCPlugin21->TabIndex = 8;
            // 
            // btn_playAll
            // 
            this->btn_playAll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_playAll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_playAll->Location = System::Drawing::Point(467, 408);
            this->btn_playAll->Name = L"btn_playAll";
            this->btn_playAll->Size = System::Drawing::Size(63, 42);
            this->btn_playAll->TabIndex = 9;
            this->btn_playAll->Text = L"Play All";
            this->btn_playAll->UseVisualStyleBackColor = true;
            this->btn_playAll->Click += gcnew System::EventHandler(this, &MainForm::btn_playAll_Click);
            // 
            // btn_stop
            // 
            this->btn_stop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_stop->Location = System::Drawing::Point(617, 409);
            this->btn_stop->Name = L"btn_stop";
            this->btn_stop->Size = System::Drawing::Size(54, 41);
            this->btn_stop->TabIndex = 11;
            this->btn_stop->Text = L"⏹️";
            this->btn_stop->UseVisualStyleBackColor = true;
            this->btn_stop->Click += gcnew System::EventHandler(this, &MainForm::btn_stop_Click);
            // 
            // btn_prev
            // 
            this->btn_prev->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_prev->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_prev->Location = System::Drawing::Point(536, 409);
            this->btn_prev->Name = L"btn_prev";
            this->btn_prev->Size = System::Drawing::Size(75, 41);
            this->btn_prev->TabIndex = 12;
            this->btn_prev->Text = L"Previous";
            this->btn_prev->UseVisualStyleBackColor = true;
            this->btn_prev->Click += gcnew System::EventHandler(this, &MainForm::btn_prev_Click);
            // 
            // btn_next
            // 
            this->btn_next->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_next->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_next->Location = System::Drawing::Point(677, 408);
            this->btn_next->Name = L"btn_next";
            this->btn_next->Size = System::Drawing::Size(75, 42);
            this->btn_next->TabIndex = 13;
            this->btn_next->Text = L"Next";
            this->btn_next->UseVisualStyleBackColor = true;
            this->btn_next->Click += gcnew System::EventHandler(this, &MainForm::btn_next_Click);
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1513, 462);
            this->Controls->Add(this->btn_next);
            this->Controls->Add(this->btn_prev);
            this->Controls->Add(this->btn_stop);
            this->Controls->Add(this->btn_playAll);
            this->Controls->Add(this->axVLCPlugin21);
            this->Controls->Add(this->btn_randomize);
            this->Controls->Add(this->lstVw_files);
            this->Controls->Add(this->txt_fileRoot);
            this->Controls->Add(this->lbl_fileRoot);
            this->Controls->Add(this->btn_fileRoot);
            this->Name = L"MainForm";
            this->Text = L"Video Randomizer";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axVLCPlugin21))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: static System::Boolean ContainsString(array<String^>^ stringArray, String^ targetString)
    {
        if (System::String::IsNullOrEmpty(targetString))
        {
            return false;
        }

        for each (String^ s in stringArray)
        {
            // path().extension() includes the leading dot, so Substring(1) to skip it
            if ( s->Equals(targetString->Substring(1)))
            {
                return true;
            }
        }
        return false;
    }

    private: System::Void AddVideoFileNamesAndPathsToListView()
    {
        lstVw_files->SelectedItems->Clear();
        this->lstVw_files->Items->Clear();

        for (int i = 0; i < m_videoFiles->size(); i++)
        {
            System::String^ fileName = gcnew System::String(m_videoFiles->at(i).path().filename().string().c_str());
            System::String^ filePath = gcnew System::String(m_videoFiles->at(i).path().c_str());
            array<System::String^>^ row = gcnew array<System::String^>{fileName, filePath};
            this->m_listViewItem = gcnew Windows::Forms::ListViewItem(row);
            this->lstVw_files->Items->Add(this->m_listViewItem);
        }
    }

    private: System::Void PopulateFileList(System::String^ folderPath)
    {
        std::string path = msclr::interop::marshal_as<std::string>(folderPath);
        for (const auto & entry : fs::recursive_directory_iterator(path))
        {
            System::String^ ext = gcnew System::String(entry.path().extension().c_str());
            if (ContainsString(m_supportedVideoFileExtensions, ext)) // This skips any non-video files
            {
                m_videoFiles->push_back(entry);
            }
        }

        // Sort the file names alphabetically
        std::sort(m_videoFiles->begin(), m_videoFiles->end());

        AddVideoFileNamesAndPathsToListView();
    }

    private: System::Void btn_fileRoot_Click(System::Object^ sender, System::EventArgs^ e)
    {
        System::Windows::Forms::FolderBrowserDialog^ dialog = gcnew System::Windows::Forms::FolderBrowserDialog();
        System::Windows::Forms::DialogResult result = dialog->ShowDialog();

        if (result == System::Windows::Forms::DialogResult::OK)
        {
            this->txt_fileRoot->Text = dialog->SelectedPath;
            m_videoFiles->clear();
            PopulateFileList(dialog->SelectedPath);
        }
    }

    private: System::Void btn_randomize_Click(System::Object^ sender, System::EventArgs^ e)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_videoFiles->begin(), m_videoFiles->end(), g);
        AddVideoFileNamesAndPathsToListView();
    }
    
    private: System::Void btn_playAll_Click(System::Object^ sender, System::EventArgs^ e) 
    {
        if (this->lstVw_files->Items->Count > 0)
        {
            lstVw_files->Items[0]->Focused = true;
            lstVw_files->Items[0]->Selected = true;
            lstVw_files->Items[0]->EnsureVisible();
            lstVw_files->Select();

            for each (System::Windows::Forms::ListViewItem ^ item in lstVw_files->Items)
            {
                Uri^ uri = gcnew Uri(item->SubItems[1]->Text);
                axVLCPlugin21->playlist->add(uri->AbsoluteUri, item->Text, nullptr);
            }
        }
        /*else if (selectedVideoCount > 1)
        {
            Feature: Select multiple episodes, then push play to play the selected items in order.
            Note: Probably should be a separate button
        }*/
        else
        {
            System::Windows::Forms::OpenFileDialog^ openFileD = gcnew System::Windows::Forms::OpenFileDialog();
            if (openFileD->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                axVLCPlugin21->playlist->add("file:///" + openFileD->FileName, openFileD->SafeFileName, nullptr);
            }
        }

        axVLCPlugin21->playlist->play();
    }

    private: System::Void btn_stop_Click(System::Object^ sender, System::EventArgs^ e)
    {
        axVLCPlugin21->playlist->stop();
    }

    private: System::Void btn_next_Click(System::Object^ sender, System::EventArgs^ e)
    {
        axVLCPlugin21->playlist->next();
    }

    private: System::Void btn_prev_Click(System::Object^ sender, System::EventArgs^ e)
    {
        axVLCPlugin21->playlist->prev();
    }
};
}
