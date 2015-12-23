/* Copyright (C) 2015 Joakim Plate
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "Std_Types.h"
#include "ComStack_Types.h"
#include "SoAd.h"
#include <string.h>

#if(SOAD_CFG_ENABLE_DEVELOPMENT_ERROR == STD_ON)
#include "Det.h"
#define SOAD_DET_ERROR(api, error) Det_ReportError(SOAD_MODULEID, SOAD_INSTANCEID, api, error)
#define SOAD_DET_CHECK_RET(check, api, error)        \
    do {                                             \
        if (!(check)) {                              \
            (void)Det_ReportError(SOAD_MODULEID      \
                                , SOAD_INSTANCEID    \
                                , api                \
                                , error);            \
            return E_NOT_OK;                         \
        }                                            \
    } while(0)

#else
#define SOAD_DET_ERROR(api, error)
#define SOAD_DET_CHECK_RET(check, api, error)
#endif

const SoAd_ConfigType * SoAd_Config = NULL_PTR;

typedef struct {
    TcpIp_SocketIdType        socket_id;
    TcpIp_SockAddrStorageType remote;
    SoAd_SoConStateType       state;
} SoAd_SoConStatusType;

typedef struct {
    TcpIp_SocketIdType        socket_id;
} SoAd_SoGrpStatusType;

SoAd_SoConStatusType SoAd_SoConStatus[SOAD_CFG_CONNECTION_COUNT];
SoAd_SoGrpStatusType SoAd_SoGrpStatus[SOAD_CFG_CONNECTIONGROUP_COUNT];

static void SoAd_SockAddrCopy(TcpIp_SockAddrStorageType* trg, const TcpIp_SockAddrType* src)
{
    switch (src->domain) {
        case TCPIP_AF_INET:
            trg->inet = *(const TcpIp_SockAddrInetType*)src;
            break;
        case TCPIP_AF_INET6:
            trg->inet6 = *(const TcpIp_SockAddrInet6Type*)src;
            break;
        default:
            break;
    }
}

/**
 * @brief Check if a socket address contains any wildcards
 * @param[in] addr Socket address to check
 * @return TRUE if socket address contain any wildcards
 */
static boolean SoAd_SockAddrWildcard(const TcpIp_SockAddrType* addr)
{
    boolean res = FALSE;
    switch (addr->domain) {
        case TCPIP_AF_INET: {
                const TcpIp_SockAddrInetType* inet = (const TcpIp_SockAddrInetType*)addr;
                if (inet->addr[0] == TCPIP_IPADDR_ANY) {
                    res = TRUE;
                }

                if (inet->port == TCPIP_PORT_ANY) {
                    res = TRUE;
                }
            }
            break;
        case TCPIP_AF_INET6: {
                const TcpIp_SockAddrInet6Type* inet6 = (const TcpIp_SockAddrInet6Type*)addr;
                if ((inet6->addr[0] == TCPIP_IPADDR_ANY)
                &&  (inet6->addr[1] == TCPIP_IPADDR_ANY)
                &&  (inet6->addr[2] == TCPIP_IPADDR_ANY)
                &&  (inet6->addr[3] == TCPIP_IPADDR_ANY)) {
                    res = TRUE;
                }

                if (inet6->port == TCPIP_PORT_ANY) {
                    res = TRUE;
                }
            }
            break;
        default:
            break;
    }
    return res;
}

static void SoAd_Init_SoCon(SoAd_SoConIdType id)
{
    const SoAd_SoConConfigType* config = SoAd_Config->connections[id];
    SoAd_SoConStatusType*       status = &SoAd_SoConStatus[id];

    memset(status, 0, sizeof(*status));
    if (config->remote) {
        SoAd_SockAddrCopy(&status->remote, config->remote);
    } else {
        status->remote.base.domain = (TcpIp_DomainType)0u;
    }
    status->socket_id = TCPIP_SOCKETID_INVALID;

    /** @req SWS_SoAd_00723 */
    status->state     = SOAD_SOCON_OFFLINE;
}

static void SoAd_Init_SoGrp(SoAd_SoGrpIdType id)
{
    const SoAd_SoGrpConfigType* config = SoAd_Config->groups[id];
    SoAd_SoGrpStatusType*       status = &SoAd_SoGrpStatus[id];
    memset(status, 0, sizeof(*status));
    status->socket_id = TCPIP_SOCKETID_INVALID;
}

