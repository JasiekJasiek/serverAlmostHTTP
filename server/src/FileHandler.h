#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <fstream>

class FileHandler{
private:
    std::string name;
public:

    FileHandler(std::string name){
        this -> name = name;
    }
    
    std::string read(){
        std::ifstream file(name, std::ios::binary);

        std::string data = "";

        char byte = file.get();
        while(file.good()){
            data += byte;
            byte = file.get();
        }

        file.close();

        return data;

    }

    void save(std::string data){
        std::ofstream file(name, std::ios::binary);

        for(char byte : data){
            file.put(byte);
        }

        file.close();

    }

};

#endif