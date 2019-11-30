/*
 * Copyright (c) 2009, Sun Microsystems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of Sun Microsystems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * rpc.h, Just includes the billions of rpc header files necessary to
 * do remote procedure calling.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */
#ifndef _TIRPC_RPC_H
#define _TIRPC_RPC_H

#include <rpc/types.h>		/* some typedefs */
#include <sys/socket.h>
#include <netinet/in.h>

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */

/*
 *  Uncomment-out the next line if you are building the rpc library with
 *  DES Authentication (see the README file in the secure_rpc/ directory).
 */
#include <rpc/auth_des.h>	/* protocol for des style cred */

/* Server side only remote procedure callee */
#include <rpc/svc_auth.h>	/* service side authenticator */
#include <rpc/svc.h>		/* service manager and multiplexer */

/* Portmapper client, server, and protocol headers */
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>

#ifndef _KERNEL
#include <rpc/rpcb_clnt.h>	/* rpcbind interface functions */
#include <rpc/svc_mt.h>
#endif
#include <rpc/rpcent.h>

#ifndef UDPMSGSIZE
#define UDPMSGSIZE 8800
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int get_myaddress(struct sockaddr_in *);
extern int bindresvport(int, struct sockaddr_in *) __THROW;;
extern int registerrpc(int, int, int, char *(*)(char [UDPMSGSIZE]),
    xdrproc_t, xdrproc_t);
extern int callrpc(const char *, int, int, int, xdrproc_t, void *,
    xdrproc_t , void *);
extern int getrpcport(char *, int, int, int);

char *taddr2uaddr(const struct netconfig *, const struct netbuf *);
struct netbuf *uaddr2taddr(const struct netconfig *, const char *);

struct sockaddr;
extern int bindresvport_sa(int, struct sockaddr *) __THROW;;
#ifdef __cplusplus
}
#endif

/*
 * The following are not exported interfaces, they are for internal library
 * and rpcbind use only. Do not use, they may change without notice.
 */
#ifdef __cplusplus
extern "C" {
#endif
int __rpc_nconf2fd(const struct netconfig *);
int __rpc_nconf2fd_flags(const struct netconfig *, int);
int __rpc_nconf2sockinfo(const struct netconfig *, struct __rpc_sockinfo *);
int __rpc_fd2sockinfo(int, struct __rpc_sockinfo *);
u_int __rpc_get_t_size(int, int, int);
#ifdef __cplusplus
}
#endif

#endif /* !_RPC_RPC_H */
