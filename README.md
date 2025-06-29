# Low Latency Trader

This application uses cURL to use the most up-to-date data on stocks. It allows for three options:

1. Buy and sell a stock. In the buy hub, the user MUST have a balance to buy stocks. In the sell section, the user MUST have stocks to sell.
2. Check a stock. So long as it is a valid ticker.
3. Check and change balance. This allows the user to add a certain (fake) balance.

# Regarding WebSocketClient

WebSocketClient generally should do the same thing as cURL, but it's very useful for getting real-time data. This is a WIP. I don't really know
how to fully make use of it properly
