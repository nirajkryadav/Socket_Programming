#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

#define PORT 8080

using namespace std;

struct sockaddr_in address;
int socket_id = -1;
int valueread;
struct sockaddr_in serv_addr;
int addrlen = sizeof(address);
char message[] = "";
char buffer_ftp[10000] = {0};
int socket_status;

void downloadF(){
	ofstream test_file;
	test_file.open("test_client_download.txt");	
	read(socket_id, buffer_ftp, 10000);
	test_file << buffer_ftp;
	test_file.close();
}

void uploadF(){
	ifstream test_file ("test_client_upload.txt", ifstream::binary);
	int length_doc=0;
	if(test_file){
		cout<<"if loop me"<<endl;
		test_file.seekg (0, test_file.end);
		length_doc = test_file.tellg();
		cout<<"size of length_doc "<<length_doc<<endl;
		test_file.seekg (0, test_file.beg);
		char buffer_file_whole[length_doc];
		test_file.read(buffer_file_whole, length_doc);
		int n = write(socket_id, buffer_file_whole, length_doc);
		cout<<"no of bytes wrote "<<n<<endl;
		cout << buffer_file_whole<<"total size wrote : ";
		test_file.close();
	}
	cout << "File successfully uploaded. "<<endl; 
}


int main(){	
// 	createSocketServer
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_id == -1){
		cout << "Error while setting socket... \n";
	}

// 	connectSocket
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int connect_status = connect(socket_id, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(connect_status == -1){
		cout << "Error while connecting from client side... \n"; 
	}

	int ans;
	cout<<endl<<"Press 1 to upload";
	cout<<endl<<"Press 2 to download";
	cout<<endl<<"Enter your choice....";
	cin>>ans;
	switch(ans){
		//Download file: Client requests server;
	case 1:uploadF();
		break;
	case 2:downloadF();
		break;
	default:cout<<"Enter a valid option";
		break;
	}
	return 0;
}
