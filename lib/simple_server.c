#include "simple_server.h"

#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
references:
https://www.die.net/
https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
*/
#define BUF_SIZE 1024
#define LISTEN_QUEUE_SIZE 10

typedef struct simple_server{
    int sock;

    // clients
    int* clients;
    int clients_sz;

    // read buffer
    char* buf;
    int buf_sz;

    // callbacks
    void* connected_ctx;
    void* disconnected_ctx;
    void* data_rcvd_ctx;
    cnxn_callback connected_cb;
    cnxn_callback disconnected_cb;
    data_callback data_rcvd_cb;
} server_t;

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;

static void noop_cnxn_cb(void* a, int b){ (void)a, (void)b;}
static void noop_data_cb(void* a, int b, const char* c, int d)
{ (void)a, (void)b, (void)c, (void)d; }

server_t* create_server(int port) {
    server_t* s = calloc(1, sizeof(server_t));
    s->buf_sz = BUF_SIZE;
    s->buf = malloc(s->buf_sz);
    s->connected_cb = noop_cnxn_cb;
    s->disconnected_cb = noop_cnxn_cb;
    s->data_rcvd_cb = noop_data_cb;

    int allow_multiple_cnxn = 1;
    sockaddr_in_t address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int ok = 1;
    ok = ok && (s->sock = socket(AF_INET , SOCK_STREAM , 0)) != 0;
    ok = ok && setsockopt(s->sock, SOL_SOCKET, SO_REUSEADDR,
        (char*)&allow_multiple_cnxn, sizeof(allow_multiple_cnxn)) == 0;
    ok = ok && bind(s->sock, (sockaddr_t*)&address, sizeof(address)) == 0;
    ok = ok && listen(s->sock, LISTEN_QUEUE_SIZE) == 0;

    if (!ok) {
        destroy_server(s), s = 0;
    }
    return s;
}

void destroy_server(server_t* s) {
    if (s) {
        for (int i = 0; i < s->clients_sz; ++i) {
            s->disconnected_cb(s->disconnected_ctx, s->clients[i]);
            close(s->clients[i]);
        }
        free(s->clients);
        free(s->buf);
        free(s);
    }
}

int poll_clients(server_t* s, struct timeval* timeout) {
    fd_set fds;
    FD_ZERO(&fds);

    // add server socket to set
    FD_SET(s->sock, &fds);
    int max_sd = s->sock;

    // add child sockets to set
    for (int i = 0; i < s->clients_sz; ++i) {
        const int sd = s->clients[i];
        FD_SET(sd, &fds);
        max_sd = sd > max_sd ? sd : max_sd;
    }

    if (select(max_sd + 1, &fds, NULL, NULL, timeout) < 0)  {
        // todo: handle select failure
    }

    // s->sock being active indicates an incoming client connection
    if (FD_ISSET(s->sock, &fds)) {
        sockaddr_in_t address;
        int addrlen = sizeof(sockaddr_in_t);
        const int new_socket =
            accept(s->sock, (sockaddr_t*)&address, (socklen_t*)&addrlen);

        if (new_socket < 0) {
            // todo: handle accept failure
        } else {
            s->clients =
                realloc(s->clients, (s->clients_sz + 1) * sizeof(int));
            s->clients[s->clients_sz++] = new_socket;
            s->connected_cb(s->connected_ctx, new_socket);
        }
    }

    // check for client input
    for (int i = 0; i < s->clients_sz; ++i) {
        /* !!! NOTE removing a socket invalidates s->clients[i],
            which means we should only use sd in this loop.
        */
        const int sd = s->clients[i];

        if (FD_ISSET(sd, &fds)) {
            const int valread = read(sd, s->buf, s->buf_sz);
            if (valread < 0) {
                // todo: handle read error;
            } else if (valread == 0) {
                s->disconnected_cb(s->disconnected_ctx, sd);
                close(sd);
                s->clients_sz--;
                s->clients[i] = s->clients[s->clients_sz];
            } else {
                s->data_rcvd_cb(s->data_rcvd_ctx, sd, s->buf, valread);
            }
        }
    }
    return 0;
}

void set_data_received_callback(server_t* s, void* ctx, data_callback c) {
    assert(c);
    s->data_rcvd_ctx = ctx;
    s->data_rcvd_cb = c;
}
void set_connected_callback(server_t* s, void* ctx, cnxn_callback c) {
    assert(c);
    s->connected_ctx = ctx;
    s->connected_cb = c;
}
void set_disconnected_callback(server_t* s, void* ctx, cnxn_callback c) {
    assert(c);
    s->disconnected_ctx = ctx;
    s->disconnected_cb = c;
}
