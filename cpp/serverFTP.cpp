#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
using namespace std;
#define PORT 8080

int socket_id, accept_socket_status, valueread;
char buffer_ftp [10000] = {0};

void uploadF(){
	cout << "In in  upload";
	ofstream test_file;
	int n =read(accept_socket_status, buffer_ftp, 10000);
	test_file.open("test_server_upload.txt");		
	cout<<"no of bytes read  "<<n<<endl;
	cout << "After read";
	//cout << buffer_ftp;
	test_file <<  buffer_ftp;
	test_file.close();
}

void downloadF(){
	//Download - Client writes, Server reads.
	ifstream test_file ("test_server_download.txt", ifstream::binary);
	int length_doc;
	if(test_file){		
		test_file.seekg (0, test_file.end);
		length_doc = test_file.tellg();
		test_file.seekg (0, test_file.beg);
		char buffer_file_whole[length_doc];		
		test_file.read(buffer_file_whole, length_doc);
		write(accept_socket_status, buffer_file_whole, length_doc);		
		test_file.close();
	}
	cout << "File successfully downloaded. "<<endl; 
}


int main(){
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int option = 1;
//	create_socket_server
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_id < 0){
		cout << "Error while setting socket... \n";
	}

//	setSocketOption
	bool set_socket_option = setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, option);
	if(set_socket_option){
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		address.sin_port = htons( PORT );
	}
	else
		cout << "Error while setting socket... \n";

//	bindSocket
	int bind_status = bind(socket_id, (sockaddr *)&address, sizeof(address));
	if(bind_status == -1){
		cout << "Error while binding... \n";
	}
	
//	listenSocket
	int listen_status = listen(socket_id, 3);
	if(listen_status == -1){
		cout << "Error while listening... \n";
	}	

//	acceptSocket
	accept_socket_status = accept(socket_id, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	cout<<accept_socket_status<<" accepting socket"<<endl;
	if(accept_socket_status <0){
		cout << "Error while accepting new socket... \n";
	}
	downloadF();
/*
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
	}*/
	return 0;
}
