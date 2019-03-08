#ifndef simple_server_h
#define simple_server_h

/** A simple multi-client TCP server

This server is single-threaded, using select to support
multiple clients. It is up to the user of this class to
decide on the timeout for polling - if NULL is used,
polling will block until a client responds.
*/
struct simple_server;
struct timeval;

struct simple_server* create_server(int port);
int poll_clients(struct simple_server* srv, struct timeval* timeout);
void destroy_server(struct simple_server* srv);

typedef void (*data_callback) (void*, int/*fd*/, const char*, int /*size*/);
void set_data_received_callback(struct simple_server*, void*, data_callback);

typedef void (*cnxn_callback) (void*, int);
void set_connected_callback(struct simple_server*, void*, cnxn_callback);
void set_disconnected_callback(struct simple_server*, void*, cnxn_callback);

#endif // simple_server_h
