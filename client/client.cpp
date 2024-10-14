#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "src/HTTPClient.h"

const std::string CHOOSE = "CHOOSE FILE\n";

std::string file(){
    std::cerr << CHOOSE;
    std::string file; std::cin >> file;
    return file;
}

int main(){

    while(true){
        system("clear");
        HTTPClient client("Your server IP", 8080);
        std::cerr << "1. GET \n2. PUT \n3. DELETE \n";
        std::string option; std::cin >> option;
        if(option == "1"){
            client.get_file(file());
        }
        else if(option == "2"){
            client.put_file(file());
        }
        else if(option == "3"){
            client.delete_file(file());
        }
    }
    

    return 0;
}
