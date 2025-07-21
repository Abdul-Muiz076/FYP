#pragma once
#include <fstream>
#include <string>
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <cstring>  // For strcpy
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used Windows components
#include <Windows.h>

namespace formcombine {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::IO;
    using namespace System::Drawing;

    public ref class CombinForm : public System::Windows::Forms::Form
    {
    public:
        CombinForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CombinForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ techniqueButton; // Show Techniques Button
        System::Windows::Forms::ListBox^ techniqueList; // Technique List
        System::Windows::Forms::Button^ chooseFileButton; // File Selection Button
        System::Windows::Forms::Button^ cleanButton; // Apply Technique Button
        System::Windows::Forms::RichTextBox^ outputBox; // Output Display Box
        System::ComponentModel::Container^ components;
        String^ loadedFileContent;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->techniqueButton = (gcnew System::Windows::Forms::Button());
            this->techniqueList = (gcnew System::Windows::Forms::ListBox());
            this->chooseFileButton = (gcnew System::Windows::Forms::Button());
            this->cleanButton = (gcnew System::Windows::Forms::Button());
            this->outputBox = (gcnew System::Windows::Forms::RichTextBox());
            this->SuspendLayout();

            // Techniques Button
            this->techniqueButton->BackColor = System::Drawing::Color::Cyan;
            this->techniqueButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold));
            this->techniqueButton->ForeColor = System::Drawing::Color::Red;
            this->techniqueButton->Location = System::Drawing::Point(44, 30);
            this->techniqueButton->Name = L"techniqueButton";
            this->techniqueButton->Size = System::Drawing::Size(323, 50);
            this->techniqueButton->TabIndex = 0;
            this->techniqueButton->Text = L"Techniques";
            this->techniqueButton->UseVisualStyleBackColor = false;
            this->techniqueButton->Click += gcnew System::EventHandler(this, &CombinForm::techniqueButton_Click);

            // ListBox for Techniques
            this->techniqueList->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->techniqueList->FormattingEnabled = true;
            this->techniqueList->ItemHeight = 19;
            this->techniqueList->Location = System::Drawing::Point(44, 86);
            this->techniqueList->Name = L"techniqueList";
            this->techniqueList->Size = System::Drawing::Size(323, 156);
            this->techniqueList->TabIndex = 1;
            this->techniqueList->Visible = false;

            // Choose File Button
            this->chooseFileButton->BackColor = System::Drawing::Color::LightBlue;
            this->chooseFileButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
            this->chooseFileButton->Location = System::Drawing::Point(44, 260);
            this->chooseFileButton->Name = L"chooseFileButton";
            this->chooseFileButton->Size = System::Drawing::Size(323, 35);
            this->chooseFileButton->TabIndex = 2;
            this->chooseFileButton->Text = L"Choose File";
            this->chooseFileButton->UseVisualStyleBackColor = false;
            this->chooseFileButton->Visible = false;
            this->chooseFileButton->Click += gcnew System::EventHandler(this, &CombinForm::chooseFileButton_Click);

            // Apply Clean Button
            this->cleanButton->BackColor = System::Drawing::Color::LightGreen;
            this->cleanButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
            this->cleanButton->Location = System::Drawing::Point(44, 310);
            this->cleanButton->Name = L"cleanButton";
            this->cleanButton->Size = System::Drawing::Size(323, 35);
            this->cleanButton->TabIndex = 3;
            this->cleanButton->Text = L"Clean";
            this->cleanButton->UseVisualStyleBackColor = false;
            this->cleanButton->Visible = false;
            this->cleanButton->Click += gcnew System::EventHandler(this, &CombinForm::cleanButton_Click);

            // RichTextBox for Output
            this->outputBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->outputBox->Location = System::Drawing::Point(44, 360);
            this->outputBox->Name = L"outputBox";
            this->outputBox->Size = System::Drawing::Size(323, 120);
            this->outputBox->TabIndex = 4;
            this->outputBox->Visible = false;
            this->outputBox->ReadOnly = true;
            this->outputBox->Multiline = true;
            this->outputBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Both;

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->ClientSize = System::Drawing::Size(450, 500);
            this->Controls->Add(this->techniqueButton);
            this->Controls->Add(this->techniqueList);
            this->Controls->Add(this->chooseFileButton);
            this->Controls->Add(this->cleanButton);
            this->Controls->Add(this->outputBox);
            this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->Name = L"MainForm";
            this->Text = L"Text Preprocessing Techniques";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        // Show Techniques
        System::Void techniqueButton_Click(System::Object^ sender, System::EventArgs^ e) {
            array<String^>^ techniques = { L"Punctuation Removal", L"Lowercasing", L"Stopword Removal", L"Tokenization", L"Remove Accents" , L"Remove HTML tags"};
            this->techniqueList->Items->Clear();
            this->techniqueList->Items->AddRange(techniques);
            this->techniqueList->Visible = true;
            this->chooseFileButton->Visible = true;
        }

        // Choose File
        System::Void chooseFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = L"Text Files|*.txt";
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                this->loadedFileContent = File::ReadAllText(openFileDialog->FileName);
                this->cleanButton->Visible = true;
            }
        }


        // Helper Methods
