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

#ifndef PDUR_SOAD_H_
#define PDUR_SOAD_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

extern void PduR_SoAdIfRxIndication(
            PduIdType           pdu,
            const PduInfoType*  info
    );

extern Std_ReturnType PduR_SoAdIfTriggerTransmit(
            PduIdType           pdu,
            PduInfoType*        info
    );

extern void PduR_SoAdIfTxConfirmation(
            PduIdType           pdu
    );

extern BufReq_ReturnType PduR_SoAdTpStartOfReception(
        PduIdType               id,
        const PduInfoType*      info,
        PduLengthType           len,
        PduLengthType*          buf_len
    );

extern BufReq_ReturnType PduR_SoAdTpCopyRxData(
        PduIdType               id,
        const PduInfoType*      info,
        PduLengthType*          len
    );

void PduR_SoAdTpRxIndication(
        PduIdType               id,
        Std_ReturnType          result
    );

extern BufReq_ReturnType PduR_SoAdTpCopyTxData(
        PduIdType               id,
        const PduInfoType*      info,
        RetryInfoType*          retry,
        PduLengthType*          available
    );

extern void PduR_SoAdTpTxConfirmation(
        PduIdType               id,
        Std_ReturnType          result
    );

#endif /* PDUR_SOAD_H_ */
