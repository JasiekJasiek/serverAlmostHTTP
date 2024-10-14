#include "FileHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class HTTPServer{

public:

    HTTPServer(int server_port){
        this -> server_port = server_port;
        server_sock = -1;
        cur_path = "main/";

        server_sock = socket(AF_INET, SOCK_STREAM, 0);

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(server_port);

        bind(server_sock, (struct sockaddr *)&server, sizeof(server));

        listen(server_sock, 3);
        std::cerr << "Server started ---> Port: " << server_port << '\n';

    }

    ~HTTPServer() {
        if (server_sock != -1) {
            close(server_sock);
        }
    }

    void run() {
        while (true) {
            struct sockaddr_in client;
            socklen_t client_len = sizeof(client);
            int client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len);
            system("clear");
            handle_client(client_sock);
        }
    }

private:

    int server_port;
    int server_sock;
    struct sockaddr_in server;
    std::string cur_path;
    const int BLOCK_SIZE = 1024;

    void handle_client(int client_sock) {
        std::cerr << "Someone conected :)" << std::endl;
        const int BUFFER_SIZE = 1000;
        char buffer[BUFFER_SIZE] = {0};

        int bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);

        buffer[bytes_received] = '\0';
        std::string request(buffer);

        if (request.substr(0, 4) == "GET ") {
            get_file(request, client_sock);
        } 
        else if(request.substr(0, 4) == "PUT "){
            put_file(request, client_sock);
        }
        else if(request.substr(0, 7) == "DELETE "){
            delete_file(request);
        }    
    }

    void send_data(std::string& data, int client_sock){
        long long cnt = 1;
        long long all_packeges = (data.size() / BLOCK_SIZE);
        for(int i = 0; i < data.size();){
            std::string bytes = "";
            for(int j = 0; j < BLOCK_SIZE && i < data.size(); j++){
                bytes += data[ i ];
                i++;
            }
            std::cerr << "Sending: " << cnt << " / " << all_packeges << " package ---> " << (double(cnt) / double(all_packeges)) * 100 << "%"<< '\n';
            system("clear");
            cnt++;
            send(client_sock, bytes.c_str(), bytes.size(), 0);
        }
    }

    std::string recive_data(int client_sock){
        std::string data = "";
        char buff[BLOCK_SIZE];
        long long i = 1;
        
        ssize_t bytes_received;
        while ((bytes_received = recv(client_sock, buff, BLOCK_SIZE, 0)) > 0) {
            data.append(buff, bytes_received);
            std::cerr << "Received: " << i << "th package, bytes: " << bytes_received << '\n';
            system("clear");
            i++;
        }
        return data;
    }

    void get_file(const std::string& request, int client_sock){
        std::string file_path = extract_file_path(request);

        FileHandler file(cur_path + file_path);
        std::string data = file.read();
        send_data(data, client_sock);

        close(client_sock);
    }

    void put_file(const std::string& request, int client_sock){
        std::string file_path = extract_file_path(request);

        FileHandler file(cur_path + file_path);

        std::string data = recive_data(client_sock);
        
        file.save(data);

        close(client_sock);

    }

    void delete_file(const std::string& request){
        std::string file_path = extract_file_path(request);

        std::string remove_comand = "rm -r " + cur_path + file_path;
        system(remove_comand.c_str());
    }

    std::string extract_file_path(const std::string& request) {
        size_t start_pos = request.find("/") + 1;
        size_t end_pos = request.find(" ", start_pos);

        std::string file_path = request.substr(start_pos, end_pos - start_pos);

        return file_path;
    }

};