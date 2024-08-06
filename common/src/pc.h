#ifndef PRECOMPILED_H
#define PRECOMPILED_H

// Common precompiled headers

#define LOCAL_ADDRESS "127.0.0.1"

#define SERVER_ADDRESS LOCAL_ADDRESS
#define SERVER_PORT 27015

#define CLIENT_PORT 0 // The client will automatically choose an available port

#define MAX_IP_ADDRESS_LENGTH 17
#define MAX_PORT_LENGTH 7
#define MAX_IP_ADDRESS_WITH_PORT_LENGTH MAX_IP_ADDRESS_LENGTH + MAX_PORT_LENGTH + 2

#endif // PRECOMPILED_H