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

struct suite_socket_state {
    boolean retrieve;
    boolean bound;
    boolean listen;
    boolean connect;
};


struct suite_state {
    TcpIp_SocketIdType socket_id;
    uint16             port_index;

    struct suite_socket_state sockets[100];
};

struct suite_state suite_state;

#define SOCKET_GRP1      0
#define SOCKET_GRP2      1

#define SOCKET_GRP1_CON1 0
#define SOCKET_GRP1_CON2 1
#define SOCKET_GRP2_CON1 2
#define SOCKET_GRP2_CON2 3


const TcpIp_SockAddrInetType socket_remote_any_v4 = {
    .domain  = TCPIP_AF_INET,
    .addr[0] = TCPIP_IPADDR_ANY,
    .port    = TCPIP_PORT_ANY,
};

const SoAd_SoGrpConfigType           socket_group_1 = {
    .localport = 8000,
    .protocol  = TCPIP_IPPROTO_TCP,
    .automatic = TRUE,
    .initiate  = FALSE,
};

const SoAd_SoGrpConfigType           socket_group_2 = {
    .localport = 8001,
    .protocol  = TCPIP_IPPROTO_UDP,
    .automatic = TRUE,
    .initiate  = FALSE,
};

const SoAd_SocketRouteType           socket_route_1 = {
        .header_id = 0u,
        .destination = {
                .upper_type = SOAD_UPPER_LAYER_TP,
                .pdu        = 0u
        }
};

const SoAd_SocketRouteType           socket_route_2 = {
        .header_id = 0u,
        .destination = {
                .upper_type = SOAD_UPPER_LAYER_IF,
                .pdu        = 1u
        }
};

const SoAd_SoConConfigType           socket_group_1_conn_1 = {
    .group  = SOCKET_GRP1,
    .remote = (const TcpIp_SockAddrType*)&socket_remote_any_v4,
    .socket_route  = &socket_route_1,
};

const SoAd_SoConConfigType           socket_group_1_conn_2 = {
    .group  = SOCKET_GRP1,
    .remote = (const TcpIp_SockAddrType*)&socket_remote_any_v4,
    .socket_route  = &socket_route_1,
};

const SoAd_SoConConfigType           socket_group_2_conn_1 = {
    .group  = SOCKET_GRP2,
    .remote = (const TcpIp_SockAddrType*)&socket_remote_any_v4,
    .socket_route  = &socket_route_2,
};

const SoAd_SoConConfigType           socket_group_2_conn_2 = {
    .group  = SOCKET_GRP2,
    .remote = (const TcpIp_SockAddrType*)&socket_remote_any_v4,
    .socket_route  = &socket_route_2,
};

const SoAd_PduRouteType              pdu_route_1;

const SoAd_ConfigType config = {
    .groups = {
        [SOCKET_GRP1] = &socket_group_1,
        [SOCKET_GRP2] = &socket_group_2,
    },

    .connections = {
        [SOCKET_GRP1_CON1] = &socket_group_1_conn_1,
        [SOCKET_GRP1_CON2] = &socket_group_1_conn_2,
        [SOCKET_GRP2_CON1] = &socket_group_2_conn_1,
        [SOCKET_GRP2_CON2] = &socket_group_2_conn_2,
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
    CU_ASSERT_EQUAL(ModuleId  , SOAD_MODULEID);
    CU_ASSERT_EQUAL(InstanceId, 0u);
    CU_ASSERT_TRUE(FALSE);
    return E_OK;
}

Std_ReturnType TcpIp_SoAdGetSocket(
        TcpIp_DomainType            domain,
        TcpIp_ProtocolType          protocol,
        TcpIp_SocketIdType*         id
    )
{
    *id = ++suite_state.socket_id;
    suite_state.sockets[*id].retrieve = TRUE;
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

Std_ReturnType TcpIp_TcpReceived(
        TcpIp_SocketIdType id,
        uint32             len
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
    if (port == TCPIP_PORT_ANY) {
        *port = ++suite_state.port_index;
    }
    suite_state.sockets[id].bound = TRUE;
    return E_OK;
}

Std_ReturnType TcpIp_TcpListen(
        TcpIp_SocketIdType id,
        uint16 channels
    )
{
    suite_state.sockets[id].listen = TRUE;
    return E_OK;
}

Std_ReturnType TcpIp_TcpConnect(
        TcpIp_SocketIdType          id,
        const TcpIp_SockAddrType*   remote
    )
{
    suite_state.sockets[id].connect = TRUE;
    return E_OK;
}


Std_ReturnType TcpIp_Close(
        TcpIp_SocketIdType          id,
        boolean                     abort
    )
{
    suite_state.sockets[id].connect  = FALSE;
    suite_state.sockets[id].bound    = FALSE;
    suite_state.sockets[id].listen   = FALSE;
    suite_state.sockets[id].retrieve = FALSE;
    return E_OK;
}

void PduR_SoAdIfRxIndication(
            PduIdType           pdu,
            const PduInfoType*  info
    )
{

}

int suite_init(void)
{
    suite_state.socket_id  = 1u;
    suite_state.port_index = 1024u;
    memset(suite_state.sockets, 0, sizeof(suite_state.sockets));

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

void main_test_mainfunction_open()
{
    struct suite_socket_state* socket_state;

    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP1_CON1].state, SOAD_SOCON_OFFLINE);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP1_CON2].state, SOAD_SOCON_OFFLINE);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP2_CON1].state, SOAD_SOCON_OFFLINE);
    SoAd_MainFunction();

    /* TCP listen socket should be bound and listening */
    CU_ASSERT_NOT_EQUAL_FATAL(SoAd_SoGrpStatus[SOCKET_GRP1].socket_id, TCPIP_SOCKETID_INVALID);
    socket_state = &suite_state.sockets[SoAd_SoGrpStatus[SOCKET_GRP1].socket_id];
    CU_ASSERT_EQUAL(socket_state->retrieve    , TRUE);
    CU_ASSERT_EQUAL(socket_state->bound       , TRUE);
    CU_ASSERT_EQUAL(socket_state->listen      , TRUE);
    CU_ASSERT_EQUAL(socket_state->connect     , FALSE);

    /* TCP extra sockets should be just waiting to connect */
    CU_ASSERT_EQUAL_FATAL(SoAd_SoConStatus[SOCKET_GRP1_CON1].socket_id, TCPIP_SOCKETID_INVALID);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP1_CON1].state, SOAD_SOCON_RECONNECT);

    CU_ASSERT_EQUAL_FATAL(SoAd_SoConStatus[SOCKET_GRP1_CON2].socket_id, TCPIP_SOCKETID_INVALID);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP1_CON2].state, SOAD_SOCON_RECONNECT);

    /* UDP group socket should be bound, but not listening or connected */
    CU_ASSERT_NOT_EQUAL_FATAL(SoAd_SoGrpStatus[SOCKET_GRP2].socket_id, TCPIP_SOCKETID_INVALID);
    socket_state = &suite_state.sockets[SoAd_SoGrpStatus[SOCKET_GRP2].socket_id];
    CU_ASSERT_EQUAL(socket_state->retrieve    , TRUE);
    CU_ASSERT_EQUAL(socket_state->bound       , TRUE);
    CU_ASSERT_EQUAL(socket_state->listen      , FALSE);
    CU_ASSERT_EQUAL(socket_state->connect     , FALSE);

    CU_ASSERT_EQUAL_FATAL(SoAd_SoConStatus[SOCKET_GRP2_CON1].socket_id, TCPIP_SOCKETID_INVALID);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[SOCKET_GRP2_CON1].state, SOAD_SOCON_RECONNECT);
}

