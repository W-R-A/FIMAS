#include "Networkbits.hpp"

Serial pc(USBTX, USBRX, 115200);

//Network thread - responsible for listening for connectinos and responding with updated tempature values
void networktest()
{   
    //Configure an ethernet connection
    EthernetInterface eth;
    eth.set_network(IP, NETMASK, GATEWAY);
    eth.connect();
    
    //Now setup a web server
    TCPSocket srv;           //TCP/IP Server
    TCPSocket* clt_sock;      //Socket for communication
    SocketAddress clt_addr;  //Address of incoming connection
    
    /* Open the server on ethernet stack */
    srv.open(&eth);
    
    /* Bind the HTTP port (TCP 80) to the server */
    srv.bind(eth.get_ip_address(), 80);
    
    /* Can handle 5 simultaneous connections */
    srv.listen(5);
    
	int i = 0;
    //KEEP RESPONDING WHILE THE SWITCHES ARE PRESSED
	
	//this will run once per http request
    while (true) {
        using namespace std;

        char *buffer = new char[1024];
        
        //Block and wait on an incoming connection
        clt_sock = srv.accept();
		
        clt_sock->getpeername(&clt_addr);  //this will fill address of client to the SocketAddress object

        pc.printf("accept %s:%d\n", clt_addr.get_ip_address(), clt_addr.get_port());

        clt_sock->recv(buffer, 1024);

        pc.printf("Received Msg: %s\n\n", buffer);  //this was missing in original example. 
		
		//address parser logic, decide what repsonse is required dependant on the incoming address
		
		string addFavicon ("favicon");
		string address (buffer);
		
		
		string response;
		
		
		    //Read All from buffer
		if (address.find(addFavicon) != string::npos) {
			//Echo confirmation
			pc.printf("favicon, 404");
			
			//Uses a C++ string to make it easier to concatinate
			response += HTTP_STATUS_LINE_404;
			
			response += "\r\n";
		
		} 
		else {
			//Uses a C++ string to make it easier to concatinate
			response += HTTP_STATUS_LINE_200;
			
			response += "\r\n";
			
			response += HTTP_HEADER_FIELDS;
			
			response += "\r\n\r\n";
			
			//Build the C++ string response
			response += HTTP_MESSAGE_BODY1;
		}
		
		
        
        
		
		//print send html
		printf("\n\nHTML: %s", response.c_str());
		
		//Send static HTML response (as a C string)
        clt_sock->send(response.c_str(), response.size());  
		
		
		
		//response = "HTTP/1.0 200 OK\r\n Content-Type: application/javascript; charset=utf-8\r\n";
		
		//Build the C++ string response
        //response =+ jquery;
		
		//Send static HTML response (as a C string)
        //clt_sock->send(response.c_str(), response.size()); 

		clt_sock->close();
		
        delete[] buffer;

		wait_us(100000);
    }
}