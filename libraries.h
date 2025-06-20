//This file contains all the required external libraries needed for this project.
#ifndef LIBRARIES_H
#define LIBRARIES_H
/*
 Use SQLite3 to create a local database to store items within the machine itself
 
*/

#include <sqlite3.h>


/*
 Use cURL for API calls and general API usage
*/

#include <curl/curl.h>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <uwebsockets/App.h>


/*
Use these header files for their .cpp counterparts.
*/
#include "APIHandler.h"
#include "StockTrading.h"
#include "Balance.h"
#include "DatabaseManager.h"

/*
 Use the rapidJSON libraries to do, at the least, basic JSON file parsing to extract necessary data

*/
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

/*
 Use the Boost libraries for network operations and more efficient algorithms.

 TODO: Learn more about Boost to give more details regarding the libraries
*/

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>
#endif //LIBRARIES_H

