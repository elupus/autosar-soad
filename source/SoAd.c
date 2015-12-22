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

const SoAd_ConfigType * SoAd_Config = NULL_PTR;

void SoAd_Init(const SoAd_ConfigType* config)
{
    SoAd_Config = config;
}

void SoAd_RxIndication(
        TcpIp_SocketIdType          id,
        const TcpIp_SockAddrType*   remote,
        uint8*                      BufPtr,
        uint16                      Length
    )
{
}

void SoAd_TcpIpEvent(
        TcpIp_SocketIdType          SocketId,
        TcpIp_EventType             Event
    )
{
}

void SoAd_TxConfirmation(
        TcpIp_SocketIdType          SocketId,
        uint16                      Length
    )
{
}

Std_ReturnType SoAd_TcpAccepted(
        TcpIp_SocketIdType          SocketId,
        TcpIp_SocketIdType          SocketIdConnected,
        const TcpIp_SockAddrType*   RemoteAddrPtr
    )
{
    return E_NOT_OK;
}

void SoAd_TcpConnected(
        TcpIp_SocketIdType SocketId
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
