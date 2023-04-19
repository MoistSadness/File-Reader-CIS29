#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <sys/stat.h>
#include <cerrno>
#include <regex>
#include <functional>
#include <algorithm>

class FileReader{
public:
    // The constructor sets the file name
    FileReader(std::string filename){
        _filename = filename; 
    }

    // Return the size of the file
    long Size(){
        struct stat st;
        if (stat(_filename.c_str(), &st) == 0) {
            return st.st_size;
        } else std::perror("FileReader construtor");
        return -1;
    }
    
    // Return the name of the file
    std::string Name(){
        return _filename;
    }

    std::vector<char> Raw(){
        std::ifstream inFile(_filename, std::ios::binary);       // Open file

        if(inFile.is_open()){
            std::vector<char> data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
            inFile.close();
            return data;
        }

        std::perror("FileReader getRawData");
        std::vector<char> empty;
        return empty;
    }

    void Parse(void (*callback)(std::string)){
        std::vector<char> rawData = Raw();

        if (rawData.empty()) {
            std::cerr << "No raw data to parse" << std::endl;
            return;
        }

        std::string dataStr(rawData.begin(), rawData.end());
        callback(dataStr);
    }


private:
    std::string _filename;
    
};

void parseTxt( std::string dataStr) {
    /*
    std::cout << "*  Raw Text Data" << std::endl;
    std::cout << dataStr << std::endl;
    */

    std::regex pattern(",");
    std::string parsed = std::regex_replace(dataStr, pattern, "");

    std::cout << "*  Parsed Text Data" << std::endl;
    std::cout << parsed << std::endl << std::endl;
}

void parseBin( std::string dataStr) {
    std::cout << "*  Binary file data can't be parsed using regex" << std::endl;
    std::cout << dataStr << std::endl << std::endl;
}

void parseCSV( std::string dataStr) {
    /*
    std::cout << "*  Raw CSV Data" << std::endl;
    std::cout << dataStr << std::endl;
    */

    std::cout << "*  CSV Text Data" << std::endl;
    std::istringstream dataStream(dataStr);
    std::regex pattern("[^,]*");
    std::string line;
    std::vector<std::string> parsed;

    while(std::getline(dataStream, line)){
        std::cout << line << std::endl;             // Print the line
        
        std::vector< std::tuple<std::string, std::string, std::string> > storeCSV;      // Vector of tuples to store CSV data

        std::tuple<std::string, std::string, std::string> csvTuple;

        /** Loop to split by ',' and print each item
        std::string item;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, item, ',')){
            std::cout << item << std::endl;
            parsed.push_back(item);
        }
        */
    }
}

int main(int argc, const char * argv[]) {
    // Declaring stuff here
    std::string textFile = "Encrypt.txt";
    std::string binaryFile = "Morse.bin";
    std::string csvFile = "Tuple.csv";
    
    std::cout << std::endl;
    std::cout <<  "*****************************************" << std::endl;
    std::cout <<  "*\tFile Reader\t\t\t*" << std::endl;
    std::cout <<  "*****************************************" << std::endl << std::endl;

    std::cout <<  "Handling Text file" << std::endl;
    std::cout <<  "*****************************************" << std::endl;
    FileReader textFileTest(textFile);
    std::cout << "*  " << "Name of the file is"<<" "<< textFileTest.Name() << std::endl;
    std::cout << "*  "  <<"Size of the file is"<<" "<< textFileTest.Size() <<" "<<"bytes" << std::endl;
    textFileTest.Parse(parseTxt);       // Parse data
    
    std::cout <<  "Handling Binary file" << std::endl;
    std::cout <<  "*****************************************" << std::endl;
    FileReader binaryFileTest(binaryFile);
    std::cout << "*  " << "Name of the file is"<<" "<< binaryFileTest.Name() << std::endl;
    std::cout << "*  "  <<"Size of the file is"<<" "<< binaryFileTest.Size() <<" "<<"bytes" << std::endl;
    binaryFileTest.Parse(parseBin);       // Parse data

    std::cout <<  "Handling CSV file" << std::endl;
    std::cout <<  "*****************************************" << std::endl;
    FileReader csvFileTest(csvFile);
    std::cout << "*  " << "Name of the file is"<<" "<< csvFileTest.Name() << std::endl;
    std::cout << "*  "  <<"Size of the file is"<<" "<< csvFileTest.Size() <<" "<<"bytes" << std::endl;
    csvFileTest.Parse(parseCSV);       // Parse data




    /*
    std::cout <<  "Handling CSV file" << std::endl;
    std::cout <<  "*****************************************" << std::endl;
    FileReader csvFileTest(csvFile, "csv");
    csvFileTest.printResults();
    */

    return 0;
}
