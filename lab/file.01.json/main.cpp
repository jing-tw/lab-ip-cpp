#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int test_readfile(std::string file);

int main() {
    json j;
    j["name"] = "example";
    j["value"] = 42;

    std::cout << j.dump(4) << std::endl; 


    test_readfile("../data/1.json");

    return 0;
}

int test_readfile(std::string file){
    // Open the JSON file
    std::ifstream inputFile(file);
    
    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    // Parse the JSON file
    json j;
    inputFile >> j;

    // Print the entire JSON object
    std::cout << j.dump(4) << std::endl; // Pretty print with 4 spaces indentation

}