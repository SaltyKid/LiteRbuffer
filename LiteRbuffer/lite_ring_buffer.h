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
 *   2024-04-22  |  v0.2.0     |  SaltyKid   |  Add expansion macro
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef LITE_RING_BUFFER_H
#define LITE_RING_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ================================*/
#include "lite_ring_buffer_types.h"

/*============================= EXPORTED MACRO ==============================*/
#define DECLARE_LBC_BUFFER(lbc_name, data_size, chapter_size)                  \
    static uint8_t lbc_name##_buffer_data[data_size];                          \
    static uint32_t lbc_name##_buffer_chapter[chapter_size];                   \
    lbc_t lbc_name;
#define LBC_BUFFER_INIT(lbc_name, data_size, chapter_size)                     \
    lbc_init(&lbc_name,                                                        \
             lbc_name##_buffer_data,                                           \
             data_size,                                                        \
             lbc_name##_buffer_chapter,                                        \
             chapter_size);

#define DECLARE_LBN_BUFFER(lbn_name, data_size)                                \
    static uint8_t lbc_name##_buffer_data[data_size];                          \
    lbn_t lbc_name;
#define LBN_BUFFER_INIT(lbn_name, data_size)                                   \
    lbn_init(&lbn_name, lbn_name##_buffer_data, data_size);

/*========================== FUNCTION PROTOTYPES =============================*/

extern uint8_t lbn_init(lbn_t *lbf, uint8_t *buf_addr, uint32_t buf_size);
extern uint8_t lbn_write_data(lbn_t *lbf, void *in_data, uint32_t length);
extern uint8_t lbn_read_data(lbn_t *lbf, void *out_data, uint32_t length);
extern uint32_t lbn_get_used_size(lbn_t *lbf);
extern uint32_t lbn_get_free_size(lbn_t *lbf);

extern uint8_t lbc_init(lbc_t *lbc,
                        uint8_t *data_buf_addr,
                        uint32_t data_buf_size,
                        uint32_t *chapter_buf_addr,
                        uint32_t chapter_num);
extern uint8_t lbc_write_data(lbc_t *lbc, void *in_data, uint32_t length);
extern uint8_t lbc_read_data(lbc_t *lbc, void *out_data, uint32_t *out_length);
extern bool lbc_chapter_is_full(lbc_t *lbc);
extern bool lbc_chapter_is_empty(lbc_t *lbc);
extern uint32_t lbc_get_chapter_number(lbc_t *lbc);
extern uint32_t lbc_get_data_free_size(lbc_t *lbc);

#ifdef __cplusplus
}
#endif

#endif