// Updated RemovePunctuation function
    private:
        // Function to remove punctuation and count spaces/full stops
        System::String^ RemovePunctuation(System::String^ input) {
            int spaceCount = 0;
            int stopCount = 0;
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

            for each(wchar_t c in input) {
                if (c == ' ') {
                    spaceCount++;
                }
                if (c == '.') {
                    stopCount++;
                }
                // Append only non-punctuation characters
                if (!Char::IsPunctuation(c) || c == ' ') {
                    cleanedText->Append(c);
                }
            }

            // Display counts in the output box
            this->outputBox->AppendText(L"\nTotal spaces: " + spaceCount + L"\n");
            this->outputBox->AppendText(L"Total full stops: " + stopCount + L"\n");

            return cleanedText->ToString();
        }
        // Function to demonstrate stopword removal (case-insensitive)
        System::String^ RemoveStopwords(System::String^ input) {
            array<String^>^ stopwords = { L"the", L"and", L"is", L"to", L"in" , L"but" , L"of" , L"on" , L"what" , L"how" , L"will" , L"or" , L"a" , L"or" , L"at" }; // Extend as needed
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();
            array<String^>^ words = input->Split(' ');

            for each(String ^ word in words) {
                // Convert both the word and stopwords to lowercase for comparison
                String^ lowerWord = word->ToLower();
                if (Array::IndexOf(stopwords, lowerWord) == -1) {
                    cleanedText->Append(word + " ");
                }
            }
            return cleanedText->ToString()->TrimEnd();
        }
        System::String^ LowercaseText(System::String^ input) {
            return input->ToLower();
        }

        // Function for tokenization in C++/CLI

     private:
         void TokenizeText(System::String^ text) {
             // Clear previous output
             this->outputBox->Clear();

             // Split input text into words using spaces and punctuation as delimiters
             array<wchar_t>^ delimiters = gcnew array<wchar_t>{ ' ', '\n', '\t', '.', ',', '?', '!', '(', ')', ';' };

             array<System::String^>^ tokens = text->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

             // Display each token
             for each (System::String ^ token in tokens) {
                 this->outputBox->AppendText("Token: " + token + "\n");
             }
         }

         // Accents Removal Function
         System::String^ RemoveAccents(System::String^ input) {
             System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

             for each (wchar_t c in input) {
                 switch (c) {
                 case L'é': case L'è': case L'ë': case L'ê':
                     cleanedText->Append(L"e");
                     break;
                 case L'à': case L'á': case L'ä': case L'â':
                     cleanedText->Append(L"a");
                     break;
                 case L'í': case L'ì': case L'ï': case L'î':
                     cleanedText->Append(L"i");
                     break;
                 case L'ó': case L'ò': case L'ö': case L'ô':
                     cleanedText->Append(L"o");
                     break;
                 case L'ú': case L'ù': case L'ü': case L'û':
                     cleanedText->Append(L"u");
                     break;
                 case L'ç':
                     cleanedText->Append(L"c");
                     break;
                 case L'ñ':
                     cleanedText->Append(L"n");
                     break;
                 case L'Á': case L'À': case L'Ä': case L'Â':
                     cleanedText->Append(L"A");
                     break;
                 case L'É': case L'È': case L'Ë': case L'Ê':
                     cleanedText->Append(L"E");
                     break;
                 case L'Í': case L'Ì': case L'Ï': case L'Î':
                     cleanedText->Append(L"I");
                     break;
                 case L'Ó': case L'Ò': case L'Ö': case L'Ô':
                     cleanedText->Append(L"O");
                     break;
                 case L'Ú': case L'Ù': case L'Ü': case L'Û':
                     cleanedText->Append(L"U");
                     break;
                 case L'Ç':
                     cleanedText->Append(L"C");
                     break;
                 case L'Ñ':
                     cleanedText->Append(L"N");
                     break;
                 default:
                     cleanedText->Append(c);
                     break;
                 }
             }

             return cleanedText->ToString();  // Ensure the string is returned
         }

         private:
             // Function to remove HTML tags
             System::String^ RemoveHTMLTags(System::String^ input) {
                 System::Text::RegularExpressions::Regex^ htmlTagRegex = gcnew System::Text::RegularExpressions::Regex(L"<.*?>");
                 return htmlTagRegex->Replace(input, L"");
             }



         // Apply Technique
         System::Void cleanButton_Click(System::Object^ sender, System::EventArgs^ e) {
             if (String::IsNullOrEmpty(this->loadedFileContent)) {
                 MessageBox::Show(L"No file loaded. Please load a file first.", L"Error");
                 return;
             }

             if (this->techniqueList->SelectedItem == nullptr) {
                 MessageBox::Show(L"Please select a technique.", L"Error");
                 return;
             }

             String^ selectedTechnique = this->techniqueList->SelectedItem->ToString();
             String^ result = this->loadedFileContent;

             if (selectedTechnique == L"Punctuation Removal") {
                 result = RemovePunctuation(result); // Call the RemovePunctuation function
             }
             else if (selectedTechnique == L"Stopword Removal") {
                 result = RemoveStopwords(this->loadedFileContent);
             }
             else if (selectedTechnique == L"Lowercasing") {
                 result = LowercaseText(result); // Call the LowercaseText function
             }
             else if (selectedTechnique == L"Tokenization") {
                 // Call TokenizeText function when Tokenization is selected
                 TokenizeText(result); // Tokenize based on space (adjust the delimiter as needed)
                 return;
             }
             else if (selectedTechnique == L"Remove Accents") {
                 result = RemoveAccents(result); // Call RemoveAccents and store the result
             }

             else if (selectedTechnique == L"Remove HTML tags") {
                 result = RemoveHTMLTags(result);
             }
             
            

             this->outputBox->Text = result; // Display the result in the output box
             this->outputBox->Visible = true;
         }

    };
}


