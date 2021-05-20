#include <iostream>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <fstream>

using namespace std;

int main()
{
    SetConsoleTitleA("Corrupted Assignment Generator");
start:
    cout << "Enter file size in bytes: ";
    string fileSize;
    cin >> fileSize;
    fileSize.erase(remove(fileSize.begin(), fileSize.end(), ' '), fileSize.end());
    int size;
    try {
        size = stoi(fileSize);
    }
    catch (...) {
        cout << "Invalid size! Max size is 2,147,483,647 bytes \n";
        goto start;
    }
    if (size < 1) {
        cout << "Size must be greater than 0! \n";
        goto start;
    }
    string outputString = "";
    int lastGenProgress = -1;
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        char randomChar = rand() % 255;
        outputString += randomChar;
        int generationProgress = ((float)i / (float)size) * 100.f;
        if (generationProgress > lastGenProgress) {
            cout << "Generating string (" << generationProgress << "%)...\r";
            lastGenProgress = generationProgress;
        }
    }
    cout << "Generating string (100%)... \n";

    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = (LPCWSTR)L"Text File (*.txt)\0*.txt\0Word Document (*.docx)\0*.docx\0PowerPoint Presentation (*.pptx)\0*.pptx\0PDF (*.pdf)\0*.pdf\0Audio File (*.mp3)\0*.mp3\0Video File (*.mp4)\0*.mp4\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = (LPWSTR)szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = (LPCWSTR)L"";

    if (GetSaveFileName(&ofn)) {
        cout << "Saving to ";
        wcout << ofn.lpstrFile;
        cout << "\n";
        ofstream outputFile(ofn.lpstrFile);
        outputFile << outputString;
        outputFile.close();
    }
    return 0;
}
