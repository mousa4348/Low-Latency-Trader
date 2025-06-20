#include "libraries.h"
#include "WebSocketClient.h"

WebSocketClient::WebSocketClient()
{
	client.init_asio();
	client.set_open_handler([this](websocketpp::connection_hdl hdl)
		{
			connection_hdl = hdl;
			std::cout << "Connection opened. " << std::endl;
		});

	client.set_message_handler([this](websocketpp::connection_hdl,
		websocketpp::config::asio_client::message_type::ptr msg)
		{
			if (message_callback)
			{
				message_callback(msg->get_payload());
			}
		});

	client.set_fail_handler([](websocketpp::connection_hdl)
		{
			std::cout << "Connection failed. " << std::endl;
		});
	client.set_close_handler([](websocketpp::connection_hdl) {

		std::cout << "Connection closed. " << std::endl;
		});
}

WebSocketClient::~WebSocketClient()
{ }

void WebSocketClient::connect(const std::string& uri)
{
	websocketpp::lib::error_code ec;
	auto con = client.get_connection(uri, ec);
	if (ec)
	{
		std::cout << "Could not get connection. Error code: " << ec.message() << std::endl;
		return;
	}
	client.connect(con);
}
void WebSocketClient::setOnMessage(on_message_callback callback)
{
	message_callback = callback;
}
void WebSocketClient::run()
{
	client.run();
}
void WebSocketClient::send(const std::string& message)
{
	websocketpp::lib::error_code ec;
	client.send(connection_hdl, message, websocketpp::frame::opcode::text, ec);
	if (ec)
	{
		std::cout << "Send error. Error code: " << ec.message() << std::endl;
		return;
	}
}