Second one....................................................................
..............................................................................
.................................................................................
#pragma once
#include <fstream>
#include <string>
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <cstring>  // For strcpy
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used Windows components
#include <Windows.h>

namespace formcombine {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::IO;
    using namespace System::Drawing;

    public ref class CombinForm : public System::Windows::Forms::Form
    {
    public:
        CombinForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CombinForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ techniqueButton; // Show Techniques Button
        System::Windows::Forms::ListBox^ techniqueList; // Technique List
        System::Windows::Forms::Button^ chooseFileButton; // File Selection Button
        System::Windows::Forms::Button^ cleanButton; // Apply Technique Button
        System::Windows::Forms::RichTextBox^ outputBox; // Output Display Box
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ applyAllTechniquesButton;
        String^ loadedFileContent;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            // Adjust form size
            this->Width = 600;  // Increased width
            this->Height = 700; // Increased height
            this->techniqueButton = (gcnew System::Windows::Forms::Button());
            this->applyAllTechniquesButton = (gcnew System::Windows::Forms::Button());
            this->techniqueList = (gcnew System::Windows::Forms::ListBox());
            this->chooseFileButton = (gcnew System::Windows::Forms::Button());
            this->cleanButton = (gcnew System::Windows::Forms::Button());
            this->outputBox = (gcnew System::Windows::Forms::RichTextBox());
            this->SuspendLayout();

            // Techniques Button
            this->techniqueButton->BackColor = System::Drawing::Color::Cyan;
            this->techniqueButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold));
            this->techniqueButton->ForeColor = System::Drawing::Color::Red;
            this->techniqueButton->Location = System::Drawing::Point(44, 30);
            this->techniqueButton->Name = L"techniqueButton";
            this->techniqueButton->Size = System::Drawing::Size(323, 50);
            this->techniqueButton->TabIndex = 0;
            this->techniqueButton->Text = L"Techniques";
            this->techniqueButton->UseVisualStyleBackColor = false;

            this->techniqueButton->Click += gcnew System::EventHandler(this, &CombinForm::techniqueButton_Click);

            // In the InitializeComponent method
            this->applyAllTechniquesButton = (gcnew System::Windows::Forms::Button());
            this->applyAllTechniquesButton->BackColor = System::Drawing::Color::Orange;
            this->applyAllTechniquesButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
            this->applyAllTechniquesButton->ForeColor = System::Drawing::Color::White;
            this->applyAllTechniquesButton->Location = System::Drawing::Point(44, 420);
            this->applyAllTechniquesButton->Name = L"applyAllTechniquesButton";
            this->applyAllTechniquesButton->Size = System::Drawing::Size(323, 35);
            this->applyAllTechniquesButton->TabIndex = 5;
            this->applyAllTechniquesButton->Text = L"Apply All Techniques";
            this->applyAllTechniquesButton->UseVisualStyleBackColor = false;
            this->applyAllTechniquesButton->Visible = true; // Ensure button visibility
            this->applyAllTechniquesButton->Click += gcnew System::EventHandler(this,&CombinForm::applyAllTechniquesButton_Click);

            // Add the button to the Form
            this->Controls->Add(this->applyAllTechniquesButton);

        


            // ListBox for Techniques
            this->techniqueList->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->techniqueList->FormattingEnabled = true;
            this->techniqueList->ItemHeight = 19;
            this->techniqueList->Location = System::Drawing::Point(44, 86);
            this->techniqueList->Name = L"techniqueList";
            this->techniqueList->Size = System::Drawing::Size(323, 156);
            this->techniqueList->TabIndex = 1;
            this->techniqueList->Visible = false;

            // Choose File Button
            this->chooseFileButton->BackColor = System::Drawing::Color::LightBlue;
            this->chooseFileButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
            this->chooseFileButton->Location = System::Drawing::Point(44, 260);
            this->chooseFileButton->Name = L"chooseFileButton";
            this->chooseFileButton->Size = System::Drawing::Size(323, 35);
            this->chooseFileButton->TabIndex = 2;
            this->chooseFileButton->Text = L"Choose File";
            this->chooseFileButton->UseVisualStyleBackColor = false;
            this->chooseFileButton->Visible = false;
            this->chooseFileButton->Click += gcnew System::EventHandler(this, &CombinForm::chooseFileButton_Click);

            // Apply Clean Button
            this->cleanButton->BackColor = System::Drawing::Color::LightGreen;
            this->cleanButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
            this->cleanButton->Location = System::Drawing::Point(44, 310);
            this->cleanButton->Name = L"cleanButton";
            this->cleanButton->Size = System::Drawing::Size(323, 35);
            this->cleanButton->TabIndex = 3;
            this->cleanButton->Text = L"Clean";
            this->cleanButton->UseVisualStyleBackColor = false;
            this->cleanButton->Visible = false;
            this->cleanButton->Click += gcnew System::EventHandler(this, &CombinForm::cleanButton_Click);

            // RichTextBox for Output
            this->outputBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->outputBox->Location = System::Drawing::Point(44, 360);
            this->outputBox->Name = L"outputBox";
            this->outputBox->Size = System::Drawing::Size(323, 120);
            this->outputBox->TabIndex = 4;
            this->outputBox->Visible = false;
            this->outputBox->ReadOnly = true;
            this->outputBox->Multiline = true;
            this->outputBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Both;

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 19);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->ClientSize = System::Drawing::Size(450, 500);
            this->Controls->Add(this->techniqueButton);
            this->Controls->Add(this->techniqueList);
            this->Controls->Add(this->chooseFileButton);
            this->Controls->Add(this->cleanButton);
            this->Controls->Add(this->outputBox);
            this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12));
            this->Name = L"MainForm";
            this->Text = L"Text Preprocessing Techniques";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        // Show Techniques
        System::Void techniqueButton_Click(System::Object^ sender, System::EventArgs^ e) {
            array<String^>^ techniques = { L"Punctuation Removal", L"Lowercasing", L"Stopword Removal", L"Tokenization", L"Remove Accents" , L"Remove HTML tags"};
            this->techniqueList->Items->Clear();
            this->techniqueList->Items->AddRange(techniques);
            this->techniqueList->Visible = true;
            this->chooseFileButton->Visible = true;
        }
        // Apply All Techniques Button Click Event
       System::Void applyAllTechniquesButton_Click(System::Object^ sender, System::EventArgs^ e) {
            ApplyAllTechniques();
        }


        // Choose File
        System::Void chooseFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = L"Text Files|*.txt";
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                this->loadedFileContent = File::ReadAllText(openFileDialog->FileName);
                this->cleanButton->Visible = true;
            }
        }


        // Helper Methods
