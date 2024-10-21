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
/* PRQA S ALL EOF */ /* lite ring buffer */
/*============================= INCLUDE FILES ================================*/
#include "lite_ring_buffer_types.h"

/*============================= EXPORTED MACRO ==============================*/
#define DECLARE_LBC_BUFFER(lbc_name, data_size, chapter_size)                  \
    static uint8_t lbc_name##_buffer_data[data_size];                          \
    static uint32_t lbc_name##_buffer_chapter[chapter_size];                   \
    lbccb_t lbc_name;
#define LBC_BUFFER_INIT(lbc_name, data_size, chapter_size)                     \
    lbc_init(&lbc_name,                                                        \
             lbc_name##_buffer_data,                                           \
             data_size,                                                        \
             lbc_name##_buffer_chapter,                                        \
             chapter_size);

#define DECLARE_LBN_BUFFER(lbn_name, data_size)                                \
    static uint8_t lbc_name##_buffer_data[data_size];                          \
    lbncb_t lbc_name;
#define LBN_BUFFER_INIT(lbn_name, data_size)                                   \
    lbn_init(&lbn_name, lbn_name##_buffer_data, data_size);

/*========================== FUNCTION PROTOTYPES =============================*/

extern uint8_t lbn_init(lbncb_t *lbn, uint8_t *buf_addr, uint32_t buf_size);
extern uint8_t lbn_write_data(lbncb_t *lbn, void *in_data, uint32_t length);
extern uint8_t lbn_read_data(lbncb_t *lbn,
                             void *out_data,
                             uint32_t length,
                             uint32_t outbuf_size);
extern uint32_t lbn_get_used_size(lbncb_t *lbn);
extern uint32_t lbn_get_free_size(lbncb_t *lbn);

extern uint8_t lbc_init(lbccb_t *lbc,
                        uint8_t *data_buf_addr,
                        uint32_t data_buf_size,
                        uint32_t *chapter_buf_addr,
                        uint32_t chapter_num);
extern uint8_t lbc_set_threshold_data_length(lbccb_t *lbc, uint32_t length);
extern uint8_t lbc_write_data(lbccb_t *lbc, void *in_data, uint32_t length);
extern uint8_t lbc_read_data(lbccb_t *lbc,
                             void *out_data,
                             uint32_t *out_length,
                             uint32_t outbuf_size);
extern bool lbc_chapter_is_full(lbccb_t *lbc);
extern bool lbc_chapter_is_empty(lbccb_t *lbc);
extern uint32_t lbc_get_chapter_number(lbccb_t *lbc);
extern uint32_t lbc_get_data_free_size(lbccb_t *lbc);

extern uint8_t lbq_init(lbqcb_t *lbq,
                        void *data_buf,
                        uint32_t data_bufsize,
                        uint32_t element_size);
extern bool lbq_is_full(lbqcb_t *lbq);
extern bool lbq_is_empty(lbqcb_t *lbq);
extern uint8_t lbq_get_wbuf(lbqcb_t *lbq, void **element);
extern uint8_t lbq_get_rbuf(lbqcb_t *lbq, void **element);
extern uint8_t lbq_get_wbuf_noupdate(lbqcb_t *lbq, void **element);
extern uint8_t lbq_get_rbuf_noupdate(lbqcb_t *lbq, void **element);
extern uint8_t lbq_wbuf_update(lbqcb_t *lbq);
extern uint8_t lbq_rbuf_update(lbqcb_t *lbq);

extern uint8_t mbn_init(mbncb_t *mbn,
                        uint8_t *buf_addr,
                        uint32_t buf_size,
                        uint32_t *multi_rid_list,
                        uint32_t multi_rid_num);
extern uint8_t mbn_write_data(mbncb_t *mbn, void *in_data, uint32_t length);
extern uint8_t mbn_read_data(mbncb_t *mbn,
                             uint32_t multi_rid,
                             void *out_data,
                             uint32_t length,
                             uint32_t outbuf_size);
extern uint32_t mbn_get_used_size(mbncb_t *mbn);
extern uint32_t mbn_get_free_size(mbncb_t *mbn);

extern uint8_t mbc_init(mbccb_t *mbc,
                        uint8_t *data_buf_addr,
                        uint32_t data_buf_size,
                        uint32_t *chapter_buf_addr,
                        uint32_t chapter_num,
                        uint32_t *multi_datarid_list,
                        uint32_t *multi_chaprid_list,
                        uint32_t multi_rid_num);
extern uint8_t mbc_set_threshold_data_length(mbccb_t *mbc, uint32_t length);
extern uint8_t mbc_write_data(mbccb_t *mbc, void *in_data, uint32_t length);
extern uint8_t mbc_read_data(mbccb_t *mbc,
                             uint32_t multi_rid,
                             void *out_data,
                             uint32_t *out_length,
                             uint32_t outbuf_size);
extern bool mbc_chapter_is_full(mbccb_t *mbc);
extern bool mbc_chapter_is_empty(mbccb_t *mbc, uint32_t multi_rid);
extern uint32_t mbc_get_chapter_number(mbccb_t *mbc, uint32_t multi_rid);
extern uint32_t mbc_get_data_free_size(mbccb_t *mbc);

#ifdef __cplusplus
}
#endif

#endif
