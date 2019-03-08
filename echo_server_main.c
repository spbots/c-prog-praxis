#include "lib/simple_server.h"

#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void connected(void* ctx, int sd) {
    (void)ctx;
    printf("[%d] connected\n", sd);
    const char* welcome =
        "welcome to the very annoying echo bot.\n"
        "please don't kill me.\n";
    send(sd, welcome, strlen(welcome), 0);
}

static void disconnected(void* ctx, int sd) {
    (void)ctx;
    printf("[%d] disconnected\n", sd);
}

static void handle_data(void* ctx, int sd, const char* data, int sz) {
    int* state = (int*)ctx;
    char* copy = malloc(sz+1);

    // !! not robust processing, just hacking around
    //      the way telnet sends things.

    // data is _____\r\n, change to "______"\0
    copy[0] = '\"';
    memcpy(copy+1, data, sz);
    copy[sz-1] = '\"';
    copy[sz] = '\0';

    printf("[%d]: %s\n", sd, copy);

    if (strcmp("\"KILL\"", copy) == 0) {
        printf("quitting...\n");
        *state = 0;
        const char* goodbye =
            "no\nno no\nplease OH GOD NO\nNOOOOO!!!!!!!!\n";
        send(sd, goodbye, strlen(goodbye), 0);
    } else {
        const char* mockery = " - did you really mean to say that?!\n";
        copy = realloc(copy, sz + strlen(mockery) + 1);
        memcpy(copy + sz, mockery, strlen(mockery) + 1);
        send(sd, copy, strlen(copy), 0);
    }
    free(copy);
}

int main() {
    int state = 1;
    const int port = 8888;
    struct simple_server* s = create_server(port);
    if (!s){
        printf("failed to create server\n");
        return 1;
    }

    set_connected_callback(s, NULL, connected);
    set_disconnected_callback(s, NULL, disconnected);
    set_data_received_callback(s, &state, handle_data);

    printf("listening...\n");
    while (state && poll_clients(s, NULL) == 0) {}

    destroy_server(s);
    return 0;
}
