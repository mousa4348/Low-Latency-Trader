#pragma once
#include "libraries.h"
#include <iostream>
#include <string>

class WebSocketClient
{
public:
	using on_message_callback = std::function<void(const std::string&)>;

	WebSocketClient();
	~WebSocketClient();

	void connect(const std::string& uri);
	void send(const std::string& message);
	void setOnMessage(on_message_callback callback);
	void run();
private:
	websocketpp::client<websocketpp::config::asio_client> client;
	websocketpp::connection_hdl connection_hdl;
	on_message_callback message_callback;



};