void main_test_mainfunction_accept(SoAd_SoGrpIdType id_grp, SoAd_SoConIdType id_con)
{
    TcpIp_SockAddrInetType inet;
    inet.domain  = TCPIP_AF_INET;
    inet.addr[0] = 1;
    inet.port    = 1;

    CU_ASSERT_EQUAL(SoAd_TcpAccepted(SoAd_SoGrpStatus[id_grp].socket_id
                                   , ++suite_state.socket_id
                                   , (TcpIp_SockAddrType*)&inet)
                  , E_OK);
    CU_ASSERT_NOT_EQUAL_FATAL(SoAd_SoConStatus[id_con].socket_id
                           , TCPIP_SOCKETID_INVALID);

    struct suite_socket_state* socket_state;
    socket_state = &suite_state.sockets[SoAd_SoConStatus[id_con].socket_id];
    CU_ASSERT_EQUAL(socket_state->retrieve    , FALSE);
    CU_ASSERT_EQUAL(socket_state->bound       , FALSE);
    CU_ASSERT_EQUAL(socket_state->listen      , FALSE);
    CU_ASSERT_EQUAL(socket_state->connect     , FALSE);
    CU_ASSERT_EQUAL(SoAd_SoConStatus[id_con].state
                 , SOAD_SOCON_ONLINE);
}

void main_test_mainfunction_accept_1(void)
{
    main_test_mainfunction_accept(SOCKET_GRP1, SOCKET_GRP1_CON1);
}

void main_test_mainfunction_accept_2(void)
{
    main_test_mainfunction_accept(SOCKET_GRP1, SOCKET_GRP1_CON2);
}

void main_test_mainfunction_receive_udp_online(SoAd_SoGrpIdType id_grp, SoAd_SoConIdType id_con)
{
    TcpIp_SockAddrInetType inet;
    inet.domain  = TCPIP_AF_INET;
    inet.addr[0] = 1;
    inet.port    = id_con;

    CU_ASSERT_EQUAL_FATAL(SoAd_SoConStatus[id_con].state
                           , SOAD_SOCON_RECONNECT);


    SoAd_RxIndication(SoAd_SoGrpStatus[id_grp].socket_id
                    , (TcpIp_SockAddrType*)&inet
                    , NULL
                    , 0);

    CU_ASSERT_EQUAL_FATAL(SoAd_SoConStatus[id_con].state
                           , SOAD_SOCON_ONLINE);

}

void main_test_mainfunction_receive_udp_1()
{
    main_test_mainfunction_receive_udp_online(SOCKET_GRP2, SOCKET_GRP2_CON1);
}

void main_test_mainfunction_receive_udp_2()
{
    main_test_mainfunction_receive_udp_online(SOCKET_GRP2, SOCKET_GRP2_CON2);
}

void main_add_mainfunction_suite(CU_pSuite suite)
{
    CU_add_test(suite, "open"              , main_test_mainfunction_open);
    CU_add_test(suite, "accept_1"          , main_test_mainfunction_accept_1);
    CU_add_test(suite, "accept_2"          , main_test_mainfunction_accept_2);
    CU_add_test(suite, "receive_udp_1"     , main_test_mainfunction_receive_udp_1);
    CU_add_test(suite, "receive_udp_2"     , main_test_mainfunction_receive_udp_2);
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

    suite = CU_add_suite("Suite_MainFunction", suite_init, suite_clean);
    main_add_mainfunction_suite(suite);


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    /* Run results and output to files */
    CU_automated_run_tests();
    CU_list_tests_to_file();

    CU_cleanup_registry();
    return CU_get_error();
}
