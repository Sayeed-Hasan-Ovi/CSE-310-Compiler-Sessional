#ifndef UTIL_H
#define UTIL_H
#include <bits/stdc++.h>
#include "symbol_info.h"
using namespace std;

void printRuleInLog(ofstream& logout, int line, string rule) {
    logout<<"Line "<<line<<": "<<rule<<"\n\n";
}

void printCodeInLog(ofstream& logout, string code) {
    logout<<code<<"\n\n";
}



void printError(ofstream& errout, int line, string error) {
    errout<<"Error at line "<<line<<": "<<error<<"\n\n";
}

vector<string> split(string input, char delimiter) {
    istringstream ss(input);
    vector<string>output;
	string token;
	while(getline(ss, token, delimiter)) {
    	output.push_back(token);
	}
    return output;
}


bool isArray(string input) {
    if ((input.find("[") != string::npos) && (input.find("]") != string::npos))
        return true;
    return false;
}

string extractArrayName(string input) {
    istringstream ss(input);
    string arrayName;
    getline(ss, arrayName, '[');
    return arrayName;
}

int extractArraySize(string input) {
    unsigned first = input.find("[");
    unsigned last = input.find("]");
    string arraySize = input.substr(first+1,last-first-1);
    return stoi(arraySize);
}

vector<Parameter> extractParameterList(string input) {
    vector<string>tempList = split(input,',');
    vector<Parameter>parameterList;
    for (int i = 0; i < tempList.size(); i++) {
        vector<string>temp = split(tempList[i], ' ');
        parameterList.push_back(Parameter(temp[1],temp[0]));
    }
    return parameterList;
}



void initAsmFile(string fileName){
    ofstream writeFile;

    writeFile.open(fileName.c_str());
    string code = "";
    code += ".MODEL SMALL\n";
    code += ".STACK 400H\n";
    code += ".DATA\n";
    code += ".CODE\n";
    writeFile<<code;
    cout<<"initAsmFIle\n";
    writeFile.close();
}

void printAsm(string fileName, string code) {
    ofstream writeFile;
    writeFile.open(fileName.c_str(),ios_base::app);
    writeFile<<code;
    writeFile.close();
}

void printAtLineNo(string fileName, string code, int lineNo) {
    string tempFile = "temp.asm";
    cout<<"printAtLineNo\n";
    ofstream writeFile;
    writeFile.open(tempFile.c_str());
    ifstream readFile;
    readFile.open(fileName.c_str(),ios_base::in);
    string line;
    int lineCount = 0;
    bool hasWritten = false;
    

    while (getline(readFile, line)) {
        if (lineCount == lineNo) {
            writeFile << code << '\n';
            hasWritten = true;
        }
        writeFile << line << '\n';
        lineCount++;
    }

    if(!hasWritten) {
        writeFile << code << '\n';
        hasWritten = true;
    }

    readFile.close();
    writeFile.close();
    int failStatus = remove(fileName.c_str());
    if (failStatus)
        cout << "Error deleting file\n";
    failStatus = rename(tempFile.c_str(),fileName.c_str());
    if (failStatus)
        cout << "Error renaming file\n";
}


//asm code copied from ./sample_1.out test1_i.c
void printNewlineInAsm(string fileName){
    string code = 
    "\tPRINT_NEWLINE PROC\n\
        ; PRINTS A NEW LINE WITH CARRIAGE RETURN\n\
        PUSH AX\n\
        PUSH DX\n\
        MOV AH, 2\n\
        MOV DL, 0Dh\n\
        INT 21h\n\
        MOV DL, 0Ah\n\
        INT 21h\n\
        POP DX\n\
        POP AX\n\
        RET\n\
    PRINT_NEWLINE ENDP\n\n";
    printAsm(fileName, code);
}