// Updated RemovePunctuation function
    private:
        // Function to remove punctuation and count spaces/full stops
        System::String^ RemovePunctuation(System::String^ input) {
            int spaceCount = 0;
            int stopCount = 0;
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

            for each(wchar_t c in input) {
                if (c == ' ') {
                    spaceCount++;
                }
                if (c == '.') {
                    stopCount++;
                }
                // Append only non-punctuation characters
                if (!Char::IsPunctuation(c) || c == ' ') {
                    cleanedText->Append(c);
                }
            }

            // Display counts in the output box
            this->outputBox->AppendText(L"\nTotal spaces: " + spaceCount + L"\n");
            this->outputBox->AppendText(L"Total full stops: " + stopCount + L"\n");

            return cleanedText->ToString();
        }
        // Function to demonstrate stopword removal (case-insensitive)
        System::String^ RemoveStopwords(System::String^ input) {
            array<String^>^ stopwords = { L"the", L"and", L"is", L"to", L"in" , L"but" , L"of" , L"on" , L"what" , L"how" , L"will" , L"or" , L"a" , L"or" , L"at" }; // Extend as needed
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();
            array<String^>^ words = input->Split(' ');

            for each(String ^ word in words) {
                // Convert both the word and stopwords to lowercase for comparison
                String^ lowerWord = word->ToLower();
                if (Array::IndexOf(stopwords, lowerWord) == -1) {
                    cleanedText->Append(word + " ");
                }
            }
            return cleanedText->ToString()->TrimEnd();
        }
        System::String^ LowercaseText(System::String^ input) {
            return input->ToLower();
        }

        // Function for tokenization in C++/CLI

     private:
         void TokenizeText(System::String^ text) {
             // Clear previous output
             this->outputBox->Clear();

             // Split input text into words using spaces and punctuation as delimiters
             array<wchar_t>^ delimiters = gcnew array<wchar_t>{ ' ', '\n', '\t', '.', ',', '?', '!', '(', ')', ';' };

             array<System::String^>^ tokens = text->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

             // Display each token
             for each (System::String ^ token in tokens) {
                 this->outputBox->AppendText("Token: " + token + "\n");
             }
         }

         // Accents Removal Function
         System::String^ RemoveAccents(System::String^ input) {
             System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

             for each (wchar_t c in input) {
                 switch (c) {
                 case L'é': case L'è': case L'ë': case L'ê':
                     cleanedText->Append(L"e");
                     break;
                 case L'à': case L'á': case L'ä': case L'â':
                     cleanedText->Append(L"a");
                     break;
                 case L'í': case L'ì': case L'ï': case L'î':
                     cleanedText->Append(L"i");
                     break;
                 case L'ó': case L'ò': case L'ö': case L'ô':
                     cleanedText->Append(L"o");
                     break;
                 case L'ú': case L'ù': case L'ü': case L'û':
                     cleanedText->Append(L"u");
                     break;
                 case L'ç':
                     cleanedText->Append(L"c");
                     break;
                 case L'ñ':
                     cleanedText->Append(L"n");
                     break;
                 case L'Á': case L'À': case L'Ä': case L'Â':
                     cleanedText->Append(L"A");
                     break;
                 case L'É': case L'È': case L'Ë': case L'Ê':
                     cleanedText->Append(L"E");
                     break;
                 case L'Í': case L'Ì': case L'Ï': case L'Î':
                     cleanedText->Append(L"I");
                     break;
                 case L'Ó': case L'Ò': case L'Ö': case L'Ô':
                     cleanedText->Append(L"O");
                     break;
                 case L'Ú': case L'Ù': case L'Ü': case L'Û':
                     cleanedText->Append(L"U");
                     break;
                 case L'Ç':
                     cleanedText->Append(L"C");
                     break;
                 case L'Ñ':
                     cleanedText->Append(L"N");
                     break;
                 default:
                     cleanedText->Append(c);
                     break;
                 }
             }

             return cleanedText->ToString();  // Ensure the string is returned
         }

         private:
             // Function to remove HTML tags
             System::String^ RemoveHTMLTags(System::String^ input) {
                 System::Text::RegularExpressions::Regex^ htmlTagRegex = gcnew System::Text::RegularExpressions::Regex(L"<.*?>");
                 return htmlTagRegex->Replace(input, L"");
             }



         // Apply Technique
         System::Void cleanButton_Click(System::Object^ sender, System::EventArgs^ e) {
             if (String::IsNullOrEmpty(this->loadedFileContent)) {
                 MessageBox::Show(L"No file loaded. Please load a file first.", L"Error");
                 return;
             }

             if (this->techniqueList->SelectedItem == nullptr) {
                 MessageBox::Show(L"Please select a technique.", L"Error");
                 return;
             }

             String^ selectedTechnique = this->techniqueList->SelectedItem->ToString();
             String^ result = this->loadedFileContent;

             if (selectedTechnique == L"Punctuation Removal") {
                 result = RemovePunctuation(result); // Call the RemovePunctuation function
             }
             else if (selectedTechnique == L"Stopword Removal") {
                 result = RemoveStopwords(this->loadedFileContent);
             }
             else if (selectedTechnique == L"Lowercasing") {
                 result = LowercaseText(result); // Call the LowercaseText function
             }
             else if (selectedTechnique == L"Tokenization") {
                 // Call TokenizeText function when Tokenization is selected
                 TokenizeText(result); // Tokenize based on space (adjust the delimiter as needed)
                 return;
             }
             else if (selectedTechnique == L"Remove Accents") {
                 result = RemoveAccents(result); // Call RemoveAccents and store the result
             }

             else if (selectedTechnique == L"Remove HTML tags") {
                 result = RemoveHTMLTags(result);
             }
             
            

             this->outputBox->Text = result; // Display the result in the output box
             this->outputBox->Visible = true;
         }
         // Function to apply all techniques sequentially
         System::Void ApplyAllTechniques() {
             if (String::IsNullOrEmpty(this->loadedFileContent)) {
                 MessageBox::Show(L"No file loaded. Please load a file first.", L"Error");
                 return;
             }

             String^ result = this->loadedFileContent;

             // Apply techniques in a logical sequence
             result = RemoveHTMLTags(result);       // Remove HTML tags first
             result = LowercaseText(result);        // Lowercase text
             result = RemoveAccents(result);        // Remove accents
             result = RemoveStopwords(result);      // Remove stopwords
             result = RemovePunctuation(result);    // Remove punctuation

             // Tokenize the cleaned text
             array<wchar_t>^ delimiters = gcnew array<wchar_t>{ ' ', '\n', '\t', '.', ',', '?', '!', '(', ')', ';' };
             array<System::String^>^ tokens = result->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

             // Display the cleaned text with tokens
             this->outputBox->Clear(); // Clear any previous text
             this->outputBox->AppendText(L"Final Cleaned Text:\n");
             this->outputBox->AppendText(result + L"\n\n");

             this->outputBox->AppendText(L"Tokens:\n");
             for each (System::String ^ token in tokens) {
                 this->outputBox->AppendText(token + L"\n");
             }

             this->outputBox->Visible = true;
         }

        
    };
}

