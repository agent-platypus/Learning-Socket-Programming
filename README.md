This is a simple "messaging" application between a server and a client 
Requirements: Linux OS and gcc 

Note: The current implementation is very basic; the user enters a message to be transmitted by the server and received by the client, then upon reception, on the client end
the received message is displayed and the client can now send a message back to the server. 

TODO: 

1. Implement multithreading to enable simultaneous message reception and transmission on the server and client.
2. Implement a messaging GUI (using the terminal for messaging is highkey primitive)
3. Implement connection status indicators
4. Implement a method to end/reconnect the messaging session 

To start the application:

Navigate to the directory containing the files.
run 'make' to generate the client and server executables.
Open a separate terminal window to run the client.

For the server:

run './server'

You will be prompted to enter a message, max 100 characters. 

For the client:

run './client'

