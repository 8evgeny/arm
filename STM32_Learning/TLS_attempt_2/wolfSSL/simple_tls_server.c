/*************************************************
 Copyright (c) 2020
 All rights reserved.
 File name:     simple_tls_server.c
 Description:
 History:
 1. Version:
    Date:       2020-11-30
    Author:     wangjunjie
    Modify:
*************************************************/

#include <rtthread.h>

/* socket */
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>

/* wolfSSL */
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

#define TLS_SERVER_PORT    3334
#define TCP_LISTEN_BACKLOG 5
#define TLS_BUFF_SIZE      1024

#define SERVER_KEY_PATH  "/sdcard/certs/server.key"
#define SERVER_CERT_PATH "/sdcard/certs/server.crt"

static int listen_socket_create(void) {
    int sockfd = -1, reuse = 1;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("create socket failed.\r\n");
        return -1;
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    rt_memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TLS_SERVER_PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        printf("socket %d bind failed.\r\n", sockfd);
        closesocket(sockfd);
        return -1;
    }

    if (listen(sockfd, TCP_LISTEN_BACKLOG) < 0) {
        printf("socket %d listen failed.\r\n", sockfd);
        closesocket(sockfd);
        return -1;
    }

    return sockfd;
}

static WOLFSSL_CTX *TLS_ctx_create(void) {
    WOLFSSL_CTX *wolfssl_ctx = NULL;
    WOLFSSL_METHOD *method = NULL;

    /* Init wolfSSL library */
    wolfSSL_Init();

    /* Create wolfSSL context */
    method = wolfTLSv1_2_server_method();
    wolfssl_ctx = wolfSSL_CTX_new(method);
    if (wolfssl_ctx == NULL) {
        printf("wolfSSL context create failed.\r\n");
        return NULL;
    }

    /* Load private key and certificate */
    if (wolfSSL_CTX_use_PrivateKey_file(wolfssl_ctx, SERVER_KEY_PATH,
                                        SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        printf("wolfSSL load %s failed.\r\n", SERVER_KEY_PATH);
        goto exit;
    }
    if (wolfSSL_CTX_use_certificate_file(wolfssl_ctx, SERVER_CERT_PATH,
                                         SSL_FILETYPE_PEM) != WOLFSSL_SUCCESS) {
        printf("wolfSSL load %s failed.\r\n", SERVER_CERT_PATH);
        goto exit;
    }

    return wolfssl_ctx;
exit:
    wolfSSL_CTX_free(wolfssl_ctx);
    wolfSSL_Cleanup();
    return NULL;
}

static WOLFSSL *TLS_session_create(int sock, WOLFSSL_CTX *ctx) {
    WOLFSSL *ssl = NULL;

    /* create tls session */
    ssl = wolfSSL_new(ctx);
    if (ssl == NULL) {
        printf("TLS session create failed.\r\n");
        return NULL;
    }

    /* set fd */
    wolfSSL_set_fd(ssl, sock);

    /* do handshake */
    do {
        int ret = wolfSSL_accept(ssl);
        if (ret != SSL_SUCCESS) {
            printf("TLS handshake failed.\r\n");
            wolfSSL_free(ssl);
            return NULL;
        }
    } while (wolfSSL_want_read(ssl));
    return ssl;
}

void tls_server(void *param) {
    int listenfd = -1, clifd = -1;
    struct sockaddr_in cliaddr;
    WOLFSSL_CTX *wolfssl_ctx = NULL;
    socklen_t clilen = sizeof(struct sockaddr_in);

    /* Create listen socket */
    listenfd = listen_socket_create();
    if (listenfd < 0) goto exit;

    /* Create tls context */
    wolfssl_ctx = TLS_ctx_create();
    if (wolfssl_ctx == NULL) goto exit;

    for (;;) {
        WOLFSSL *session = NULL;
        printf("waiting for a new connection.\r\n");

        /* Accept a new connection request */
        clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if (clifd < 0) {
            printf("connection accept failed.\r\n");
            continue;
        }
        printf("new connection comes in,ip:%s port:%d.\r\n",
               netdev_ip4addr_ntoa((ip4_addr_t *)&cliaddr.sin_addr), cliaddr.sin_port);

        /* Create TLS session */
        session = TLS_session_create(clifd, wolfssl_ctx);
        if (session == NULL) {
            closesocket(clifd);
            continue;
        }

        /* Communication */
        while (1) {
            int ret = -1;
            char buff[TLS_BUFF_SIZE];
            rt_memset(buff, 0, sizeof(buff));

            ret = wolfSSL_read(session, buff, sizeof(buff));
            if (ret > 0) {
                wolfSSL_write(session, buff, ret);
            } else {
                break;
            }
        }
        if (clifd > 0) {
            printf("connection close on socket %d .\r\n", clifd);
            closesocket(clifd);
        }
        wolfSSL_free(session);
    }
exit:
    if (listenfd >= 0) closesocket(listenfd);
    wolfSSL_CTX_free(wolfssl_ctx);
    wolfSSL_Cleanup();
}

int tls_server_create(void) {
    rt_thread_t tid = NULL;
    tid = rt_thread_create("sslServer", tls_server, NULL, 6 * 1024, 10, 5);
    if (tid) {
        rt_thread_startup(tid);
        return 0;
    } else {
        printf("ssl server thread create failed.\r\n");
        return -1;
    }
}
