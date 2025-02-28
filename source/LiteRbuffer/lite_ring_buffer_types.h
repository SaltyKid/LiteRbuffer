/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_ring_buffer_types.h
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
 *   2024-04-22  |  v0.2.0     |  SaltyKid   |  Add error codes and adjust the
 *                                              order of assignments occupying
 *                                              buffer space
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef LITE_RING_BUFFER_TYPES_H
#define LITE_RING_BUFFER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
/* PRQA S ALL EOF */ /* lite ring buffer */
/*============================= INCLUDE FILES ================================*/
#include <stdint.h>
#include <stdbool.h>

/*========================= PERIPHERAL DECLARATION ===========================*/
#define LITE_RING_BUFFER_VERSION ("0.5.0")

/*============================ TYPE DEFINITIONS ==============================*/
#define LBF_NULL     ((void *)0)
#define LBF_MAX_SIZE (0xFFFFFFFFu)
#define LBF_MIN_SIZE (0x02u)

#define LBF_E_OK     (0u)
#define LBF_E_NOT_OK (1u)

#define LBF_E_LBN_NO_HANDLE      (2u)
#define LBF_E_DBUF_NUL           (3u)
#define LBF_E_DBUF_SIZE_EXMINI   (4u)
#define LBF_E_DBUF_SIZE_EXMAXI   (5u)
#define LBF_E_DBUF_NOSPACE       (6u)
#define LBF_E_DBUF_NOENOUGH_DATA (7u)

#define LBF_E_LBC_NO_HANDLE        (18u)
#define LBF_E_CBUF_NUL             (19u)
#define LBF_E_CBUF_SIZE_EXMINI     (20u)
#define LBF_E_CBUF_SIZE_EXMAXI     (21u)
#define LBF_E_CBUF_NOSPACE         (22u)
#define LBF_E_CBUF_NOENOUGH_DATA   (23u)
#define LBF_E_CBUF_ERROR_THRESHOLD (24u)

#define LBF_E_LBQ_NO_HANDLE           (34u)
#define LBF_E_QBUF_NUL                (35u)
#define LBF_E_QBUF_SIZE_EXMINI        (36u)
#define LBF_E_QBUF_SIZE_EXMAXI        (37u)
#define LBF_E_QBUF_ELEMENT_ERROR_SIZE (38u)
#define LBF_E_QBUF_ELEMENT_NUM_EXMINI (39u)
#define LBF_E_QBUF_NOSPACE            (40u)
#define LBF_E_QBUF_NOENOUGH_DATA      (41u)

/*=========================== STRUCTURE DEFINES ==============================*/

typedef struct LBF_NODE_CONTROL_STRU
{
    uint32_t ridx;
    uint32_t widx;
    uint32_t used_len;
    uint32_t max_len;
    uint8_t *data_buf;
} lbncb_t;

typedef struct LBF_CHAPTER_CONTROL_STRU
{
    bool full;
    lbncb_t base_handle;
    uint32_t ridx;
    uint32_t widx;
    uint32_t chapter_maxnum;
    uint32_t *chapter_buf;
    uint32_t threshold_length;
} lbccb_t;

typedef struct LBF_QUEUE_CONTROL_STRU
{
    bool full;
    uint32_t ridx;
    uint32_t widx;
    uint32_t element_size;
    uint32_t element_maxnum;
    uint32_t buf_maxsize;
    void *buf;
} lbqcb_t;

typedef struct LBF_MULTINODE_CONTROL_STRU
{
    uint32_t widx;
    uint32_t used_len;
    uint32_t max_len;
    uint32_t *ridx;
    uint32_t multi_maxnum;
    uint8_t *data_buf;
} mbncb_t;

typedef struct LBF_MULTICHAPTER_CONTROL_STRU
{
    bool full;
    mbncb_t base_handle;
    uint32_t widx;
    uint32_t *ridx;
    uint32_t multi_maxnum;
    uint32_t chapter_maxnum;
    uint32_t *chapter_buf;
    uint32_t threshold_length;
} mbccb_t;

#ifdef __cplusplus
}
#endif

#endif
