#include "mdfile.h"
#include <limits>
using namespace std;

void msgsend(int work_sock, string mess){
    char *buffer = new char[4096];
    strcpy(buffer, mess.c_str());
    send(work_sock, buffer, mess.length(), 0);
}

string MD(string sah){
Weak::MD5 hash;
    string digest;
    StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));
      return digest;
 }
void errors(string error, string name){
    ofstream file;
    file.open(name, ios::app);
    if(file.is_open()){
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        file << error << ':' << asctime(timeinfo) << endl;
        cout << "Detected error: " << error << endl;
    }
}
int er(string file_name, string file_error){
        fstream file;
        file.exceptions(ifstream::badbit | ifstream::failbit);
        try{
        file.open(file_name);
        return 1;
        } catch(const exception & ex){
        string error = "Error is entered in the Error file!";
        errors(error, file_error);
        return 12;
        }
        }

int Server::self_addr(string error, string file_error, int port){
            int s = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in * self_addr = new (sockaddr_in);
            self_addr->sin_family = AF_INET;
            self_addr->sin_port = htons(port);
            self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
            cout << "Client connection is expected...\n";
        int b = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
            if (b == -1) {
                cout << "Binding error!\n";
                error = "Error binding";
                errors(error, file_error);
                return 1;
            }
            listen(s, SOMAXCONN);
            return s;
            }

int Server::client_addr(int s, string error, string file_error){
                sockaddr_in * client_addr = new sockaddr_in;
                socklen_t len = sizeof (sockaddr_in);
                int work_sock = accept(s, (sockaddr*)(client_addr), &len);
                if (work_sock == -1) {
                    cout << "Connection error!\n";
                    error = "Connection error";
                    errors(error, file_error);
                    return 1;
                }
                else {
                    cout << "Successfull client connection!\n";
                    return work_sock;
                }
                }

int autorized(int work_sock, string file_name, string file_error){

                    string ok = "OK";
                    string salt = "0011CF334455DA66";
                    string err = "ERR";
                    string error;
                    char msg[255];
                    
                    int msg_size;
                    msg_size = recv(work_sock, &msg, sizeof(msg), 0);
                    string message(msg, msg_size);
                        string login, hashq;
                        fstream file;
                        file.open(file_name);
                        getline (file, login, ':');
                        getline (file, hashq);

                    if (message != login){
                        msgsend(work_sock, err);
                        error = "Login error";
                        errors(error, file_error);
                        close(work_sock);
                        return 1;
                    } else{
                    	msgsend(work_sock,  salt);
                    msg_size = recv(work_sock, msg, sizeof(msg), 0);
                    string HASH(msg, msg_size);
                    string sah = salt + hashq;
                    string digest;
                    digest = MD(sah);

                    if (digest != HASH){
                        cout << digest << endl;
                        cout << HASH << endl;
                        msgsend(work_sock,  err);
                        error = "Password error";
                        errors(error, file_error);
                        close(work_sock);
                        return 1;
                    } else{
                        msgsend(work_sock,  ok);
                    }
}
return 1;
}
     
    int math(int work_sock){
                    uint32_t quantity;
                    uint32_t number;
                    uint64_t numeric_vector;
                        recv(work_sock, &quantity, sizeof(quantity), 0);

                    for(int j=0; j<quantity; j++){
                        recv(work_sock, &number, sizeof(number), 0);
                        uint32_t sum = 0;

                    for(int i=0; i<number; i++){
                        recv(work_sock, &numeric_vector, sizeof(numeric_vector), 0);
                        if (sum > (numeric_limits < uint64_t > ::max() - numeric_vector)) {
                            sum = numeric_limits < uint64_t > ::max();
                            break;
                        }
                        sum = sum+numeric_vector;
                    }
                    uint64_t mfc;
                    mfc = sum/quantity;
                    send(work_sock, &mfc, sizeof(mfc), 0);
                    }
                    
                    cout << "Server operation is completed!\n" <<endl;
                    close(work_sock);
                    return 1;
                    }