void SoAd_Init(const SoAd_ConfigType* config)
{
    uint16 id;

    SoAd_Config       = config;


    /** @req SWS_SoAd_00723 */
    for (id = 0u; id < SOAD_CFG_CONNECTION_COUNT; ++id) {
        SoAd_Init_SoCon(id);
    }

    for (id = 0u; id < SOAD_CFG_CONNECTIONGROUP_COUNT; ++id) {
        SoAd_Init_SoGrp(id);
    }
}

void SoAd_RxIndication(
        TcpIp_SocketIdType          socket_id,
        const TcpIp_SockAddrType*   remote,
        uint8*                      buf,
        uint16                      len
    )
{
}

void SoAd_TcpIpEvent(
        TcpIp_SocketIdType          socket_id,
        TcpIp_EventType             event
    )
{
}

void SoAd_TxConfirmation(
        TcpIp_SocketIdType          socket_id,
        uint16                      len
    )
{
}

Std_ReturnType SoAd_TcpAccepted(
        TcpIp_SocketIdType          socket_id,
        TcpIp_SocketIdType          socket_id_connected,
        const TcpIp_SockAddrType*   remote
    )
{
    return E_NOT_OK;
}

void SoAd_TcpConnected(
        TcpIp_SocketIdType          socket_id
    )
{
}

BufReq_ReturnType SoAd_CopyTxData(
        TcpIp_SocketIdType          socket_id,
        uint8*                      buf,
        uint16                      len
    )
{
    return BUFREQ_E_NOT_OK;
}

Std_ReturnType SoAd_IfTransmit(
        PduIdType                   pdu_id,
        const PduInfoType*          pdu_info
    )
{
    const SoAd_PduRouteType*    route;
    const SoAd_SoConStatusType* status;
    const SoAd_SoConConfigType* config;
    const SoAd_SoGrpConfigType* group;
    Std_ReturnType              res;


    /**
     * @req SWS_SoAd_00213
     */
    SOAD_DET_CHECK_RET(SoAd_Config != NULL_PTR
                     , SOAD_API_IFTRANSMIT
                     , SOAD_E_NOTINIT);

    /**
     * @req SWS_SoAd_00214
     */
    SOAD_DET_CHECK_RET(pdu_id < SOAD_CFG_PDUROUTE_COUNT
                     , SOAD_API_IFTRANSMIT
                     , SOAD_E_INV_PDUID);

    /**
     * @req SWS_SoAd_00653-TODO
     */

    route  = SoAd_Config->pdu_routes[pdu_id];
    status = &SoAd_SoConStatus[route->destination.connection];
    config = SoAd_Config->connections[route->destination.connection];
    group  = SoAd_Config->groups[config->group];

    if (status->state == SOAD_SOCON_ONLINE) {
        res = E_OK;
    } else {
        res = E_NOT_OK;
    }

    switch(group->protocol) {
        case TCPIP_IPPROTO_TCP:
            res = TcpIp_UdpTransmit(status->socket_id
                                   , pdu_info->SduDataPtr
                                   , &status->remote.base
                                   , pdu_info->SduLength);
            break;
        case TCPIP_IPPROTO_UDP:
            res = TcpIp_TcpTransmit(status->socket_id
                                  , pdu_info->SduDataPtr
                                  , pdu_info->SduLength
                                  , TRUE);
            break;
        default:
            res = E_NOT_OK;
            break;
    }

    return res;
}

void SoAd_SoCon_State_Online(SoAd_SoConIdType id)
{
    const SoAd_SoConConfigType* config = SoAd_Config->connections[id];

}

void SoAd_SoCon_State_Reconnect(SoAd_SoConIdType id)
{
    const SoAd_SoConConfigType* config = SoAd_Config->connections[id];

}
void SoAd_SoCon_State_Offline(SoAd_SoConIdType id)
{
}

void SoAd_SoCon_MainFunction(SoAd_SoConIdType id)
{
    SoAd_SoConStatusType* status = &SoAd_SoConStatus[id];

    switch(status->state) {
        case SOAD_SOCON_OFFLINE:
            SoAd_SoCon_State_Offline(id);
            break;
        case SOAD_SOCON_RECONNECT:
            SoAd_SoCon_State_Reconnect(id);
            break;
        case SOAD_SOCON_ONLINE:
            SoAd_SoCon_State_Online(id);
            break;
        default:
            break;
    }
}

void SoAd_MainFunction(void)
{
    SoAd_SoConIdType id;
    for (id = 0u; id < SOAD_CFG_CONNECTION_COUNT; ++id) {
        SoAd_SoCon_MainFunction(id);
    }
}
