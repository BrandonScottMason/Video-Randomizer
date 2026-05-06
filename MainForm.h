#pragma once
#include <msclr/marshal_cppstd.h>
#include <string>
#include <shobjidl_core.h>
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
#ifdef _DEBUG
            this->btn_debugMenu->Enabled = true;
            this->btn_debugMenu->Visible = true;
#else
            this->btn_debugMenu->Enabled = false;
            this->btn_debugMenu->Visible = false;
#endif // _DEBUG

            m_videoFiles = new std::vector<fs::directory_entry>();
            axVLCPlugin21->MediaPlayerEndReached += gcnew EventHandler(this, &MainForm::PlayerEndReached);
            axVLCPlugin21->MediaPlayerPaused += gcnew EventHandler(this, &MainForm::PlayerPaused);
            axVLCPlugin21->MediaPlayerStopped += gcnew EventHandler(this, &MainForm::PlayerStopped);
            axVLCPlugin21->MediaPlayerPlaying += gcnew EventHandler(this, &MainForm::PlayerPlaying);
        }

    public: System::Void PlayerEndReached(System::Object^ sender, System::EventArgs^ e)
    {
        HighlightCurrentVLCItemInListView();
    }

    public: System::Void PlayerPaused(System::Object^ sender, System::EventArgs^ e)
    {
        this->btn_pause->Text = m_emojiPlay;
    }

    public: System::Void PlayerStopped(System::Object^ sender, System::EventArgs^ e)
    {
        this->btn_pause->Text = m_emojiPlay;
    }

    public: System::Void PlayerPlaying(System::Object^ sender, System::EventArgs^ e) // Happens to be called when a new video starts playing
    {
        this->btn_pause->Text = m_emojiPause;
        HighlightCurrentVLCItemInListView();
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

        virtual bool ProcessCmdKey(System::Windows::Forms::Message% msg, System::Windows::Forms::Keys keyData) override
        {
            /// Full Screen Toggle
            if (keyData == System::Windows::Forms::Keys::F) // F for full screen toggle (also match's VLC's default full screen toggle hotkey)
            {
                ToggleFullScreen();
                return true;
            }

            /// Play/Pause
            if (keyData == System::Windows::Forms::Keys::Space) // Space for play/pause (also match's VLC's default play/pause hotkey)
            {
                PlayPause();
                return true;
            }

            /// Stop
            if (keyData == System::Windows::Forms::Keys::S) // S for stop (also match's VLC's default stop hotkey)
            {
                Stop();
                return true;
            }

            /// Next track in playlist
            if (keyData == System::Windows::Forms::Keys::N) // N for next (also match's VLC's default next hotkey)
            {
                Next();
                return true;
            }

            /// Previous track in playlist
            if (keyData == System::Windows::Forms::Keys::P) // P for previous (also match's VLC's default previous hotkey)
            {
                Previous();
                return true;
            }

            /// Add to playlist
            if (keyData == (System::Windows::Forms::Keys::Oemplus | System::Windows::Forms::Keys::Control) || keyData == (System::Windows::Forms::Keys::Add | System::Windows::Forms::Keys::Control)) // Ctrl + Plus for adding to list
            {
                PromptAddToListView();
                return true;
            }

            /// Randomize playlist
            if (keyData == (System::Windows::Forms::Keys::R | System::Windows::Forms::Keys::Control)) // Ctrl + R for randomize (also match's VLC's default randomize hotkey)
            {
                RandomizeListView();
                return true;
            }

            /// Clear playlist
            if (keyData == System::Windows::Forms::Keys::Delete) // Delete to clear the list view
            {
                ClearListView();
                return true;
            }

            // For keys that are not processed, call the base class's method
            return __super::ProcessCmdKey(msg, keyData);
        };

    private:
        System::Boolean m_listViewMatchesVLCPlaylist = true;
        System::String^ m_emojiPause = u8"⏸️";
        System::String^ m_emojiPlay = u8"▶️";
        System::ComponentModel::BackgroundWorker^ backgroundWorker1;
        System::Windows::Forms::ListView^ lstVw_files;
        System::Windows::Forms::Button^ btn_fileRoot;
        System::Windows::Forms::Button^ btn_clearList;
        System::Windows::Forms::Button^ btn_debugMenu;
        System::ComponentModel::IContainer^ components;

        /// <summary>
        /// Required designer variable.
        /// </summary>
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
        System::Windows::Forms::ColumnHeader^ columnHeader2;
        System::Windows::Forms::Button^ btn_randomize;

        /// <summary>
        /// Container for adding new items to the list view
        /// </summary>
        System::Windows::Forms::ListViewItem^ m_listViewItem;
        AxAXVLC::AxVLCPlugin2^ axVLCPlugin21;

        System::Windows::Forms::Button^ btn_stop;
        System::Windows::Forms::Button^ btn_prev;
        System::Windows::Forms::Button^ btn_next;
        System::Windows::Forms::Button^ btn_pause;
        System::Windows::Forms::Button^ btn_fullScreen;
private: System::Windows::Forms::ToolTip^ toolTip1;

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
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->btn_fileRoot = (gcnew System::Windows::Forms::Button());
            this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
            this->lstVw_files = (gcnew System::Windows::Forms::ListView());
            this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
            this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
            this->btn_randomize = (gcnew System::Windows::Forms::Button());
            this->axVLCPlugin21 = (gcnew AxAXVLC::AxVLCPlugin2());
            this->btn_stop = (gcnew System::Windows::Forms::Button());
            this->btn_prev = (gcnew System::Windows::Forms::Button());
            this->btn_next = (gcnew System::Windows::Forms::Button());
            this->btn_pause = (gcnew System::Windows::Forms::Button());
            this->btn_fullScreen = (gcnew System::Windows::Forms::Button());
            this->btn_debugMenu = (gcnew System::Windows::Forms::Button());
            this->btn_clearList = (gcnew System::Windows::Forms::Button());
            this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axVLCPlugin21))->BeginInit();
            this->SuspendLayout();
            // 
            // btn_fileRoot
            // 
            this->btn_fileRoot->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_fileRoot->Location = System::Drawing::Point(12, 4);
            this->btn_fileRoot->Name = L"btn_fileRoot";
            this->btn_fileRoot->Size = System::Drawing::Size(30, 25);
            this->btn_fileRoot->TabIndex = 0;
            this->btn_fileRoot->Text = L"+";
            this->toolTip1->SetToolTip(this->btn_fileRoot, L"Add Folders (Ctrl +)");
            this->btn_fileRoot->UseVisualStyleBackColor = true;
            this->btn_fileRoot->Click += gcnew System::EventHandler(this, &MainForm::btn_fileRoot_Click);
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
            this->btn_randomize->Location = System::Drawing::Point(48, 4);
            this->btn_randomize->Name = L"btn_randomize";
            this->btn_randomize->Size = System::Drawing::Size(115, 25);
            this->btn_randomize->TabIndex = 7;
            this->btn_randomize->Text = L"Randomize List";
            this->toolTip1->SetToolTip(this->btn_randomize, L"(Ctrl R)");
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
            // btn_stop
            // 
            this->btn_stop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_stop->Font = (gcnew System::Drawing::Font(L"Segoe UI Emoji", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_stop->Location = System::Drawing::Point(377, 414);
            this->btn_stop->Name = L"btn_stop";
            this->btn_stop->Size = System::Drawing::Size(44, 40);
            this->btn_stop->TabIndex = 11;
            this->btn_stop->Text = L"⏹️";
            this->toolTip1->SetToolTip(this->btn_stop, L"Stop (S)");
            this->btn_stop->UseVisualStyleBackColor = true;
            this->btn_stop->Click += gcnew System::EventHandler(this, &MainForm::btn_stop_Click);
            // 
            // btn_prev
            // 
            this->btn_prev->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_prev->Font = (gcnew System::Drawing::Font(L"Segoe UI Emoji", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_prev->Location = System::Drawing::Point(277, 414);
            this->btn_prev->Name = L"btn_prev";
            this->btn_prev->Size = System::Drawing::Size(44, 40);
            this->btn_prev->TabIndex = 12;
            this->btn_prev->Text = L"⏮️";
            this->toolTip1->SetToolTip(this->btn_prev, L"Previous (P)");
            this->btn_prev->UseVisualStyleBackColor = true;
            this->btn_prev->Click += gcnew System::EventHandler(this, &MainForm::btn_prev_Click);
            // 
            // btn_next
            // 
            this->btn_next->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_next->Font = (gcnew System::Drawing::Font(L"Segoe UI Emoji", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_next->Location = System::Drawing::Point(427, 414);
            this->btn_next->Name = L"btn_next";
            this->btn_next->Size = System::Drawing::Size(44, 40);
            this->btn_next->TabIndex = 13;
            this->btn_next->Text = L"⏭️";
            this->toolTip1->SetToolTip(this->btn_next, L"Next (N)");
            this->btn_next->UseVisualStyleBackColor = true;
            this->btn_next->Click += gcnew System::EventHandler(this, &MainForm::btn_next_Click);
            // 
            // btn_pause
            // 
            this->btn_pause->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_pause->Font = (gcnew System::Drawing::Font(L"Segoe UI Emoji", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_pause->Location = System::Drawing::Point(327, 414);
            this->btn_pause->Name = L"btn_pause";
            this->btn_pause->Size = System::Drawing::Size(44, 40);
            this->btn_pause->TabIndex = 14;
            this->btn_pause->Text = L"▶️";
            this->toolTip1->SetToolTip(this->btn_pause, L"Pause/Play (Space)");
            this->btn_pause->UseVisualStyleBackColor = true;
            this->btn_pause->Click += gcnew System::EventHandler(this, &MainForm::btn_pause_Click);
            // 
            // btn_fullScreen
            // 
            this->btn_fullScreen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_fullScreen->Cursor = System::Windows::Forms::Cursors::SizeAll;
            this->btn_fullScreen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_fullScreen->Location = System::Drawing::Point(594, 414);
            this->btn_fullScreen->Name = L"btn_fullScreen";
            this->btn_fullScreen->Size = System::Drawing::Size(158, 40);
            this->btn_fullScreen->TabIndex = 15;
            this->btn_fullScreen->Text = L"Toggle Full Screen";
            this->toolTip1->SetToolTip(this->btn_fullScreen, L"(F)");
            this->btn_fullScreen->UseVisualStyleBackColor = true;
            this->btn_fullScreen->Click += gcnew System::EventHandler(this, &MainForm::btn_fullScreen_Click);
            // 
            // btn_debugMenu
            // 
            this->btn_debugMenu->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->btn_debugMenu->Font = (gcnew System::Drawing::Font(L"Consolas", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_debugMenu->ForeColor = System::Drawing::Color::Red;
            this->btn_debugMenu->Location = System::Drawing::Point(12, 414);
            this->btn_debugMenu->Name = L"btn_debugMenu";
            this->btn_debugMenu->Size = System::Drawing::Size(25, 40);
            this->btn_debugMenu->TabIndex = 16;
            this->btn_debugMenu->Text = L"!";
            this->btn_debugMenu->UseVisualStyleBackColor = true;
            this->btn_debugMenu->Click += gcnew System::EventHandler(this, &MainForm::btn_debugMenu_Click);
            // 
            // btn_clearList
            // 
            this->btn_clearList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->btn_clearList->Location = System::Drawing::Point(668, 4);
            this->btn_clearList->Name = L"btn_clearList";
            this->btn_clearList->Size = System::Drawing::Size(84, 25);
            this->btn_clearList->TabIndex = 17;
            this->btn_clearList->Text = L"Clear List";
            this->toolTip1->SetToolTip(this->btn_clearList, L"(Delete)");
            this->btn_clearList->UseVisualStyleBackColor = true;
            this->btn_clearList->Click += gcnew System::EventHandler(this, &MainForm::btn_clearList_Click);
            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1513, 462);
            this->Controls->Add(this->btn_clearList);
            this->Controls->Add(this->btn_debugMenu);
            this->Controls->Add(this->btn_fullScreen);
            this->Controls->Add(this->btn_pause);
            this->Controls->Add(this->btn_next);
            this->Controls->Add(this->btn_prev);
            this->Controls->Add(this->btn_stop);
            this->Controls->Add(this->axVLCPlugin21);
            this->Controls->Add(this->btn_randomize);
            this->Controls->Add(this->lstVw_files);
            this->Controls->Add(this->btn_fileRoot);
            this->Name = L"MainForm";
            this->Text = L"Video Randomizer";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axVLCPlugin21))->EndInit();
            this->ResumeLayout(false);

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

    private: System::Void SetEnabledForAllButtons(bool enable)
    {
        for each (System::Windows::Forms::Control ^ c in this->Controls)
        {
            System::Windows::Forms::Button^ btn = dynamic_cast<System::Windows::Forms::Button^>(c);
            if (btn != nullptr)
            {
                btn->Enabled = enable;
            }
        }
    }

    private: System::Void AddVideoFileNamesAndPathsToListView()
    {
        for (int i = 0; i < static_cast<int>(m_videoFiles->size()); i++)
        {
            System::String^ fileName = gcnew System::String(m_videoFiles->at(i).path().filename().string().c_str());
            System::String^ filePath = gcnew System::String(m_videoFiles->at(i).path().c_str());
            array<System::String^>^ row = gcnew array<System::String^>{fileName, filePath};
            this->m_listViewItem = gcnew Windows::Forms::ListViewItem(row);
            this->lstVw_files->Items->Add(this->m_listViewItem);
        }
    }

    private: System::Void AddToFileList(System::String^ folderPath)
    {
        std::string path = msclr::interop::marshal_as<std::string>(folderPath);
        try {
            for (const auto& entry : fs::recursive_directory_iterator(path, std::filesystem::directory_options::skip_permission_denied))
            {
                System::String^ ext = gcnew System::String(entry.path().extension().c_str());
                if (ContainsString(m_supportedVideoFileExtensions, ext)) // This skips any non-video files
                {
                    m_videoFiles->push_back(entry);
                }
            }
        }
        catch (const fs::filesystem_error& e) 
        {
            std::cerr << "Filesystem Error: " << e.what() << std::endl;
            System::Diagnostics::Debug::WriteLine("Filesystem Error: " + gcnew System::String(e.what()));

            std::cerr << "Path: " << e.path1().string() << std::endl; // Path associated with the error
            System::Diagnostics::Debug::WriteLine("Path: " + gcnew System::String(e.path1().c_str()));

            if (e.path2().empty() == false) 
            {
                std::cerr << "Path2: " << e.path2().string() << std::endl; // Optional second path
                System::Diagnostics::Debug::WriteLine("Path2: " + gcnew System::String(e.path2().c_str()));
            }

            std::cerr << "Error Code: " << e.code() << std::endl;
            System::Diagnostics::Debug::WriteLine("Error Code Message: " + gcnew System::String(e.code().message().c_str()));
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "General Exception: " << e.what() << std::endl;
            System::Diagnostics::Debug::WriteLine("General Exception: " + gcnew System::String(e.what()));
        }
    }

    private: System::Void EnqueueAllFromListViewToVLCPlaylist()
    {
        for each(System::Windows::Forms::ListViewItem ^ item in lstVw_files->Items)
        {
            Uri^ uri = gcnew Uri(item->SubItems[1]->Text);
            axVLCPlugin21->playlist->add(uri->AbsoluteUri, item->Text, nullptr);
        }
    }

    private: System::Void HighlightCurrentVLCItemInListView() // If it exists
    {
        if (lstVw_files->Items->Count == 0 || axVLCPlugin21->playlist->itemCount == 0 || !m_listViewMatchesVLCPlaylist) // Return if there's nothing to highlight or if there's a list mismatch
        {
            return;
        }
        else
        {
            lstVw_files->SelectedItems->Clear();
            lstVw_files->Items[axVLCPlugin21->playlist->currentItem]->Focused = true;
            lstVw_files->Items[axVLCPlugin21->playlist->currentItem]->Selected = true;
            lstVw_files->Items[axVLCPlugin21->playlist->currentItem]->EnsureVisible();
            lstVw_files->Select();
        }
    }

    private: System::Void PlayPause()
    {
        if (axVLCPlugin21->playlist->itemCount > 0)
        {
            if (axVLCPlugin21->playlist->isPlaying)
            {
                axVLCPlugin21->playlist->pause();
            }
            else
            {
                axVLCPlugin21->playlist->play();
            }
        }
        else if (this->lstVw_files->Items->Count > 0)
        {
            axVLCPlugin21->playlist->stop();
            axVLCPlugin21->playlist->clear();
            EnqueueAllFromListViewToVLCPlaylist();
            m_listViewMatchesVLCPlaylist = true;
            axVLCPlugin21->playlist->play();
        }
    }

    private: System::Void Stop()
    {
        axVLCPlugin21->playlist->stop();
    }

    private: System::Void Next()
    {
        axVLCPlugin21->playlist->next();
    }

    private: System::Void Previous()
    {
        axVLCPlugin21->playlist->prev();
    }

    private: System::Void ToggleFullScreen()
    {
        axVLCPlugin21->video->toggleFullscreen();
    }

    private: System::Void ClearListView()
    {
        System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show("Are you sure you want to clear the list? It will also clear the VLC playlist. This cannot be undone.", "Clear List", System::Windows::Forms::MessageBoxButtons::YesNo);
        if (result == System::Windows::Forms::DialogResult::Yes)
        {
            m_videoFiles->clear();
            lstVw_files->Items->Clear();
            if (axVLCPlugin21->playlist->isPlaying)
            {
                Stop();
            }
            axVLCPlugin21->playlist->clear();

            if (axVLCPlugin21->playlist->itemCount > 0)
            {
                m_listViewMatchesVLCPlaylist = false;
            }
            else if (axVLCPlugin21->playlist->itemCount == 0)
            {
                m_listViewMatchesVLCPlaylist = true; // Both lists are empty so they match again
            }
        }
    }

    private: System::Void RandomizeListView()
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_videoFiles->begin(), m_videoFiles->end(), g);
        lstVw_files->SelectedItems->Clear();
        lstVw_files->Items->Clear();
        AddVideoFileNamesAndPathsToListView();

        if (axVLCPlugin21->playlist->itemCount > 0)
        {
            m_listViewMatchesVLCPlaylist = false; // The list may have the same contents but the order is different, so it no longer matches the VLC playlist
        }
    }

    private: System::Void PromptAddToListView()
    {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        IFileOpenDialog* pFileOpen = nullptr;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileOpen));
        pFileOpen->SetOptions(FOS_PICKFOLDERS | FOS_ALLOWMULTISELECT);

        if (SUCCEEDED(hr))
        {
            if (SUCCEEDED(pFileOpen->Show(NULL)))
            {
                IShellItemArray* pItems;
                if (SUCCEEDED(pFileOpen->GetResults(&pItems)))
                {
                    DWORD dwNumItems = 0;
                    pItems->GetCount(&dwNumItems);
                    for (DWORD i = 0; i < dwNumItems; i++)
                    {
                        IShellItem* pItem;
                        if (SUCCEEDED(pItems->GetItemAt(i, &pItem)))
                        {
                            LPWSTR lpszFilePath;
                            pItem->GetDisplayName(SIGDN_FILESYSPATH, &lpszFilePath);
                            AddToFileList(gcnew String(lpszFilePath));
                            CoTaskMemFree(lpszFilePath);
                            pItem->Release();
                        }
                    }
                    pItems->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();

        std::sort(m_videoFiles->begin(), m_videoFiles->end());

        AddVideoFileNamesAndPathsToListView();

        if (axVLCPlugin21->playlist->itemCount > 0)
        {
            m_listViewMatchesVLCPlaylist = false; // Videos are getting added while VLC already has a playlist causing a mismatch
        }
    }

    private: System::Void btn_fileRoot_Click(System::Object^ sender, System::EventArgs^ e)
    {
        PromptAddToListView();
    }

    private: System::Void btn_randomize_Click(System::Object^ sender, System::EventArgs^ e)
    {
        RandomizeListView();
    }

    private: System::Void btn_stop_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Stop();
    }

    private: System::Void btn_next_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Next();
    }

    private: System::Void btn_prev_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Previous();
    }

    private: System::Void btn_pause_Click(System::Object^ sender, System::EventArgs^ e)
    {
        PlayPause();
    }

    private: System::Void btn_fullScreen_Click(System::Object^ sender, System::EventArgs^ e)
    {
        ToggleFullScreen();
    }

    private: System::Void btn_clearList_Click(System::Object^ sender, System::EventArgs^ e)
    {
        ClearListView();
    }

    private: System::Void btn_debugMenu_Click(System::Object^ sender, System::EventArgs^ e) 
    {
#ifdef _DEBUG
        System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show("Run the PopulateFileList Test?", "PopulateFileList", System::Windows::Forms::MessageBoxButtons::YesNo);
        
        if (result == System::Windows::Forms::DialogResult::Yes)
        {
            UnitTestPopulateFileList();
        }
#endif // _DEBUG
    }
#ifdef _DEBUG
    private: System::Void UnitTestPopulateFileList()
    {
        SetEnabledForAllButtons(false);
        m_videoFiles->clear();
        AddToFileList("C:\\"); // This is a pretty good stress test since it has a lot of files and folders, and some permission denied folders
        System::Windows::Forms::MessageBox::Show("Scanned C: and found " + m_videoFiles->size() + " videos.", "PopulateFileList Reuslts");
        SetEnabledForAllButtons(true);
        AddVideoFileNamesAndPathsToListView();
    }
#endif // _DEBUG
};
}
