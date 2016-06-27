/* Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PI/pi.h"

#include <stdio.h>

pi_status_t _pi_table_entry_add(pi_session_handle_t session_handle,
                                pi_dev_tgt_t dev_tgt,
                                pi_p4_id_t table_id,
                                const pi_match_key_t *match_key,
                                const pi_table_entry_t *table_entry,
                                int overwrite,
                                pi_entry_handle_t *entry_handle) {
  (void) session_handle; (void) dev_tgt; (void) table_id; (void) match_key;
  (void) table_entry; (void) overwrite; (void) entry_handle;
  printf("_pi_table_entry_add\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_default_action_set(pi_session_handle_t session_handle,
                                         pi_dev_tgt_t dev_tgt,
                                         pi_p4_id_t table_id,
                                         const pi_table_entry_t *table_entry) {
  (void) session_handle; (void) dev_tgt; (void) table_id; (void) table_entry;
  printf("_pi_table_default_action_set\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_default_action_get(pi_session_handle_t session_handle,
                                         pi_dev_id_t dev_id,
                                         pi_p4_id_t table_id,
                                         pi_table_entry_t *table_entry) {
  (void) session_handle; (void) dev_id; (void) table_id; (void) table_entry;
  printf("_pi_table_default_action_get\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_default_action_done(pi_session_handle_t session_handle,
                                          pi_table_entry_t *table_entry) {
  (void) session_handle; (void) table_entry;
  printf("_pi_table_default_action_done\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_entry_delete(pi_session_handle_t session_handle,
                                   pi_dev_id_t dev_id,
                                   pi_p4_id_t table_id,
                                   pi_entry_handle_t entry_handle) {
  (void) session_handle; (void) dev_id; (void) table_id; (void) entry_handle;
  printf("_pi_table_entry_delete\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_entry_modify(pi_session_handle_t session_handle,
                                   pi_dev_id_t dev_id,
                                   pi_p4_id_t table_id,
                                   pi_entry_handle_t entry_handle,
                                   const pi_table_entry_t *table_entry) {
  (void) session_handle; (void) dev_id; (void) table_id; (void) entry_handle;
  (void) table_entry;
  printf("_pi_table_entry_modify\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_entries_fetch(pi_session_handle_t session_handle,
                                    pi_dev_id_t dev_id,
                                    pi_p4_id_t table_id,
                                    pi_table_fetch_res_t *res) {
  (void) session_handle; (void) dev_id; (void) table_id; (void) res;
  printf("_pi_table_fetch\n");
  return PI_STATUS_SUCCESS;
}

pi_status_t _pi_table_entries_fetch_done(pi_session_handle_t session_handle,
                                         pi_table_fetch_res_t *res) {
  (void) session_handle; (void) res;
  printf("_pi_table_fetch_done\n");
  return PI_STATUS_SUCCESS;
}