void printCharInAsm(string fileName){
    string code = 
    "\tPRINT_CHAR PROC\n\
        ; PRINTS A 8 bit CHAR \n\
        ; INPUT : GETS A CHAR VIA STACK\n\ 
        ; OUTPUT : NONE\n\
        PUSH BP\n\
        MOV BP, SP\n\
        ; STORING THE GPRS\n\
        PUSH AX\n\
        PUSH BX\n\
        PUSH CX\n\
        PUSH DX\n\
        PUSHF\n\
        MOV DX, [BP + 4]\n\
        MOV AH, 2\n\
        INT 21H\n\
        POPF\n\
        POP DX\n\
        POP CX\n\
        POP BX\n\
        POP AX\n\
        POP BP\n\
        RET 2\n\
    PRINT_CHAR ENDP\n\n";
    printAsm(fileName, code);
}

void printIntegerInAsm(string fileName){
    string code = 
    "\tPRINT_DECIMAL_INTEGER PROC NEAR\n\
        ; PRINTS SIGNED INTEGER NUMBER WHICH IS IN HEX FORM IN ONE OF THE REGISTER\n\
        ; INPUT : CONTAINS THE NUMBER  (SIGNED 16BIT) IN STACK\n\
        ; OUTPUT : \n\
        ; STORING THE REGISTERS\n\
        PUSH BP\n\
        MOV BP, SP\n\
        PUSH AX\n\
        PUSH BX\n\
        PUSH CX\n\
        PUSH DX\n\
        PUSHF\n\
        MOV AX, [BP+4]\n\
        ; CHECK IF THE NUMBER IS NEGATIVE\n\
        OR AX, AX\n\
        JNS @POSITIVE_NUMBER\n\
        ; PUSHING THE NUMBER INTO STACK BECAUSE A OUTPUT IS WILL BE GIVEN\n\
        PUSH AX\n\
        MOV AH, 2\n\
        MOV DL, 2Dh\n\
        INT 21h\n\
        ; NOW IT'S TIME TO GO BACK TO OUR MAIN NUMBER\n\
        POP AX\n\
        ; AX IS IN 2'S COMPLEMENT FORM\n\
        NEG AX\n";
        code+="\t\t@POSITIVE_NUMBER:\n\
            ; NOW PRINTING RELATED WORK GOES HERE\n\
            XOR CX, CX      ; CX IS OUR COUNTER INITIALIZED TO ZERO\n\
            MOV BX, 0Ah\n\
            @WHILE_PRINT:\n\
                ; WEIRD DIV PROPERTY DX:AX / BX = VAGFOL(AX) VAGSESH(DX)\n\
                XOR DX, DX\n\
                ; AX IS GUARRANTEED TO BE A POSITIVE NUMBER SO DIV AND IDIV IS SAME\n\
                DIV BX\n\
                ; NOW AX CONTAINS NUM/10\n\
                ; AND DX CONTAINS NUM%10\n\
                ; WE SHOULD PRINT DX IN REVERSE ORDER\n\
                PUSH DX\n\
                ; INCREMENTING COUNTER\n\
                INC CX\n\
                ; CHECK IF THE NUM IS 0\n\
                OR AX, AX\n\
                JZ @BREAK_WHILE_PRINT; HERE CX IS ALWAYS > 0\n\
                ; GO AGAIN BACK TO LOOP\n\
                JMP @WHILE_PRINT\n\
            @BREAK_WHILE_PRINT:\n\
            \n\
            ;MOV AH, 2\n\
            ;MOV DL, CL \n\
            ;OR DL, 30H\n\
            ;INT 21Hn\n\
            @LOOP_PRINT:\n\
                POP DX\n\
                OR DX, 30h\n\
                MOV AH, 2\n\
                INT 21h\n\
                LOOP @LOOP_PRINT\n\
        CALL PRINT_NEWLINE\n\
        ; RESTORE THE REGISTERS\n\
        POPF\n\
        POP DX\n\
        POP CX\n\
        POP BX\n\
        POP AX\n\
        POP BP\n\
        RET\n\
    PRINT_DECIMAL_INTEGER ENDP\n\n";
    printAsm(fileName, code);
}

#endif