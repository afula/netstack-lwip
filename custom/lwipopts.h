/**
 * @file lwipopts.h
 * @author Ambroz Bizjak <ambrop7@gmail.com>
 *
 * @section LICENSE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LWIP_CUSTOM_LWIPOPTS_H
#define LWIP_CUSTOM_LWIPOPTS_H

// enable tun2socks logic
#define TUN2SOCKS 1

#define NO_SYS 1
#define LWIP_TIMERS 1

#define IP_DEFAULT_TTL 64
#define LWIP_ARP 0
#define ARP_QUEUEING 0
#define IP_FORWARD 0
#define LWIP_ICMP 0
#define LWIP_RAW 1
#define LWIP_DHCP 0
#define LWIP_AUTOIP 0
#define LWIP_SNMP 0
#define LWIP_IGMP 0
#define LWIP_DNS 0
#define LWIP_UDP 1
#define LWIP_UDPLITE 0
#define LWIP_TCP 1
#define LWIP_CALLBACK_API 1
#define LWIP_NETIF_API 0
#define LWIP_NETIF_LOOPBACK 0
#define LWIP_HAVE_LOOPIF 1
#define LWIP_HAVE_SLIPIF 0
#define LWIP_NETCONN 0
#define LWIP_SOCKET 0
#define PPP_SUPPORT 0
#define LWIP_IPV6 1
#define LWIP_IPV6_MLD 0
#define LWIP_IPV6_AUTOCONFIG 1

#if defined __APPLE__
#include <TargetConditionals.h>
#include <stdlib.h>

#if TARGET_OS_IPHONE
#define LWIP_TCP_KEEPALIVE 1
#define MEMP_NUM_TCP_PCB 256
#else
#define MEMP_NUM_TCP_PCB 4096
#endif
#elif defined __linux__
#include <endian.h>
#include <stdlib.h>

// BYTE_ORDER by default is LITTLE_ENDIAN if undefined,
// detects only big endian here.
#if defined __BYTE_ORDER && defined __BIG_ENDIAN
#if _BYTE_ORDER == __BIG_ENDIAN
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif

#define MEMP_NUM_TCP_PCB 1024
#else
#define MEMP_NUM_TCP_PCB 1024
#endif

// disable checksum checks
#define CHECKSUM_CHECK_IP 0
#define CHECKSUM_CHECK_UDP 0
#define CHECKSUM_CHECK_TCP 0
#define CHECKSUM_CHECK_ICMP 0
#define CHECKSUM_CHECK_ICMP6 0

#define LWIP_CHECKSUM_ON_COPY 1
#define LWIP_CHKSUM_ALGORITHM 3

#define TCP_MSS 8191
#define TCP_WND (8 * TCP_MSS)
#define TCP_SND_BUF (8 * TCP_MSS)
/**
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work.
 */
#define TCP_SND_QUEUELEN                ((128 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))



#if defined __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define MEM_SIZE (512 * 1024)
#else
#define MEM_SIZE (2 * 1024 * 1024)
#endif
#else
#define MEM_SIZE (2 * 1024 * 1024)
#endif

#define MEMP_NUM_TCP_SEG 8192
#define PBUF_POOL_SIZE 32

// #define TCP_MSS 1460
// #define TCP_WND (16 * TCP_MSS)
// #define TCP_SND_BUF (8 * TCP_MSS)
// #define MEM_LIBC_MALLOC 1
// #define MEMP_MEM_MALLOC 1

#define SYS_LIGHTWEIGHT_PROT 0
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS

// needed on 64-bit systems, enable it always so that the same configuration
// is used regardless of the platform
#define IPV6_FRAG_COPYHEADER 1

#define LWIP_DEBUG 0
#define LWIP_DBG_MIN_LEVEL LWIP_DBG_LEVEL_ALL
#define LWIP_DBG_TYPES_ON LWIP_DBG_OFF
#define NETIF_DEBUG LWIP_DBG_OFF
#define PBUF_DEBUG LWIP_DBG_OFF
#define INET_DEBUG LWIP_DBG_OFF
#define IP_DEBUG LWIP_DBG_OFF
#define IP_REASS_DEBUG LWIP_DBG_OFF
#define RAW_DEBUG LWIP_DBG_OFF
#define MEM_DEBUG LWIP_DBG_OFF
#define MEMP_DEBUG LWIP_DBG_OFF
#define SYS_DEBUG LWIP_DBG_OFF
#define TIMERS_DEBUG LWIP_DBG_OFF
#define TCP_DEBUG LWIP_DBG_ON
#define TCP_INPUT_DEBUG LWIP_DBG_OFF
#define TCP_RTO_DEBUG LWIP_DBG_OFF
#define TCP_CWND_DEBUG LWIP_DBG_OFF
#define TCP_WND_DEBUG LWIP_DBG_OFF
#define TCP_RST_DEBUG LWIP_DBG_ON
#define TCP_QLEN_DEBUG LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG LWIP_DBG_ON
#define UDP_DEBUG LWIP_DBG_OFF
#define TCPIP_DEBUG LWIP_DBG_OFF
#define IP6_DEBUG LWIP_DBG_OFF

