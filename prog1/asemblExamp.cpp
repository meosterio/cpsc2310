// Licensed under GPL 3.0
//
// CPSC 231-001
// Assignment 1
//
// Assembles a subset of JVM assembly code into Java bytecode using a
// two-pass structure
//
// Assumptions about input:
// - Input file is read from argv[1]
// - Opcode mnemonics are lowercased
// - Statements contain no spaces
// - Program should be called in the form: ./program input.m > executable

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

map<string, int> table;  // Maps label to pc
map<string, int> opcode;  // Maps mnemonic to opcode

int main(int argc, char const *argv[]) {
    opcode["iconst_m1"] = 2;
    opcode["iconst_0"] = 3;
    opcode["iconst_1"] = 4;
    opcode["iconst_2"] = 5;
    opcode["iconst_3"] = 6;
    opcode["iconst_4"] = 7;
    opcode["iconst_5"] = 8;
    opcode["bipush"] = 16;
    opcode["iload_0"] = 26;
    opcode["iload_1"] = 27;
    opcode["iload_2"] = 28;
    opcode["iload_3"] = 29;
    opcode["iload"] = 21;
    opcode["istore_0"] = 59;
    opcode["istore_1"] = 60;
    opcode["istore_2"] = 61;
    opcode["istore_3"] = 62;
    opcode["istore"] = 54;
    opcode["pop"] = 87;
    opcode["swap"] = 95;
    opcode["dup"] = 89;
    opcode["iadd"] = 96;
    opcode["isub"] = 100;
    opcode["imul"] = 104;
    opcode["idiv"] = 108;
    opcode["irem"] = 112;
    opcode["ineg"] = 116;
    opcode["iinc"] = 132;
    opcode["ifeq"] = 153;
    opcode["ifge"] = 156;
    opcode["ifgt"] = 157;
    opcode["ifle"] = 158;
    opcode["iflt"] = 155;
    opcode["ifne"] = 154;
    opcode["goto"] = 167;
    opcode["jsr"] = 168;
    opcode["ret"] = 169;
    opcode["invokevirtual"] = 182;
    opcode["return"] = 177;


    ifstream fin(argv[1]);

    // General parsing strategy:
    // 1. Read tokens separated by spaces into std::string
    // 2. Attempt to match mnemonics that don't use parentheses
    // 3. Otherwise, sscanf the resulting string to extract the
    //    mnemonic and characters between parentheses
    // 4. Two-argument mnemonics are run through sscanf again
    //    to split the comma

    int pc = 0;
    string buf;
    while (fin >> buf) {
        // Test for and ignore comment(`...')
        // len( comment(`') ) == 11
        // len( comment ) == 7
        if (buf.substr(0, min((int)buf.length(), 7)) == "comment") {
            // Consume tokens until a closing ') is found
            while (buf.find("')") == string::npos) {
                if (!fin.good()) {
                    cerr << "Encountered an error attempting to find the" <<
                    " end of a comment(`') token. Crashing." << endl;
                    return 1;
                } else {
                    fin >> buf;
                }
            }
        } else if (buf == "iconst_m1" ||
            buf == "iconst_0" ||
            buf == "iconst_1" ||
            buf == "iconst_2" ||
            buf == "iconst_3" ||
            buf == "iconst_4" ||
            buf == "iconst_5" ||
            buf == "iload_0" ||
            buf == "iload_1" ||
            buf == "iload_2" ||
            buf == "iload_3" ||
            buf == "istore_0" ||
            buf == "istore_1" ||
            buf == "istore_2" ||
            buf == "istore_3" ||
            buf == "pop" ||
            buf == "swap" ||
            buf == "dup" ||
            buf == "iadd" ||
            buf == "isub" ||
            buf == "imul" ||
            buf == "idiv" ||
            buf == "irem" ||
            buf == "ineg" ||
            buf == "ret" ||
            buf == "ineg" ||
            buf == "return") {
            // No arguments
            pc++;
        } else {
            // Has arguments
            char mnemonic[32];
            char args[32];

            // %[^(] matches a string up until a ( character
            // ( matches the ( character
            // %[^)] matches a string up until a ) character
            // ) matches the ) character
            if (sscanf(buf.c_str(), "%[^(](%[^)])", mnemonic, args) != 2) {
                cerr << "Failed to deparenthesize token: '" << buf <<
                "'. Crashing." << endl;
                return 1;
            }

            if (strcmp(mnemonic, "bipush") == 0 ||
                strcmp(mnemonic, "iload") == 0 ||
                strcmp(mnemonic, "ifeq") == 0 ||
                strcmp(mnemonic, "ifge") == 0 ||
                strcmp(mnemonic, "ifgt") == 0 ||
                strcmp(mnemonic, "ifle") == 0 ||
                strcmp(mnemonic, "iflt") == 0 ||
                strcmp(mnemonic, "ifne") == 0 ||
                strcmp(mnemonic, "goto") == 0 ||
                strcmp(mnemonic, "jsr") == 0 ||
                strcmp(mnemonic, "invokevirtual") == 0) {
                // One argument
                pc += 2;
            } else if (strcmp(mnemonic, "iinc") == 0) {
                // Two arguments
                pc += 3;
            } else if (strcmp(mnemonic, "label") == 0) {
                // Label
                if (table.find(string(args)) == table.end()) {
                    table[string(args)] = pc;
                } else {
                    cerr << "Duplicate label " << args << ". Crashing." << endl;
                    return 1;
                }
            } else {
                cerr << "Bad token: '" << buf << "'. Crashing." << endl;
                return 1;
            }
        }
    }

    fin.clear();                 // clear fail and eof bits
    fin.seekg(0, std::ios::beg);  // back to the start!

    pc = 0;
    while (fin >> buf) {
        // Test for and ignore comment(`...')
        // len( comment(`') ) == 11
        // len( comment ) == 7
        if (buf.substr(0, min((int)buf.length(), 7)) == "comment") {
            // Consume tokens until a closing ') is found
            while (buf.find("')") == string::npos) {
                if (!fin.good()) {
                    cerr << "Encountered an error attempting to find the" <<
                    " end of a comment(`') token. Crashing." << endl;
                    return 1;
                } else {
                    fin >> buf;
                }
            }
        } else if (buf == "iconst_m1" ||
            buf == "iconst_0" ||
            buf == "iconst_1" ||
            buf == "iconst_2" ||
            buf == "iconst_3" ||
            buf == "iconst_4" ||
            buf == "iconst_5" ||
            buf == "iload_0" ||
            buf == "iload_1" ||
            buf == "iload_2" ||
            buf == "iload_3" ||
            buf == "istore_0" ||
            buf == "istore_1" ||
            buf == "istore_2" ||
            buf == "istore_3" ||
            buf == "pop" ||
            buf == "swap" ||
            buf == "dup" ||
            buf == "iadd" ||
            buf == "isub" ||
            buf == "imul" ||
            buf == "idiv" ||
            buf == "irem" ||
            buf == "ineg" ||
            buf == "ret" ||
            buf == "ineg" ||
            buf == "return") {
            // No arguments
            cout << pc << ": " << opcode[buf] << endl;
            pc++;
        } else {
            // Has arguments
            char mnemonic[32];
            char args[32];

            // %[^(] matches a string up until a ( character
            // ( matches the ( character
            // %[^)] matches a string up until a ) character
            // ) matches the ) character
            if (sscanf(buf.c_str(), "%[^(](%[^)])", mnemonic, args) != 2) {
                cerr << "Failed to deparenthesize token: '" << buf <<
                    "'. Crashing." << endl;
                return 1;
            }

            if (strcmp(mnemonic, "bipush") == 0 ||
                strcmp(mnemonic, "invokevirtual") == 0) {
                // One argument. Don't lookup symbol.
                cout << pc << ": " << opcode[string(mnemonic)] << " " <<
                    string(args) << endl;
                pc += 2;
            } else if (strcmp(mnemonic, "iload") == 0 ||
                strcmp(mnemonic, "ifeq") == 0 ||
                strcmp(mnemonic, "ifge") == 0 ||
                strcmp(mnemonic, "ifgt") == 0 ||
                strcmp(mnemonic, "ifle") == 0 ||
                strcmp(mnemonic, "iflt") == 0 ||
                strcmp(mnemonic, "ifne") == 0 ||
                strcmp(mnemonic, "goto") == 0 ||
                strcmp(mnemonic, "jsr") == 0) {
                // One argument. Lookup symbol.
                if (table.find(string(args)) == table.end()) {
                    cerr << "Label not found: " << args <<
                        ". Crashing." << endl;
                    return 1;
                } else {
                    cout << pc << ": " << opcode[string(mnemonic)] << " " <<
                        table[string(args)] << endl;
                    pc += 2;
                }
            } else if (strcmp(mnemonic, "iinc") == 0) {
                // Two arguments
                char args1[32], args2[32];
                if (sscanf(args, "%[^,],%s", args1, args2) != 2) {
                    cerr << "Failed to separate comma token: '" << string(args)
                        << "'. Crashing." << endl;
                    return 1;
                }
                cout << pc << ": " << opcode[string(mnemonic)] << " " <<
                    string(args1) << " " << string(args2) << endl;
                pc += 3;
            } else if (strcmp(mnemonic, "label") == 0) {
                // Label. Do nothing.
            } else {
                cerr << "Bad token: '" << buf << "'. Crashing." << endl;
                return 1;
            }
        }
    }

    return 0;
}
