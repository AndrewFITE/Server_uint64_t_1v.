#include <iostream>
#include <getopt.h>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
using namespace std;
using namespace CryptoPP;
#include <cryptopp/md5.h>
string MD(string sah);
void errors(string error, string name);
int er(string file_name, string file_error);
void msgsend(int work_sock, string mess);
int autorized(int work_sock, string file_name, string file_error);
class Server{
private:

public:
int client_addr(int s, string error, string file_error);
int self_addr(string error, string file_error, int port);
};
int math(int work_sock);