#define LWIP_STATS 0
#define LWIP_STATS_DISPLAY 0
#define LWIP_PERF 0

/*
   ------------------------------------
   ---------- Memory options ----------
   ------------------------------------
*/

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#define MEM_ALIGNMENT                   4U

/**
 * MEM_CUSTOM_ALLOCATOR==1: Use malloc/free/realloc provided by a custom
 * implementation instead of the lwip internal allocator. Can save code size if
 * you already use it. If enabled, you have to define those functions:
 */
#define MEM_CUSTOM_ALLOCATOR            1

void hev_free (void *ptr);
#define MEM_CUSTOM_FREE hev_free

void *hev_malloc (size_t size);
#define MEM_CUSTOM_MALLOC hev_malloc

void *hev_calloc (size_t nmemb, size_t size);
#define MEM_CUSTOM_CALLOC hev_calloc

/*
   ------------------------------------------------
   ---------- Internal Memory Pool Sizes ----------
   ------------------------------------------------
*/
/**
 * MEMP_NUM_PBUF: the number of memp struct pbufs (used for PBUF_ROM and PBUF_REF).
 * If the application sends a lot of data out of ROM (or other static memory),
 * this should be set high.
 */
#define MEMP_NUM_PBUF                   8192

/**
 * MEMP_NUM_RAW_PCB: Number of raw connection PCBs
 * (requires the LWIP_RAW option)
 */
#define MEMP_NUM_RAW_PCB                4

/**
 * MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
 * per active UDP "connection".
 * (requires the LWIP_UDP option)
 */
#define MEMP_NUM_UDP_PCB                1024

/**
 * MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections.
 * (requires the LWIP_TCP option)
 */
#define MEMP_NUM_TCP_PCB_LISTEN         16

/**
 * MEMP_NUM_REASSDATA: the number of simultaneously IP packets queued for
 * reassembly (whole packets, not fragments!)
 */
#define MEMP_NUM_REASSDATA              1

/**
 * MEMP_NUM_ARP_QUEUE: the number of simulateously queued outgoing
 * packets (pbufs) that are waiting for an ARP request (to resolve
 * their destination address) to finish.
 * (requires the ARP_QUEUEING option)
 */
#define MEMP_NUM_ARP_QUEUE              2

/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts.
 * (requires NO_SYS==0)
 */
#define MEMP_NUM_SYS_TIMEOUT            8

/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETBUF                 2

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#define MEMP_NUM_NETCONN               32

/**
 * MEMP_NUM_TCPIP_MSG_API: the number of struct tcpip_msg, which are used
 * for callback/timeout API communication.
 * (only needed if you use tcpip.c)
 */
#define MEMP_NUM_TCPIP_MSG_API          8

/**
 * MEMP_NUM_TCPIP_MSG_INPKT: the number of struct tcpip_msg, which are used
 * for incoming packets.
 * (only needed if you use tcpip.c)
 */
#define MEMP_NUM_TCPIP_MSG_INPKT        8

/*
   ----------------------------------
   ---------- Pbuf options ----------
   ----------------------------------
*/
/**
 * PBUF_LINK_HLEN: the number of bytes that should be allocated for a
 * link level header. The default is 14, the standard value for
 * Ethernet.
 */
#define PBUF_LINK_HLEN                  16

/**
 * PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. The default is
 * designed to accommodate single full size TCP frame in one pbuf, including
 * TCP_MSS, IP header, and link header.
*
 */
#define PBUF_POOL_BUFSIZE               LWIP_MEM_ALIGN_SIZE(TCP_MSS+40+PBUF_LINK_HLEN)


/*
   ---------------------------------------
   ---------- Threading options ----------
   ---------------------------------------
*/

#define LWIP_TCPIP_CORE_LOCKING    1

#if !NO_SYS
void sys_check_core_locking(void);
#define LWIP_ASSERT_CORE_LOCKED()  sys_check_core_locking()
#endif



#endif
