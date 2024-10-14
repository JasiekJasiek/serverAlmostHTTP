#include "FileHandler.h"
class HTTPClient{

public:
    HTTPClient(const std::string& server_ip, int server_port){
        this -> server_ip = server_ip;
        this -> server_port = server_port;

        client_sock = socket(AF_INET, SOCK_STREAM, 0);
 
        server.sin_addr.s_addr = inet_addr(server_ip.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(server_port);
        
        connect(client_sock, (struct sockaddr *)&server, sizeof(server));

    }

    ~HTTPClient() {
        if (client_sock != -1) {
            close(client_sock);
        }
    }

    void get_content(){
        std::string data = recive_data();
        std::cerr << data << "\n";
    }

    void get_file(const std::string& file_path) {
        std::string request = "GET /" + file_path + " ";
        
        send(client_sock, request.c_str(), request.length(), 0);

        std::string data = recive_data();
        
        FileHandler file(file_path);
        file.save(data);

        close(client_sock); 
    }

    std::string recive_data(){
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

    void send_data(std::string& data){
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


    void put_file(const std::string& file_path){
        std::string request = "PUT /" + file_path + " ";
        send(client_sock, request.c_str(), request.size(), 0);

        FileHandler file(file_path);
        std::string data = file.read();
        send_data(data);
    }

    void delete_file(const std::string& file_path){
        std::string request = "DELETE /" + file_path + " ";
        send(client_sock, request.c_str(), request.size(), 0);
    }

private:
    std::string server_ip;
    int server_port;
    int client_sock;
    struct sockaddr_in server;
    const int BLOCK_SIZE = 1024;

};