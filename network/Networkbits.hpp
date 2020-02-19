#ifndef MBED_NETWORKBITS_H
#define MBED_NETWORKBITS_H

#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPServer.h"
#include "TCPSocket.h"
#include <iostream>
#include <string> 


#define HTTP_STATUS_LINE "HTTP/1.0 200 OK"
#define HTTP_HEADER_FIELDS "Content-Type: text/html; charset=utf-8"
#define HTTP_MESSAGE_BODY1 "<!doctype html>\n<html lang=\"en-GB\">\n    <head>\n        <!-- Declare charset used at UTF-8 -->\n        <meta charset=\"UTF-8\">\n\n        <!-- Title of the webpage -->\n        <title>FIMAS Main Page</title>\n\n        <!-- Link to stylesheet -->\n        <!-- <link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\"> -->\n\n        <!-- Set initial scale for devices with smaller screens -->\n        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\n        <style>\n        body {\n            background-color: rgb(247, 252, 184);\n            margin: 0;\n            padding: 0;\n            padding-top: 0px; \n          }\n          \n          .main {\n            padding: 5px;\n            margin:auto;\n            text-align:center\n          }\n            \n          h1 {\n            color: rgb(7, 1, 61);\n            text-align: center;\n            font-family: Arial;\n          } \n          \n          p {\n            color: rgb(7, 1, 61);\n            font-family: Arial;\n            font-size: 20px;\n            text-align: center;\n          }\n          \n          ul {\n            list-style-type: none;\n            margin: 0;\n            padding: 0;\n            overflow: hidden;\n            background-color: rgb(145, 229, 255);\n            position: -webkit-sticky; /* Safari */\n            position: sticky;\n            top: 0;\n          }\n          \n          li {\n            float: left;\n          }\n          \n          li a {\n            display: block;\n            color: rgb(7, 1, 61);\n            text-align: center;\n            padding: 20px 16px;\n            font-family: Arial;\n            font-size: 20px;\n            text-decoration: none;\n            border-radius: 10px;\n          }\n          \n          /* Change the link color to #111 (black) on hover */\n          li a:hover {\n            background-color: rgb(75, 213, 255);\n          } \n          \n          .active {\n            background-color: rgb(100, 255, 255);\n          }\n          \n          table {\n            font-family: arial;\n            border-collapse: collapse;\n            width: 100%;\n          }\n          \n          td, th {\n            text-align: center;\n            padding: 8px;\n            border: 1px solid rgb(145, 229, 255)\n          }\n          \n          select {\n            padding: 16px;\n            font-family: Arial;\n            font-size: 16px;\n            background-color: rgb(145, 229, 255);\n            text-decoration: none;\n            border-radius: 10px\n          }\n          \n          button {\n            padding: 16px;\n            font-family: Arial;\n            font-size: 16px;\n            background-color: rgb(145, 229, 255);\n            text-decoration: none;\n            border-radius: 10px\n          }\n          </style>\n    </head>\n\n    <body>\n        <header>\n            <ul>\n                <li><a class=\"active\" href=\"index.html\">Home</a></li>\n                <li><a href=\"deviceConfig.html\">Device Configuration</a></li>\n                <li><a href=\"routines.html\">Routines Configuration</a></li>\n                <li><a href=\"help.html\">Help</a></li>\n            </ul>\n        </header>\n\n        <div style=\"margin:auto\">\n            <h1>Hello World!</h1>\n            <p>Temperature, 16 degrees</p>\n        </div>\n    </body>\n</html>\n"                             

#define HTTP_MESSAGE_BODY2 ""                                    \
       "</p>" "\r\n"                                             \
"    </div>" "\r\n"                                              \
"  </body>" "\r\n"                                               \
"</html>"

#define HTTP_RESPONSE HTTP_STATUS_LINE "\r\n"   \
                      HTTP_HEADER_FIELDS "\r\n" \
                      "\r\n"                    \
                      HTTP_MESSAGE_BODY "\r\n"

#define IP        "10.0.0.10"
#define NETMASK   "255.0.0.0"
#define GATEWAY   "10.0.0.1"

extern void networktest();

#endif