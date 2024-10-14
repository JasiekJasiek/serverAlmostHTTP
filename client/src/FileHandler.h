#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <fstream>

class FileHandler{
private:
    std::string name;
    std::ifstream file_in;
    std::ofstream file_out;
public:

    FileHandler(std::string name){
        this -> name = name;
    }
    
    std::string read(){
        file_in.open(name, std::ios::binary);

        std::string data = "";

        char byte = file_in.get();
        while(file_in.good()){
            data += byte;
            byte = file_in.get();
        }

        file_in.close();

        return data;

    }

    void save(std::string data){
        file_out.open(name, std::ios::binary);

        for(char byte : data){
            file_out.put(byte);
        }

        file_out.close();

    }

};

#endif