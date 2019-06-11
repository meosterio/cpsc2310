/* (alex9)
 * CPSC 2310 Sec 001
 * Program2
 * 2/15/18
 *
 * Program is a jvm assembler which creates an executable file
 * called "executable". Two pass structure is used.
 */

 #include <iostream>
 #include <fstream>
 #include <map>
 #include <string>
 #include <cstring>

 using namespace std;

 map<string, int> table;
 map<string, int> opcode;

 int main(int argc, char const *argv[]) {
   //initialize the opcode map with the opcodes value (map int to each opcode)
   opcode["iconst_m1"] = 2; opcode["iconst_0"] = 3; opcode["iconst_1"] = 4;
   opcode["iconst_2"] = 5; opcode["iconst_3"] = 6; opcode["iconst_4"] = 7;
   opcode["iconst_5"] = 8; opcode["bipush"] = 16; opcode["iload_0"] = 26;
   opcode["iload_1"] = 27; opcode["iload_2"] = 28; opcode["iload_3"] = 29;
   opcode["iload"] = 21; opcode["istore_0"] = 59; opcode["istore_1"] = 60;
   opcode["istore_2"] = 61; opcode["istore_3"] = 62; opcode["istore"] = 54;
   opcode["pop"] = 87; opcode["swap"] = 95; opcode["dup"] = 89;
   opcode["iadd"] = 96; opcode["isub"] = 100; opcode["imul"] = 104;
   opcode["idiv"] = 108; opcode["irem"] = 112; opcode["ineg"] = 116;
   opcode["iinc"] = 132; opcode["ifeq"] = 153; opcode["ifge"] = 156;
   opcode["ifgt"] = 157; opcode["ifle"] = 158; opcode["iflt"] = 155;
   opcode["ifne"] = 154; opcode["goto"] = 167; opcode["jsr"] = 168;
   opcode["ret"] = 169; opcode["return"] = 177; opcode["invokevirtual"] = 182;

   //make sure an input file is present
   if (argc < 2) {
     cerr << "Improper usage!!  Exitting\n";
     return 1;
   }

   //open the file, create an executable to print to
   ifstream fin(argv[1]);
   ofstream executable("executable");

   //create a string to read in all the info from the file
   //create the location counter
   //create bool to check for and exit loop if error is found
   string read;
   int location = 0;
   bool error = false;
   int sizeofcomment = 7;

   while (fin >> read && error == false) {
     //check for and ignore comments, read until end of comment is found (')')
     if (read.substr(0, min((int)read.length(), sizeofcomment)) == "comment") {
       while (read.find("')") == string::npos) {
         fin >> read;
       }
     }

     //check for all the opcodes which increment the location counter by 1
     else if (
       read == "iconst_m1" || read == "iconst_0" || read == "iconst_1" ||
       read == "iconst_2" || read == "iconst_3" || read == "iconst_4" ||
       read == "iconst_5" || read == "iload_0" || read == "iload_1" ||
       read == "iload_2" || read == "iload_3" || read == "istore_0" ||
       read == "istore_1" || read == "istore_2" || read == "istore_3" ||
       read == "pop" || read == "swap" || read == "dup" || read == "iadd" ||
       read == "isub" || read == "imul" || read == "idiv" ||
       read == "irem" || read == "ineg" || read == "ret" ||
       read == "return")
       {
         //increment the location couter by 1
         location++;
       }
       //check for opcodes that have a value with them and increment
       //the location counter by 2
       else {
         char name[15];
         char value[15];

         //read through and ignore the parentheses, thing before first
         //parenthese is the name, second one is the value
         //if cannot read past parentheses give error
         //ex: bipush(10), bipush is name, 10 is the value
         if (sscanf(read.c_str(), "%[^(](%[^)])", name, value) != 2) {
             cerr << "Parentheses Fail" << endl;
             error = true;
             return 1;
         }
         if (strcmp(name, "label") == 0) {
           //if label is not in the table already, add it;
           //if already in the table, give an error
           if (table.find(value) == table.end()) {
             table[value] = location;
           }
           else {
             cerr << "Error // Multiply-defined symbols" << value << endl;
             error = true;
             return 1;
           }
         }
         //check if the name read in is equal to the opcode
         else if (
           strcmp(name, "bipush") == 0 || strcmp(name, "iload") == 0 ||
           strcmp(name, "ifeq") == 0 || strcmp(name, "ifge") == 0 ||
           strcmp(name, "ifgt") == 0 || strcmp(name, "ifle") == 0 ||
           strcmp(name, "iflt") == 0 || strcmp(name, "ifne") == 0 ||
           strcmp(name, "goto") == 0 || strcmp(name, "jsr") == 0 ||
           strcmp(name, "invokevirtual") == 0)
           {
             //increment location counter by 2
             location+=2;
           }
           else if (strcmp(name, "iinc") == 0) {
             location += 3;
           }
           //if the name doesnt match a known opcode, give an error
           else {
             cerr << "Error // unknown opcode mnemonics" << read << endl;
             error = true;
             return 1;
           }
        }
    }
    //completes pass one

    //reset the file and go back to the start for pass 2
    fin.clear();
    fin.seekg(0, ios::beg);

    //set the location counter to 0
    //set error to false
    location = 0;
    error = false;
    while (fin >> read && error == false) {
      if (read.substr(0, min((int)read.length(), sizeofcomment)) == "comment") {
        while (read.find("')") == string::npos) {
          fin >> read;
        }
      }

      //check for all the opcodes which increment the location counter by 1
      else if (
        read == "iconst_m1" || read == "iconst_0" || read == "iconst_1" ||
        read == "iconst_2" || read == "iconst_3" || read == "iconst_4" ||
        read == "iconst_5" || read == "iload_0" || read == "iload_1" ||
        read == "iload_2" || read == "iload_3" || read == "istore_0" ||
        read == "istore_1" || read == "istore_2" || read == "istore_3" ||
        read == "pop" || read == "swap" || read == "dup" || read == "iadd" ||
        read == "isub" || read == "imul" || read == "idiv" ||
        read == "irem" || read == "ineg" || read == "ret" ||
        read == "return")
        {
          //print the location counter and the opcode number to the
          //executable file
          executable << location << ": " << opcode[read] << endl;
          //increment the location counter by 1
          location++;
        }
        else {
          char name[15];
          char value[15];
          //read through and ignore the parentheses, thing before first
          //parenthese is the name, second one is the value
          //if cannot read past parentheses, give error
          //ex: bipush(10), bipush is name, 10 is the value
          if (sscanf(read.c_str(), "%[^(](%[^)])", name, value) != 2) {
              cerr << "Parentheses Fail" << endl;
              error = true;
              return 1;
          }

          //check if the name read in, is equal to the opcode
          if (strcmp(name, "bipush") == 0 || strcmp(name, "invokevirtual") == 0)
          {
            //print the location counter, the opcode value, and the value
            executable << location << ": " << opcode[name] << " " <<
              value << endl;
            //increment the location counter by 2
            location += 2;
          }
          //check if the name read in is equal to the opcode
          else if (
            strcmp(name, "iload") == 0 || strcmp(name, "ifeq") == 0 ||
            strcmp(name, "ifge") == 0 || strcmp(name, "ifgt") == 0 ||
            strcmp(name, "ifle") == 0 || strcmp(name, "iflt") == 0 ||
            strcmp(name, "ifne") == 0 || strcmp(name, "goto") == 0 ||
            strcmp(name, "jsr") == 0)
            {
              //if the name doesnt match a known opcode, give an error
              if (table.find(value) == table.end()) {
                cerr << "Unknown opcode " << value << endl;
                error = true;
                return 1;
              }
              //print the location and the opcode value, and the table value
              //to the executable file
              else {
                executable << location << " " << opcode[name] <<
                " " << table[value] << endl;
                //increment location counter by 2
                location+=2;
              }
            }
            else if (strcmp(name, "iinc") == 0) {
              char firstValue[15];
              char secondValue[15];
              //read through and ingore commas, the first thing read is what to
              //increment, second value is how much to increment by
              //if cannot read passed comma, give error
              //ex: iinc(1,10), 1 is firstValue, 10 is secondValue
              if (sscanf(value, "%[^,],%s", firstValue, secondValue) != 2) {
                  cerr << "Comma Fail (Check Spacing)" << endl;
                  return 1;
              }
              //print
              executable << location << ": " << opcode[name] <<
              " " << firstValue << " " << secondValue << endl;
              //increment location counter by 3
              location+=3;
            }
        }
    }
    //completes pass 2
   return 0;
 }
