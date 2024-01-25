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
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef __LITE_RING_BUFFER_TYPES_H__
#define __LITE_RING_BUFFER_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ================================*/
#include <stdint.h>

/*============================ TYPE DEFINITIONS ==============================*/
#define LBF_NULL ((void *)0)

#define LBF_E_OK     (0)
#define LBF_E_NOT_OK (1)

/*=========================== STRUCTURE DEFINES ==============================*/

typedef struct LBF_NODE_STRU
{
    uint32_t head;
    uint32_t tail;
    uint8_t *data_buf;
    uint32_t used_len;
    uint32_t max_len;
} LBF_NODE_ST, lbf_node_t;

typedef struct LBF_CHAPTER_STRU
{
    lbf_node_t base_handle;
    uint8_t chapter_full;
    uint32_t chapter_rid;
    uint32_t chapter_wid;
    uint32_t *chapter_buf;
    uint32_t chapter_max_num;
} LBF_CHAPTER_ST, lbf_chapter_t;

#ifdef __cplusplus
}
#endif

#endif
