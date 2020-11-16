#ifndef SOCKETFUNCTIONS_H
#define SOCKETFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> // for memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BACKLOG 128 // how many pending connections queue will hold
#define PACK_SIZE 4096

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

int bindUdpSocketFd(char const *port = nullptr);

int connectUdpSocketFd(char const *host, char const *port);

int bindTcpSocketFd(char const *port = nullptr);

int connectTcpSocketFd(char const *host = nullptr, char const *port = nullptr);

#endif
