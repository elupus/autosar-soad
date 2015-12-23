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

Std_ReturnType TcpIp_SoAdGetSocket(
        TcpIp_DomainType            domain,
        TcpIp_ProtocolType          protocol,
        TcpIp_SocketIdType*         id
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
    return E_OK;
}

Std_ReturnType TcpIp_TcpTransmit(
        TcpIp_SocketIdType  id,
        const uint8*        data,
        uint32              aailable,
        boolean             force
    )
{
    return E_OK;
}


Std_ReturnType TcpIp_Bind(
        TcpIp_SocketIdType          id,
        TcpIp_LocalAddrIdType       local,
        uint16* port
    )
{
    return E_OK;
}

Std_ReturnType TcpIp_TcpListen(
        TcpIp_SocketIdType id,
        uint16 channels
    )
{
    return E_OK;
}

Std_ReturnType TcpIp_TcpConnect(
        TcpIp_SocketIdType          id,
        const TcpIp_SockAddrType*   remote
    )
{
    return E_OK;
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

void suite_test_wildcard_v4()
{
    TcpIp_SockAddrInetType inet;
    inet.domain  = TCPIP_AF_INET;

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.port    = TCPIP_PORT_ANY;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = 1u;
    inet.port    = TCPIP_PORT_ANY;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.port    = 1u;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = 1u;
    inet.port    = 1u;
    CU_ASSERT_FALSE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));
}

void suite_test_wildcard_v6()
{
    TcpIp_SockAddrInet6Type inet;
    inet.domain  = TCPIP_AF_INET6;

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.addr[1] = TCPIP_IPADDR_ANY;
    inet.addr[2] = TCPIP_IPADDR_ANY;
    inet.addr[3] = TCPIP_IPADDR_ANY;
    inet.port    = TCPIP_PORT_ANY;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.addr[1] = TCPIP_IPADDR_ANY;
    inet.addr[2] = TCPIP_IPADDR_ANY;
    inet.addr[3] = TCPIP_IPADDR_ANY;
    inet.port    = 1u;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.addr[1] = 1u;
    inet.addr[2] = TCPIP_IPADDR_ANY;
    inet.addr[3] = TCPIP_IPADDR_ANY;
    inet.port    = TCPIP_PORT_ANY;
    CU_ASSERT_TRUE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));

    inet.addr[0] = TCPIP_IPADDR_ANY;
    inet.addr[1] = 1u;
    inet.addr[2] = TCPIP_IPADDR_ANY;
    inet.addr[3] = TCPIP_IPADDR_ANY;
    inet.port    = 1u;
    CU_ASSERT_FALSE(SoAd_SockAddrWildcard((TcpIp_SockAddrType*)&inet));
}

void main_add_generic_suite(CU_pSuite suite)
{
    CU_add_test(suite, "wildcard_v4"             , suite_test_wildcard_v4);
    CU_add_test(suite, "wildcard_v6"             , suite_test_wildcard_v6);
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
