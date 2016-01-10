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

#ifndef SOAD_H_
#define SOAD_H_

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "TcpIp.h"
#include "SoAd_Cfg.h"

#define SOAD_MODULEID   56u
#define SOAD_INSTANCEID 0u

/**
 * @brief Development Errors
 * @req SWS_SoAd_00101
 * @{
 */

/**
 * @brief API service called before initializing the module
 */
#define SOAD_E_NOTINIT          0x01u

/**
 * @brief API service called with NULL pointer
 */
#define SOAD_E_PARAM_POINTER    0x02u

/**
 * @brief Invalid argument
 */
#define SOAD_E_INV_ARG          0x03u

/**
 * @brief No buffer space available
 */
#define SOAD_E_NOBUFS           0x04u

/**
 * @brief Unknown PduHeader ID
 */
#define SOAD_E_INV_PDUHEADER_ID 0x05u

/**
 * @brief Invalid PDU ID
 */
#define SOAD_E_INV_PDUID        0x06u

/**
 * @brief Invalid socket address
 */
#define SOAD_E_INV_SOCKETID     0x07u

/**
 * @brief Invalid configuration set selection
 */
#define SOAD_E_INIT_FAILED      0x08u

/**
 * @}
 */



/**
 * @brief Service identifier
 * @{
 */
#define SOAD_API_INIT                         0x01u
#define SOAD_API_IFTRANSMIT                   0x03u
#define SOAD_API_RXINDICATION                 0x12u
#define SOAD_API_TCPIPEVENT                   0x16u

/**
 * @}
 */

typedef enum {
    SOAD_SOCON_OFFLINE,
    SOAD_SOCON_RECONNECT,
    SOAD_SOCON_ONLINE,
} SoAd_SoConStateType;

typedef uint8 SoAd_SoConIdType;
typedef uint8 SoAd_SoGrpIdType;
typedef uint8 SoAd_SocketRouteIdType;

#define SOAD_SOCKETROUTEID_INVALID (SoAd_SocketRouteIdType)(-1)
#define SOAD_PDUHEADERID_INVALID   (uint32)(-1)


typedef enum {
    SOAD_UPPER_LAYER_IF,
    SOAD_UPPER_LAYER_TP,
} SoAd_UpperLayerType;


typedef struct {
    BufReq_ReturnType (*start_of_reception)(
        PduIdType               id,
        const PduInfoType*      info,
        PduLengthType           len,
        PduLengthType*          buf_len
    );

    BufReq_ReturnType (*copy_rx_data)(
        PduIdType               id,
        const PduInfoType*      info,
        PduLengthType*          len
    );

    void (*rx_indication)(
        PduIdType               id,
        Std_ReturnType          result
    );
} SoAd_TpRxType;

typedef struct {
    const SoAd_TpRxType*              upper;
    PduIdType                         pdu;                /**< SoAdRxPduRef */
} SoAd_SocketRouteDestType;

typedef struct {
    uint32                            header_id;          /**< SoAdRxPduHeaderId   */
    SoAd_SocketRouteDestType          destination;        /**< SoAdSocketRouteDest */
} SoAd_SocketRouteType;

typedef struct {
    uint16                            localport;          /**< SoAdSocketLocalPort */
    TcpIp_DomainType                  domain;             /**< domain of local interface */
    TcpIp_ProtocolType                protocol;
    boolean                           automatic;          /**< SoAdSocketAutomaticSoConSetup */
    boolean                           initiate;           /**< SoAdSocketTcpInitiate */
    boolean                           listen_only;        /**< SoAdSocketUdpListenOnly */
    boolean                           header;             /**< SoAdPduHeaderEnable */
    SoAd_SocketRouteIdType            socket_route_id;
} SoAd_SoGrpConfigType;

typedef struct {
    SoAd_SoGrpIdType             group;
    const TcpIp_SockAddrType*    remote;
    SoAd_SocketRouteIdType       socket_route_id;
} SoAd_SoConConfigType;

typedef struct {
    uint32                                  header_id;
    SoAd_SoConIdType                        connection;
} SoAd_PduRouteDestType;

typedef struct {
    SoAd_PduRouteDestType                   destination;
} SoAd_PduRouteType;

typedef struct {
    const SoAd_SoGrpConfigType*  groups       [SOAD_CFG_CONNECTIONGROUP_COUNT];
    const SoAd_SoConConfigType*  connections  [SOAD_CFG_CONNECTION_COUNT];
    const SoAd_PduRouteType*     pdu_routes   [SOAD_CFG_PDUROUTE_COUNT];
    const SoAd_SocketRouteType*  socket_routes[SOAD_CFG_SOCKETROUTE_COUNT];
} SoAd_ConfigType;

void SoAd_Init(const SoAd_ConfigType* config);
void SoAd_MainFunction(void);

Std_ReturnType SoAd_IfTransmit(
        PduIdType           pdu_id,
        const PduInfoType*  pdu_info
    );


#endif
