/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_ring_buffer.h
 * @author  SaltyKid
 * @version 0.1.0
 * @date    2023-11-16
 * @brief   Omit
 *          This file contains:
 *              - Omit
 *
 * -----------------------------------------------------------------------------
 * Change History:
 *   <Date>      |  <Version>  |  <Author>   |  <Description>
 *   2023-11-16  |  v0.1.0     |  SaltyKid   |  Create file
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef __LITE_RING_BUFFER_H__
#define __LITE_RING_BUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ================================*/
#include "lite_ring_buffer_types.h"

/*========================== FUNCTION PROTOTYPES =============================*/

extern uint8_t lbn_init(lbf_node_t *lbf, uint8_t *buf_addr, uint32_t buf_size);
extern uint8_t lbn_write_data(lbf_node_t *lbf, void *in_data, uint32_t length);
extern uint8_t lbn_read_data(lbf_node_t *lbf, void *out_data, uint32_t length);
extern uint32_t lbn_get_used_size(lbf_node_t *lbf);
extern uint32_t lbn_get_free_size(lbf_node_t *lbf);

extern uint8_t lbc_init(lbf_chapter_t *lbc,
                        uint8_t *data_buf_addr,
                        uint32_t data_buf_size,
                        uint32_t *chapter_buf_addr,
                        uint32_t chapter_num);
extern uint8_t lbc_write_data(lbf_chapter_t *lbc, void *in_data, uint32_t length);
extern uint8_t lbc_read_data(lbf_chapter_t *lbc, void *out_data, uint32_t *out_length);
extern uint8_t lbc_chapter_is_full(lbf_chapter_t *lbc);
extern uint8_t lbc_chapter_is_empty(lbf_chapter_t *lbc);
extern uint32_t lbc_get_chapter_number(lbf_chapter_t *lbc);
extern uint32_t lbc_get_data_free_size(lbf_chapter_t *lbc);

#ifdef __cplusplus
}
#endif

#endif
