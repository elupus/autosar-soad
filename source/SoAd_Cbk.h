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

/**
 * @file
 * @ingroup SoAd
 */

#ifndef SOAD_CBK_H_
#define SOAD_CBK_H_

#include "Std_Types.h"
#include "TcpIp.h"
#include "ComStack_Types.h"

void SoAd_RxIndication(
        TcpIp_SocketIdType          socket_id,
        const TcpIp_SockAddrType*   remote,
        uint8*                      buf,
        uint16                      len
    );

void SoAd_TcpIpEvent(
        TcpIp_SocketIdType          socket_id,
        TcpIp_EventType             event
    );

void SoAd_TxConfirmation(
        TcpIp_SocketIdType          socket_id,
        uint16                      len
    );

Std_ReturnType SoAd_TcpAccepted(
        TcpIp_SocketIdType          socket_id,
        TcpIp_SocketIdType          socket_id_connected,
        const TcpIp_SockAddrType*   remote
    );

void SoAd_TcpConnected(
        TcpIp_SocketIdType 			socket_id
    );

BufReq_ReturnType SoAd_CopyTxData(
        TcpIp_SocketIdType 			socket_id,
        uint8* 						buf,
        uint16 						len
    );

#endif /* SOAD_CBK_H_ */