............................................

#pragma once
#include <fstream>
#include <string>
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <cstring>  // For strcpy
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used Windows components
#include <Windows.h>
#include "Stemmtizer.h" // Include the C++ header file
#include <vector>
#include <sstream>
#include "Lemmatizer.h"

namespace formcombine {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::IO;
    using namespace System::Drawing;


    public ref class CombinForm : public System::Windows::Forms::Form
    {
    public:
        CombinForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CombinForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ techniqueButton; // Show Techniques Button
        System::Windows::Forms::CheckedListBox^ techniqueList; // Technique List (Now CheckedListBox)
        System::Windows::Forms::Button^ chooseFileButton; // File Selection Button
        System::Windows::Forms::Button^ cleanButton; // Apply Technique Button
        System::Windows::Forms::RichTextBox^ outputBox; // Output Display Box
        System::ComponentModel::Container^ components;
        System::Windows::Forms::Button^ applyAllTechniquesButton;
        String^ loadedFileContent;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            // Adjust the overall form size and color
            this->Width = 470;
            this->Height = 700;
            this->BackColor = System::Drawing::Color::FromArgb(240, 248, 255); // Light bluish (CSS: AliceBlue)



            // "Techniques" Button
            this->techniqueButton = gcnew System::Windows::Forms::Button();
            this->techniqueButton->BackColor = System::Drawing::Color::Cyan;
            this->techniqueButton->Font = (gcnew System::Drawing::Font(L"Verdana", 14, System::Drawing::FontStyle::Bold));
            this->techniqueButton->ForeColor = System::Drawing::Color::DarkRed;
            this->techniqueButton->Location = System::Drawing::Point(44, 30);
            this->techniqueButton->Size = System::Drawing::Size(323, 50);
            this->techniqueButton->Text = L"Techniques";
            this->techniqueButton->FlatStyle = FlatStyle::Flat; // Flat style for better aesthetics
            this->techniqueButton->FlatAppearance->BorderColor = System::Drawing::Color::DarkBlue;
            this->techniqueButton->FlatAppearance->BorderSize = 2;
            this->techniqueButton->Click += gcnew System::EventHandler(this, &CombinForm::techniqueButton_Click);
            this->techniqueButton->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

            // Techniques ListBox
            this->techniqueList = gcnew System::Windows::Forms::CheckedListBox();
            this->techniqueList->Font = (gcnew System::Drawing::Font(L"Verdana", 12));
            this->techniqueList->Location = System::Drawing::Point(44, 220);
            this->techniqueList->Size = System::Drawing::Size(323, 180);
            this->techniqueList->BackColor = System::Drawing::Color::WhiteSmoke;
            this->techniqueList->ForeColor = System::Drawing::Color::Black;
            this->techniqueList->Visible = false;
            this->techniqueList->CheckOnClick = true; // Allow the user to check multiple items
            this->techniqueList->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;


            // Choose File Button
            this->chooseFileButton = gcnew System::Windows::Forms::Button();
            this->chooseFileButton->BackColor = System::Drawing::Color::LightSkyBlue;
            this->chooseFileButton->Font = (gcnew System::Drawing::Font(L"Verdana", 12, System::Drawing::FontStyle::Bold));
            this->chooseFileButton->ForeColor = System::Drawing::Color::DarkSlateGray;
            this->chooseFileButton->Location = System::Drawing::Point(44, 160);
            this->chooseFileButton->Size = System::Drawing::Size(323, 40);
            this->chooseFileButton->Text = L"Choose File";
            this->chooseFileButton->FlatStyle = FlatStyle::Flat;
            this->chooseFileButton->FlatAppearance->BorderColor = System::Drawing::Color::SteelBlue;
            this->chooseFileButton->FlatAppearance->BorderSize = 1;
            this->chooseFileButton->Visible = false;
            this->chooseFileButton->Click += gcnew System::EventHandler(this, &CombinForm::chooseFileButton_Click);
            this->chooseFileButton->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

            // Clean Button
            this->cleanButton = gcnew System::Windows::Forms::Button();
            this->cleanButton->BackColor = System::Drawing::Color::LightGreen;
            this->cleanButton->Font = (gcnew System::Drawing::Font(L"Verdana", 12, System::Drawing::FontStyle::Bold));
            this->cleanButton->ForeColor = System::Drawing::Color::DarkOliveGreen;
            this->cleanButton->Location = System::Drawing::Point(44, 400);
            this->cleanButton->Size = System::Drawing::Size(323, 40);
            this->cleanButton->Text = L"Apply Technique";
            this->cleanButton->FlatStyle = FlatStyle::Flat;
            this->cleanButton->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;
            this->cleanButton->FlatAppearance->BorderSize = 1;
            this->cleanButton->Visible = false;
            this->cleanButton->Click += gcnew System::EventHandler(this, &CombinForm::cleanButton_Click);
            this->cleanButton->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

            // Apply All Techniques Button
            this->applyAllTechniquesButton = gcnew System::Windows::Forms::Button();
            this->applyAllTechniquesButton->BackColor = System::Drawing::Color::OrangeRed;
            this->applyAllTechniquesButton->Font = (gcnew System::Drawing::Font(L"Verdana", 12, System::Drawing::FontStyle::Bold));
            this->applyAllTechniquesButton->ForeColor = System::Drawing::Color::White;
            this->applyAllTechniquesButton->Location = System::Drawing::Point(44, 100);
            this->applyAllTechniquesButton->Size = System::Drawing::Size(323, 40);
            this->applyAllTechniquesButton->Text = L"Apply All Techniques";
            this->applyAllTechniquesButton->FlatStyle = FlatStyle::Flat;
            this->applyAllTechniquesButton->FlatAppearance->BorderColor = System::Drawing::Color::DarkRed;
            this->applyAllTechniquesButton->FlatAppearance->BorderSize = 1;
            this->applyAllTechniquesButton->Click += gcnew System::EventHandler(this, &CombinForm::applyAllTechniquesButton_Click);
            this->applyAllTechniquesButton->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;

            // Output RichTextBox
            this->outputBox = gcnew System::Windows::Forms::RichTextBox();
            this->outputBox->Location = System::Drawing::Point(44, 450);
            this->outputBox->Size = System::Drawing::Size(500, 200);
            this->outputBox->Font = gcnew System::Drawing::Font(L"Consolas", 11);
            this->outputBox->BackColor = System::Drawing::Color::Ivory;
            this->outputBox->ForeColor = System::Drawing::Color::DarkSlateGray;
            this->outputBox->ReadOnly = true;
            this->outputBox->BorderStyle = BorderStyle::FixedSingle;
            this->outputBox->Visible = false;
            this->outputBox->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom;

            // Adding all controls
            this->Controls->Add(this->techniqueButton);
            this->Controls->Add(this->techniqueList);
            this->Controls->Add(this->chooseFileButton);
            this->Controls->Add(this->cleanButton);
            this->Controls->Add(this->applyAllTechniquesButton);
            this->Controls->Add(this->outputBox);

            // Final Form Adjustments
            this->Text = L"Text Preprocessing Techniques";

        }
#pragma endregion

