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

/*============================= INCLUDE FILES ================================*/
#include <stdint.h>
#include <stdbool.h>

/*========================= PERIPHERAL DECLARATION ===========================*/
#define LITE_RING_BUFFER_VERSION ("0.2.0")

/*============================ TYPE DEFINITIONS ==============================*/
#define LBF_NULL     ((void *)0)
#define LBF_MAX_SIZE 0xFFFFFFFF

#define LBF_E_OK                 0
#define LBF_E_NOT_OK             1
#define LBF_E_LBC_NO_HANDLE      2
#define LBF_E_LBN_NO_HANDLE      3
#define LBF_E_DBUF_NUL           4
#define LBF_E_DBUF_SIZE_EXMINI   5
#define LBF_E_DBUF_SIZE_EXMAXI   6
#define LBF_E_CBUF_NUL           7
#define LBF_E_CBUF_SIZE_EXMINI   8
#define LBF_E_CBUF_SIZE_EXMAXI   9
#define LBF_E_DBUF_NOSPACE       10
#define LBF_E_CBUF_NOSPACE       11
#define LBF_E_DBUF_NOENOUGH_DATA 12
#define LBF_E_CBUF_NOENOUGH_DATA 13

/*=========================== STRUCTURE DEFINES ==============================*/

typedef struct LBF_NODE_STRU
{
    uint32_t head;
    uint32_t tail;
    uint8_t *data_buf;
    uint32_t used_len;
    uint32_t max_len;
} LBF_NODE_ST, lbn_t;

typedef struct LBF_CHAPTER_STRU
{
    lbn_t base_handle;
    bool chapter_full;
    uint32_t chapter_rid;
    uint32_t chapter_wid;
    uint32_t *chapter_buf;
    uint32_t chapter_max_num;
} LBF_CHAPTER_ST, lbc_t;

#ifdef __cplusplus
}
#endif

#endif
