#include "Networkbits.hpp"

//Debugging output, use faster baud rate to remain responsive
Serial pc(USBTX, USBRX, 115200);

//Network thread - This thread handles network communications over ethernet with a client
void networktest()
{
    //Declare an ethernet interface
    EthernetInterface eth;

    //Set properties
    eth.set_network(IP, NETMASK, GATEWAY);

    //Connect to client
    eth.connect();

    //Setup a web server
    //TCP/IP Server
    TCPSocket srv;

    //Socket for communication      
    TCPSocket *clt_sock; 

    //Address of incoming connection   
    SocketAddress clt_addr; 

    //Open the server on the ethernet interface stack
    srv.open(&eth);

    //Bind the HTTP port (TCP 80) to the server
    srv.bind(eth.get_ip_address(), 80);

    //Listen for 1 connection at a time
    srv.listen(1);

    //Start an infinite loop to handle http requests
    //This will run once per http request recieved
    while (true) {
        //Use the standard namespace to allow for easy use of the string type
        using namespace std;

        //Create a buffer to hold the data sent from the client
        //This will include the URL which will need to be parsed so that the appropiate action can be taken
        char buffer[1024];

        //Block and wait on an incoming connection
        clt_sock = srv.accept();

        //Fill address of client to the SocketAddress object
        clt_sock->getpeername(&clt_addr); 

        //Debugging, send the client information over serial
        pc.printf("accept %s:%d\n", clt_addr.get_ip_address(), clt_addr.get_port());

        //Recieve the data sent from the client
        clt_sock->recv(buffer, 1024);

        //Debuging, print this out over serial
        pc.printf("Received Msg: %s\n\n", buffer); //this was missing in original example.


        //Address parser logic, decide what repsonse is required dependant on the incoming address

        //Declare a string for the favicon url request - this needs to move to a more central location, header file
        string addFavicon("favicon.ico");
        string addIndex("GET / HTTP/1.1");
        string addStyles("styles.css");
        string addJquery("jquery.js");

        //Create a sting based on the recieved data from the client
        string address(buffer);

        //Create a string to hold the response to be sent to the client
        string response;

        //If the address contains the word favicon, return a 404 error
        if (address.find(addFavicon) != string::npos) {
            
            //Add a 404 header to the response
            response += HTTP_STATUS_LINE_404;

            //Add a line feed and carriage return to the response
            response += "\r\n";
        }
        else if (address.find(addIndex) != string::npos) {
            
            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += HTTP_HEADER_FIELDS;

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";

            //Add the body
            response += HTTP_MESSAGE_BODY1;
        }
        else if (address.find(addStyles) != string::npos) {
            
            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += "Content-Type: text/css";

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";
            
            //Add the body
            response += STYLES;
        }
        else if (address.find(addJquery) != string::npos) {
            
            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += "Content-Type: text/javascript";

			//Add a line feed and carriage return to the response
            response += "\r\n";
			
			//Add the header fields
            response += "Cache-Control: public, max-age=31536000";
			
            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";
            
            //Add the body
            response += JQUERY;
        }
        else {
            
            //If we get to this else statement, then no route exists for this request, throw a 404 to the client
            //Add a 404 header to the response
            response += HTTP_STATUS_LINE_404;

            //Add a line feed and carriage return to the response
            response += "\r\n";
        }

        //Debugging, print the sent html
        //printf("\n\nHTML: %s", response.c_str());

        //Send HTML response (as a C string)
        clt_sock->send(response.c_str(), response.size());

        //Close the socket to signal the end of the transmission
        clt_sock->close();
    }
}