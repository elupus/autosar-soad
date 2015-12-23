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

#ifndef SOAD_H_
#define SOAD_H_

#include "TcpIp.h"

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

/**
 * @}
 */

typedef struct {
    uint8 dummy;
} SoAd_SocketConnection;

typedef struct {
    uint32 headerid;

} SoAd_SocketRoute;

typedef struct {
    uint8 dummy;
} SoAd_ConfigType;

void SoAd_Init(const SoAd_ConfigType* config);
void SoAd_MainFunction(void);

#endif
