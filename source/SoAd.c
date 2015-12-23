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
    SoAd_SoConStateType       state;
} SoAd_SoConStatusType;

SoAd_SoConStatusType SoAd_SoConStatus[SOAD_CFG_CONNECTION_COUNT];


static void SoAd_Init_SoCon(SoAd_SoConIdType id)
{
    SoAd_SoConStatusType*       status = &SoAd_SoConStatus[id];
    status->socket_id = TCPIP_SOCKETID_INVALID;
    status->state     = SOAD_SOCON_OFFLINE;
}

void SoAd_Init(const SoAd_ConfigType* config)
{
    SoAd_SoConIdType id;
    SoAd_Config = config;

    memset(SoAd_SoConStatus, 0, sizeof(SoAd_SoConStatus));

    for (id = 0u; id < SOAD_CFG_CONNECTION_COUNT; ++id) {
        SoAd_Init_SoCon(id);
    }
}

void SoAd_RxIndication(
        TcpIp_SocketIdType          id,
        const TcpIp_SockAddrType*   remote,
        uint8*                      buf,
        uint16                      len
    )
{
}

void SoAd_TcpIpEvent(
        TcpIp_SocketIdType          id,
        TcpIp_EventType             event
    )
{
}

void SoAd_TxConfirmation(
        TcpIp_SocketIdType          id,
        uint16                      len
    )
{
}

Std_ReturnType SoAd_TcpAccepted(
        TcpIp_SocketIdType          id,
        TcpIp_SocketIdType          id_connected,
        const TcpIp_SockAddrType*   remote
    )
{
    return E_NOT_OK;
}

void SoAd_TcpConnected(
        TcpIp_SocketIdType id
    )
{
}

BufReq_ReturnType SoAd_CopyTxData(
        TcpIp_SocketIdType SocketId,
        uint8* BufPtr,
        uint16 BufLength
    )
{
    return BUFREQ_E_NOT_OK;
}


void SoAd_SoCon_MainFunction(SoAd_SoConIdType id)
{
    SoAd_SoConStatusType* status = &SoAd_SoConStatus[id];

    switch(status->state) {
        case SOAD_SOCON_OFFLINE:
            break;
        case SOAD_SOCON_RECONNECT:
            break;
        case SOAD_SOCON_ONLINE:
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
