#include "Networkbits.hpp"
#include "hardware.hpp"
#include "serialInterface.hpp"

//Network thread - To handle networking, http over TCP/IP
Thread networkThread;

//Network - responsible for listening for http connections and then processing and responding to them
//No data is returned and no parameters need to be passed
void network(void) {
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
        serialQueue.call(printf, "accept %s:%d\n", clt_addr.get_ip_address(), clt_addr.get_port());

        //Recieve the data sent from the client
        clt_sock->recv(buffer, 1023);

        //Debuging, print this out over serial
        serialQueue.call(printf, "Received Msg: %s\n\n", buffer);

        //Create a sting based on the recieved data from the client
        string clientData(buffer);

        //Find the HTTP request version so that the address can be parsed properly - only data before this is parsed
        uint16_t httpLoc = clientData.find("HTTP/");

        //Debuging, print this out over serial
        serialQueue.call(printf, "Found HTTP designator at position: %u\n\n", httpLoc);

        //Address parser logic, decide what repsonse is required dependant on the incoming address

        //Create a string based on the http get request data from the client
        string address = clientData.substr(0, httpLoc);

        //Create a string to hold the response to be sent to the client
        string response;

        //If the address contains the word favicon, return a 404 error
        if (address.find("favicon.ico") != string::npos) {

            //Add a 404 header to the response
            response += HTTP_STATUS_LINE_404;

            //Add a line feed and carriage return to the response
            response += "\r\n";
        } else if (address.find("styles.css") != string::npos) {

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
        } else if (address.find("jquery.js") != string::npos) {

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
        } else if (address.find("devicetest") != string::npos) {

            int pos = address.find("id=");

            serialQueue.call(printf, "HTTP request, found device ID at position: %d \n", pos);

            string IDstr = address.substr(pos + 3, 4);

            serialQueue.call(printf, "Device ID:%s \n", IDstr.c_str());

            int id = stoi(IDstr);

            serialQueue.call(printf, "Device ID:%d \n", id);

            int statepos = address.find("state=");

            serialQueue.call(printf, "HTTP request, found state ID at position : %d \n", statepos);

            string Statestr = address.substr(statepos + 6, 2);

            serialQueue.call(printf, "State:%s \n", Statestr.c_str());

            int state = stoi(Statestr);

            serialQueue.call(printf, "state:%d \n", state);

            for (int i = 0; i < devices.size(); i++) {
                if (id == devices[i]->getID()) {
                    devices[i]->changeState(state);
                    //Add a 200 header code to the response
                    response += HTTP_STATUS_LINE_200;

                    //Add a line feed and carriage return to the response
                    response += "\r\n";
                }
            }
        } else if (address.find("testdevices") != string::npos) {

            //load routine with requested ID
            //search for device ID used
            //test device
            //return codes dependant on the outcome of the device tests

            int pos = address.find("routineid=");

            serialQueue.call(printf, "HTTP request, found routine ID at position: %d \n", pos);

            string IDstr = address.substr(pos + 10, 4);

            serialQueue.call(printf, "Routine ID:%s \n", IDstr.c_str());

            int id = stoi(IDstr);

            //Confgure the routine with id id for use with the system
            if (configRoutine(ROUTINE1, id)) {
                serialQueue.call(printf, "Error loading routine\n");
            } else {
                printRoutine();
            }


            serialQueue.call(printf, "Routine ID:%d \n", id);

            for (int i = 0; i < devices.size(); i++) {
                if (id == devices[i]->getID()) {
                    devices[i]->testDevice();
                    //Add a 200 header code to the response
                    response += HTTP_STATUS_LINE_200;

                    //Add a line feed and carriage return to the response
                    response += "\r\n";
                }
            }

        } else if (address.find("devices.json") != string::npos) {

            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += "Content-Type: application/json";

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";

            //Add the body
            response += CONFIGURATION;
        } else if (address.find("deviceConfig") != string::npos) {

            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += HTTP_HEADER_FIELDS;

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";

            //Add the body
            response += HTTP_MESSAGE_BODY_DEVICE_CONFIG;
        } else if (address.find("routines") != string::npos) {

            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += HTTP_HEADER_FIELDS;

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";

            //Add the body
            response += HTTP_MESSAGE_BODY_ROUTINES;
        } else if ((address.find("GET / ") != string::npos) || (address.find("GET /index") != string::npos)) {

            //Add a 200 header code to the response
            response += HTTP_STATUS_LINE_200;

            //Add a line feed and carriage return to the response
            response += "\r\n";

            //Add the header fields
            response += HTTP_HEADER_FIELDS;

            //Add 2 line feeds and carriage returns to the response to signal the end of the headers
            response += "\r\n\r\n";

            //Add the body
            response += HTTP_MESSAGE_BODY_INDEX;
        } else {

            //If we get to this else statement, then no route exists for this request, throw a 404 to the client
            //Add a 404 header to the response
            response += HTTP_STATUS_LINE_404;

            //Add a line feed and carriage return to the response
            response += "\r\n";
        }

        //Debugging, print the sent html
        //serialQueue.call(printf, "\n\nHTML: %s", response.c_str());

        //Send HTML response (as a C string)
        clt_sock->send(response.c_str(), response.size());

        //Close the socket to signal the end of the transmission
        clt_sock->close();
    }
}