    private:
        // Show Techniques
        System::Void techniqueButton_Click(System::Object^ sender, System::EventArgs^ e) {
            array<String^>^ techniques = { L"Punctuation Removal", L"Lowercasing", L"Stopword Removal", L"Tokenization", L"Remove Accents" , L"Remove HTML tags" , L"Stemmintion", L"Lemmatization", L"Remove Digits and Symbols" };
            this->techniqueList->Items->Clear();
            this->techniqueList->Items->AddRange(techniques);
            this->techniqueList->Visible = true;
            this->chooseFileButton->Visible = true;
        }
        // Apply All Techniques Button Click Event
        System::Void applyAllTechniquesButton_Click(System::Object^ sender, System::EventArgs^ e) {
            ApplyAllTechniques();
        }


        // Choose File
        System::Void chooseFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = L"Text Files|*.txt";
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                this->loadedFileContent = File::ReadAllText(openFileDialog->FileName);
                this->cleanButton->Visible = true;
            }
        }


        // Helper Methods
        System::String^ RemoveDigitsAndSymbols(System::String^ input) {
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();
            for each (wchar_t c in input) {
                if (!Char::IsDigit(c) && c != '.' && c != L'π') { // Keep periods (.), since those are not numbers, also we dont want to remove pi sign from the code
                    cleanedText->Append(c);
                }
            }
            return cleanedText->ToString();
        }
        // Updated RemovePunctuation function
    private:
        // Function to remove punctuation and count spaces/full stops
        System::String^ RemovePunctuation(System::String^ input) {
            int spaceCount = 0;
            int stopCount = 0;
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

            for each (wchar_t c in input) {
                if (c == ' ') {
                    spaceCount++;
                }
                if (c == '.') {
                    stopCount++;
                }
                // Append only non-punctuation characters
                if (!Char::IsPunctuation(c) || c == ' ') {
                    cleanedText->Append(c);
                }
            }

            // Display counts in the output box
            this->outputBox->AppendText(L"\nTotal spaces: " + spaceCount + L"\n");
            this->outputBox->AppendText(L"Total full stops: " + stopCount + L"\n");

            return cleanedText->ToString();
        }
        // Function to demonstrate stopword removal (case-insensitive)
        System::String^ RemoveStopwords(System::String^ input) {
            array<String^>^ stopwords = { L"the", L"and", L"is", L"to", L"in" , L"but" , L"of" , L"on" , L"what" , L"how" , L"will" , L"or" ,
                L"a" , L"or" , L"at" , L"for" , L"with" , L"was" }; // Extend as needed
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();
            array<String^>^ words = input->Split(' ');

            for each (String ^ word in words) {
                // Convert both the word and stopwords to lowercase for comparison
                String^ lowerWord = word->ToLower();
                if (Array::IndexOf(stopwords, lowerWord) == -1) {
                    cleanedText->Append(word + " ");
                }
            }
            return cleanedText->ToString()->TrimEnd();
        }
        System::String^ LowercaseText(System::String^ input) {
            return input->ToLower();
        }

        // Function for tokenization in C++/CLI

    private:
        void TokenizeText(System::String^ text) {
            // Clear previous output
            this->outputBox->Clear();

            // Split input text into words using spaces and punctuation as delimiters
            array<wchar_t>^ delimiters = gcnew array<wchar_t>{ ' ', '\n', '\t', '.', ',', '?', '!', '(', ')', ';' };

            array<System::String^>^ tokens = text->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

            // Display each token
            for each (System::String ^ token in tokens) {
                this->outputBox->AppendText("Token: " + token + "\n");
            }
        }

        // Accents Removal Function
        System::String^ RemoveAccents(System::String^ input) {
            System::Text::StringBuilder^ cleanedText = gcnew System::Text::StringBuilder();

            for each (wchar_t c in input) {
                switch (c) {
                case L'é': case L'è': case L'ë': case L'ê':
                    cleanedText->Append(L"e");
                    break;
                case L'à': case L'á': case L'ä': case L'â':
                    cleanedText->Append(L"a");
                    break;
                case L'í': case L'ì': case L'ï': case L'î':
                    cleanedText->Append(L"i");
                    break;
                case L'ó': case L'ò': case L'ö': case L'ô':
                    cleanedText->Append(L"o");
                    break;
                case L'ú': case L'ù': case L'ü': case L'û':
                    cleanedText->Append(L"u");
                    break;
                case L'ç':
                    cleanedText->Append(L"c");
                    break;
                case L'ñ':
                    cleanedText->Append(L"n");
                    break;
                case L'Á': case L'À': case L'Ä': case L'Â':
                    cleanedText->Append(L"A");
                    break;
                case L'É': case L'È': case L'Ë': case L'Ê':
                    cleanedText->Append(L"E");
                    break;
                case L'Í': case L'Ì': case L'Ï': case L'Î':
                    cleanedText->Append(L"I");
                    break;
                case L'Ó': case L'Ò': case L'Ö': case L'Ô':
                    cleanedText->Append(L"O");
                    break;
                case L'Ú': case L'Ù': case L'Ü': case L'Û':
                    cleanedText->Append(L"U");
                    break;
                case L'Ç':
                    cleanedText->Append(L"C");
                    break;
                case L'Ñ':
                    cleanedText->Append(L"N");
                    break;
                default:
                    cleanedText->Append(c);
                    break;
                }
            }

            return cleanedText->ToString();  // Ensure the string is returned
        }

    private:
        // Function to remove HTML tags
        System::String^ RemoveHTMLTags(System::String^ input) {
            System::Text::RegularExpressions::Regex^ htmlTagRegex = gcnew System::Text::RegularExpressions::Regex(L"<.*?>");
            return htmlTagRegex->Replace(input, L"");
        }

    // C++/CLI wrapper for C++ Stemmtizer functions
        private:
            void  StemmtizeTextWrapper(System::String^ input) {

                // Convert System::String^ to std::string
                msclr::interop::marshal_context context;
                std::string inputString = context.marshal_as<std::string>(input);

                // Tokenize and lemmatize the text using C++ class
                std::vector<std::pair<std::string, std::string>> StemmtizeWords = Stemmtizer::tokenizeText(inputString, " \n");

                // Display results in the RichTextBox
                 std::stringstream ss;
                for (const auto& pair : StemmtizeWords) {
                     ss << pair.second << " ";
                }
                 std::string result = ss.str();
                // Trim string to remove trailing space before passing to the output
                if (!result.empty() && result.back() == ' ')
                {
                     result.pop_back(); // remove trailing space
                }

                 this->outputBox->Text = gcnew System::String(result.c_str());
            }

            // C++/CLI wrapper for C++ lemmatization functions
            private:
                void LemmatizeTextWrapper(System::String^ input) {
                    // Convert System::String^ to std::string
                    msclr::interop::marshal_context context;
                    std::string inputString = context.marshal_as<std::string>(input);

                    // Tokenize and lemmatize the text using C++ class
                    std::vector<std::pair<std::string, std::string>> lemmatizedWords = Lemmatizer::tokenizeText(inputString, " \n");


                    // Replace original text with lemmatized text
                    std::stringstream ss;
                    for (const auto& pair : lemmatizedWords) {
                        ss << pair.second << " ";
                    }
                    std::string result = ss.str();
                    // Trim string to remove trailing space before passing to the output
                    if (!result.empty() && result.back() == ' ')
                    {
                        result.pop_back(); // remove trailing space
                    }

                    this->outputBox->Text = gcnew System::String(result.c_str());

                }

        // Apply Technique
        System::Void cleanButton_Click(System::Object^ sender, System::EventArgs^ e) {
             if (String::IsNullOrEmpty(this->loadedFileContent)) {
                MessageBox::Show(L"No file loaded. Please load a file first.", L"Error");
                return;
            }


            String^ result = this->loadedFileContent;

           //Get all selected techniques
            for (int i = 0; i < techniqueList->CheckedItems->Count; i++)
              {
                String^ selectedTechnique = techniqueList->CheckedItems[i]->ToString();

                if (selectedTechnique == L"Punctuation Removal") {
                    result = RemovePunctuation(result); // Call the RemovePunctuation function
                }
                else if (selectedTechnique == L"Stopword Removal") {
                    result = RemoveStopwords(result);
                }
                else if (selectedTechnique == L"Lowercasing") {
                    result = LowercaseText(result); // Call the LowercaseText function
                }
                else if (selectedTechnique == L"Tokenization") {
                    // Call TokenizeText function when Tokenization is selected
                    TokenizeText(result); // Tokenize based on space (adjust the delimiter as needed)
                     continue; //Skip this function
                }
                else if (selectedTechnique == L"Remove Accents") {
                    result = RemoveAccents(result); // Call RemoveAccents and store the result
                }

                else if (selectedTechnique == L"Remove HTML tags") {
                    result = RemoveHTMLTags(result);
                }
                else if (selectedTechnique == L"Lemmatization") {
                    // Call the Lemmatization function
                    LemmatizeTextWrapper(result);
                    continue; //Skip this function
                }
                 else if (selectedTechnique == L"Stemmintion") {
                    // Call the Stemming function
                     StemmtizeTextWrapper(result);
                      continue; //Skip this function
                }
                else if (selectedTechnique == L"Remove Digits and Symbols") {
                    result = RemoveDigitsAndSymbols(result);
                }


              }


             this->outputBox->Text = result; // Display the result in the output box
              this->outputBox->Visible = true;


        }

        // Function to apply all techniques sequentially
        System::Void ApplyAllTechniques() {
            if (String::IsNullOrEmpty(this->loadedFileContent)) {
                MessageBox::Show(L"No file loaded. Please load a file first.", L"Error");
                return;
            }

            String^ result = this->loadedFileContent;

            // Apply techniques in a logical sequence
            result = RemoveHTMLTags(result);       // Remove HTML tags first
            result = RemoveAccents(result);        // Remove accents
            result = LowercaseText(result);        // Lowercase text
            result = RemovePunctuation(result);    // Remove punctuation
            result = RemoveStopwords(result);      // Remove stopwords

            // Call lemmatization
            msclr::interop::marshal_context context;
            std::string inputString = context.marshal_as<std::string>(result);
            // Tokenize and lemmatize the text using C++ class
            std::vector<std::pair<std::string, std::string>> lemmatizedWords = Lemmatizer::tokenizeText(inputString, " \n");

            // Replace original text with lemmatized text
            std::stringstream ss;
            for (const auto& pair : lemmatizedWords) {
                ss << pair.second << " ";
            }

            std::string lemmatizedResult = ss.str();
            // Trim string to remove trailing space before passing to the output
            if (!lemmatizedResult.empty() && lemmatizedResult.back() == ' ')
            {
                lemmatizedResult.pop_back(); // remove trailing space
            }
            result = gcnew System::String(lemmatizedResult.c_str());

            // Apply digit and symbol removal
            result = RemoveDigitsAndSymbols(result);

             // Display the cleaned text
            this->outputBox->Clear(); // Clear any previous text
            this->outputBox->AppendText(L"Final Cleaned Text:\n");
            this->outputBox->AppendText(result + L"\n");
             this->outputBox->Visible = true;

            // Tokenize the cleaned text
             array<wchar_t>^ delimiters = gcnew array<wchar_t>{ ' ', '\n', '\t', '.', ',', '?', '!', '(', ')', ';' };
            array<System::String^>^ tokens = result->Split(delimiters, System::StringSplitOptions::RemoveEmptyEntries);

           // Display the cleaned text with tokens
            this->outputBox->Clear(); // Clear any previous text
            this->outputBox->AppendText(L"Final Cleaned Text:\n");
             this->outputBox->AppendText(result + L"\n\n");

             this->outputBox->AppendText(L"Tokens:\n");
             for each (System::String ^ token in tokens) {
                // Filter out empty or whitespace-only tokens
                 if (!String::IsNullOrWhiteSpace(token)) {
                    this->outputBox->AppendText(L"Token: " + token + L"\n");
                 }
             }


            this->outputBox->Visible = true;
        }

    };
}
