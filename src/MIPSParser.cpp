#include "MIPSParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

int main() {
    MIPSParser testOne("assembly_files/example1.asm");
    return 0;
}

MIPSParser::MIPSParser(const std::string& inputfile)
    : inputfile(inputfile), cleanfile(generateCleanName(inputfile)) {
    // Test print New File and Temp File
    // std::cout << "Input ASM File Name: " << this->inputfile << std::endl;
    // std::cout << "Clean ASM File Name: " << this->cleanfile << std::endl;
    // Parsing input file and writing to a file with formated code
    cleanASMFile(this->inputfile, this->cleanfile);
    printFile(this->cleanfile);
    // Creating instructions and symbol tables 
    createSymbolTable();
    //this->instructions = createInstrucions();
    // Create symbol tables on first past threw 
    // Open File 
    // Readfile
    // Add symbols

    // Second pass through, create instructions and assign adress

}

MIPSParser::~MIPSParser() {
    // Destructor implementation
}

void MIPSParser::createSymbolTable() {
    // Initializing variables
    uint32_t pc = 0x00400000;
    Section cur_section = NONE;
    // Opening clean asm file
    std::ifstream asmFile(this->cleanfile);
    if (!asmFile) {
        std::cerr << "Error opening asmFile." << std::endl;
        return;
    }
    std::string curLine;
    // Proccessing each line
    while (std::getline(asmFile, curLine)) {
        // Check if line is changing 
    }    

    // Open file
    // Iterate through file and only add address on instructions
    // Add labels and data values
    // Open the input file named "input.txt" 
    // Close File
    asmFile.close();
    return;
}
    
void MIPSParser::createInstrucions() {
    std::ifstream asmFile(this->cleanfile);
    
    return; 
}


/**
 * Rules:
 * Remove all comments
 * Only copy non-whitespace lines
 * Start all values at begining of line 
 */
void cleanASMFile(const std::string& inputfile, const std::string& outfile) {
    // Open file 
    std::ifstream dirtyFile(inputfile);
    std::ofstream cleanFile(outfile);
    // Error Handling
    if (!dirtyFile || !cleanFile) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }
    // Reading each line from dirty file, cleaning, writing to clean file
    std::string curLine;
    while (std::getline(dirtyFile, curLine)) {
        cleanASMLine(curLine);
        if (!curLine.empty()) {
            cleanFile << curLine << std::endl; // Write the line followed by a newline character
        }
    }    
    // Closing File
    dirtyFile.close();
    cleanFile.close();
    return;
}

void cleanASMLine(std::string& curLine) {
    // Reading only up to comment if existent
    std::size_t pos = curLine.find('#');
    if (pos != std::string::npos) {
        curLine = curLine.substr(0, pos);
    }
    // Removing trailing whitespace and making spaces a distance of 1 max
    std::istringstream stream(curLine);
    std::string word;
    std::string result;
    
    while (stream >> word) {
        if (!result.empty()) {
            result += ' '; 
        }
        result += word;
    }
    
    // Update the original string with the normalized result
    curLine = result;
    return;
}

void printFile(const std::string& inputfile) {
    std::ifstream inputFile(inputfile); 
    std::cout << "Filename: " << inputfile << std::endl;
    // Check if the file is successfully opened 
    if (!inputFile.is_open()) { 
        std::cerr << "Failed to open file: " << inputfile << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
    } 
  
    std::string line; // Declare a string variable to store each 
                 // line of the file 
  
    // Read each line of the file and print it to the 
    // standard output stream 
    std::cout << "File Content: " << std::endl; 
    while (getline(inputFile, line)) { 
        std::cout << line << std::endl; // Print the current line 
    } 
  
    // Close the file 
    inputFile.close(); 
    return;
    
}

const std::string generateCleanName(const std::string& filename) {
    // Define the extension to be replaced
    const std::string extension = ".asm";
    
    // Check if the filename ends with the specified extension
    if (filename.size() > extension.size() &&
        filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0) {
        // Create the new filename by replacing the extension with "_clean.asm"
        return filename.substr(0, filename.size() - extension.size()) + "_clean" + extension;
    }
    
    // Return the original filename if it does not end with ".asm"
    return filename;
}



