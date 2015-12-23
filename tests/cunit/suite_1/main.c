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

#include "SoAd.c"

#include "CUnit/Basic.h"
#include "CUnit/Automated.h"

struct suite_state {
    uint8 dummy;
};

struct suite_state suite_state;

const SoAd_SoGrpConfigType           socket_group_1;
const SoAd_SocketRouteType           socket_route_1;

const SoAd_SoConConfigType           socket_conn_1 = {
    .group = 0u,
};

const SoAd_PduRouteType              pdu_route_1;

const SoAd_ConfigType config = {
    .groups = {
        &socket_group_1,
    },

    .connections = {
        &socket_conn_1,
    },

    .socket_routes     = {
        &socket_route_1,
    },

    .pdu_routes        = {
        &pdu_route_1,
    },
};

Std_ReturnType Det_ReportError(
        uint16 ModuleId,
        uint8 InstanceId,
        uint8 ApiId,
        uint8 ErrorId
    )
{
    return E_OK;
}

Std_ReturnType TcpIp_UdpTransmit(
        TcpIp_SocketIdType          id,
        const uint8*                data,
        const TcpIp_SockAddrType*   remote,
        uint16                      len
    )
{
    return E_NOT_OK;
}

Std_ReturnType TcpIp_TcpTransmit(
        TcpIp_SocketIdType  id,
        const uint8*        data,
        uint32              aailable,
        boolean             force
    )
{
    return E_NOT_OK;
}

int suite_init(void)
{
    SoAd_Init(&config);
    return 0;
}

int suite_clean(void)
{
    return 0;
}

void suite_test_1()
{
}

void main_add_generic_suite(CU_pSuite suite)
{
    CU_add_test(suite, "test_1"             , suite_test_1);
}

int main(void)
{
    CU_pSuite suite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

    /* add a suite to the registry */
    suite = CU_add_suite("Suite_Generic", suite_init, suite_clean);
    main_add_generic_suite(suite);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Run results and output to files */
    CU_automated_run_tests();
    CU_list_tests_to_file();

    CU_cleanup_registry();
    return CU_get_error();
}
