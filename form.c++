#pragma once
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>

// Function to process the file content
struct Result {
    int space;
    int stop;
};

Result detect(const std::string& text) {
    Result s1 = {0, 0};
    for (char ch : text) {
        if (ch == ' ') s1.space++;
        if (ch == '.') s1.stop++;
    }
    return s1;
}

namespace form01 {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace msclr::interop;

    public ref class MainForm : public Form {
    public:
        MainForm() {
            InitializeComponent();
        }

    private:
        Button^ btnRemovePunctuation;
        Button^ btnStart;
        TextBox^ txtFilePath;
        Label^ lblResult;

    private:
        void InitializeComponent() {
            // Initialize Components
            this->btnRemovePunctuation = gcnew Button();
            this->btnStart = gcnew Button();
            this->txtFilePath = gcnew TextBox();
            this->lblResult = gcnew Label();

            // Main Form Properties
            this->Text = "Punctuation Remover";
            this->Size = System::Drawing::Size(400, 300);

            // Button: Remove Punctuation
            this->btnRemovePunctuation->Text = "Punctuation Remove";
            this->btnRemovePunctuation->Location = Point(50, 50);
            this->btnRemovePunctuation->Click += gcnew EventHandler(this, &MainForm::btnRemovePunctuation_Click);
            this->Controls->Add(this->btnRemovePunctuation);
        }

        // Event Handler: Punctuation Remove Button Click
        void btnRemovePunctuation_Click(Object^ sender, EventArgs^ e) {
            // Create a new layout for file input and processing
            this->Controls->Clear();

            // File Path Input
            Label^ lblFilePath = gcnew Label();
            lblFilePath->Text = "Input File Path:";
            lblFilePath->Location = Point(20, 20);
            this->Controls->Add(lblFilePath);

            this->txtFilePath->Location = Point(20, 50);
            this->txtFilePath->Width = 300;
            this->Controls->Add(this->txtFilePath);

            // Start Button
            this->btnStart->Text = "Start";
            this->btnStart->Location = Point(20, 90);
            this->btnStart->Click += gcnew EventHandler(this, &MainForm::btnStart_Click);
            this->Controls->Add(this->btnStart);

            // Result Label
            this->lblResult->Location = Point(20, 130);
            this->lblResult->Size = Drawing::Size(300, 50);
            this->Controls->Add(this->lblResult);
        }

        // Event Handler: Start Button Click
        void btnStart_Click(Object^ sender, EventArgs^ e) {
            String^ filePath = this->txtFilePath->Text;

            // Validate file
            if (!File::Exists(filePath)) {
                MessageBox::Show("File not found. Please check the path and try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Read file content
            std::ifstream file(marshal_as<std::string>(filePath));
            std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            // Process text
            Result result = detect(text);

            // Display result
            this->lblResult->Text = "Total spaces: " + result.space + "\nTotal full stops: " + result.stop;
        }
    };
}
