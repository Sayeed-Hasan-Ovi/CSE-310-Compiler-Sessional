#include <bits/stdc++.h>
using namespace std;

int dataLine = 3;
void init_assembly_file(string fileName){
    ofstream writeFile;
    writeFile.open(fileName.c_str());
    string code = "";
    code += ".MODEL SMALL\n";
    code += ".STACK 400H\t;4KB stack\n";
    code += ".DATA\n";
    code += ".CODE\n";
    writeFile<<code;
    writeFile.close();
}



void writeAt(string fileName, string code, int lineNo)
{
    string tempFile = "temp.asm";
    ofstream writeFile;
    writeFile.open(tempFile.c_str());
    ifstream readFile;
    readFile.open(fileName.c_str(),ios_base::in);
    string line;
    int lineCount = 0;
    bool hasWritten = false;

    while (getline(readFile, line))
    {
        if (lineCount == lineNo)
        {
            writeFile << code << '\n';
            hasWritten = true;
            cout<<code<<"\n";
        }
        writeFile << line << '\n';
        cout<<line<<"\n";
        lineCount++;
    }

    if (!hasWritten)
    {
        writeFile << code << '\n';
        hasWritten = true;
    }

    readFile.close();
    writeFile.close();
    int status = remove(fileName.c_str());
    if (status)
        std::cout << "Error deleting file" << std::endl;
    status = rename(tempFile.c_str(),fileName.c_str());
    if (status)
        std::cout << "Error renaming file" << std::endl;
}

int main()
{

    init_assembly_file("code.asm");
    writeAt("code.asm", "abc def",3);
}