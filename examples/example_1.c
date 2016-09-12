/*******************************************************************************
 * BAREFOOT NETWORKS CONFIDENTIAL & PROPRIETARY
 *
 * Copyright (c) 2015-2016 Barefoot Networks, Inc.
 *
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of
 * Barefoot Networks, Inc. and its suppliers, if any. The intellectual and
 * technical concepts contained herein are proprietary to Barefoot Networks,
 * Inc.
 * and its suppliers and may be covered by U.S. and Foreign Patents, patents in
 * process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material is
 * strictly forbidden unless prior written permission is obtained from
 * Barefoot Networks, Inc.
 *
 * No warranty, explicit or implicit is provided, unless granted under a
 * written agreement with Barefoot Networks, Inc.
 *
 ******************************************************************************/

/*
 * Antonin Bas (antonin@barefootnetworks.com)
 *
 */

#ifndef TESTDATADIR
#define TESTDATADIR "testdata"
#endif

#include "PI/pi.h"
#include "PI/frontends/generic/pi.h"

#include <assert.h>

static pi_p4info_t *p4info = NULL;

static pi_p4_id_t t_ipv4_lpm = 0;
static pi_p4_id_t a_set_nhop = 0;
static pi_p4_id_t f_ipv4_dstAddr = 0;
static pi_p4_id_t ap_nhop_ipv4 = 0;
static pi_p4_id_t ap_port = 0;

static pi_match_key_t *mkey_ipv4_lpm = NULL;
static pi_action_data_t *adata_set_nhop = NULL;

static pi_dev_tgt_t dev_tgt = {0, 0xffff};
static pi_session_handle_t sess;

static int add_route(uint32_t prefix, int pLen, uint32_t nhop, uint16_t port,
                     pi_entry_handle_t *handle) {
  pi_status_t rc = 0;

  // match key
  rc |= pi_match_key_init(mkey_ipv4_lpm);
  pi_netv_t prefix_netv;
  rc |= pi_getnetv_u32(p4info, f_ipv4_dstAddr, prefix, &prefix_netv);
  rc |= pi_match_key_lpm_set(mkey_ipv4_lpm, &prefix_netv, pLen);

  // action data
  rc |= pi_action_data_init(adata_set_nhop);
  pi_netv_t nhop_ipv4_netv, port_netv;
  rc |= pi_getnetv_u32(p4info, ap_nhop_ipv4, nhop, &nhop_ipv4_netv);
  rc |= pi_getnetv_u16(p4info, ap_port, port, &port_netv);
  rc |= pi_action_data_arg_set(adata_set_nhop, &nhop_ipv4_netv);
  rc |= pi_action_data_arg_set(adata_set_nhop, &port_netv);

  pi_table_entry_t t_entry;
  t_entry.entry_type = PI_ACTION_ENTRY_TYPE_DATA;
  t_entry.entry.action_data = adata_set_nhop;
  t_entry.entry_properties = NULL;
  t_entry.direct_res_config = NULL;

  rc |= pi_table_entry_add(sess, dev_tgt, t_ipv4_lpm, mkey_ipv4_lpm, &t_entry,
                           0, handle);

  return rc;
}

static void init_ids() {
  t_ipv4_lpm = pi_p4info_table_id_from_name(p4info, "ipv4_lpm");
  a_set_nhop = pi_p4info_action_id_from_name(p4info, "set_nhop");
  f_ipv4_dstAddr = pi_p4info_field_id_from_name(p4info, "ipv4.dstAddr");
  ap_nhop_ipv4 =
      pi_p4info_action_param_id_from_name(p4info, a_set_nhop, "nhop_ipv4");
  ap_port = pi_p4info_action_param_id_from_name(p4info, a_set_nhop, "port");
}

int main() {
  pi_init(256, NULL);  // 256 devices max
  pi_add_config_from_file(TESTDATADIR
                          "/"
                          "simple_router.json",
                          PI_CONFIG_TYPE_BMV2_JSON, &p4info);

  pi_session_init(&sess);

  init_ids();

  pi_match_key_allocate(p4info, t_ipv4_lpm, &mkey_ipv4_lpm);
  pi_action_data_allocate(p4info, a_set_nhop, &adata_set_nhop);

  pi_entry_handle_t handle;
  // Adding entry 10.0.0.1/8 => nhop=10.0.0.1, port=11
  uint32_t ipv4_dstAddr = 0x0a000001;
  uint16_t port = 11;
  assert(!add_route(ipv4_dstAddr, 8, ipv4_dstAddr, port, &handle));

  pi_match_key_destroy(mkey_ipv4_lpm);
  pi_action_data_destroy(adata_set_nhop);
  pi_destroy_config(p4info);
  pi_session_cleanup(sess);
}
