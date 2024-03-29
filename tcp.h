extern int tcpListen(struct sockaddr_in *addr, uint16_t port);
extern void tcpClose(int fd, uint16_t port);
extern int tcpSelect(int nfds, fd_set *readfds);
extern int tctpAccept(struct sockaddr_in *addr, int listener);
extern void tcpSend(int fd, const char *data, int len);