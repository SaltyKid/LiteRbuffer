/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_ring_buffer.c
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

/*============================= INCLUDE FILES ================================*/
#include "lite_ring_buffer_types.h"
#include "lite_ring_buffer.h"
#include <string.h>

/*============================ GLOBAL VARIABLES ==============================*/

/*========================== FUNCTION PROTOTYPES =============================*/

/*******************************************************************************
 * @brief        Initialize the lite chapter buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    data_buf_addr: A buffer to store data
 *
 * @param[in]    data_buf_size: The size of the data that can be stored
 *
 * @param[in]    chapter_buf_addr: A buffer to store chapter info
 *
 * @param[in]    chapter_num: The maximum number of the chapter that can be stored
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbc_init(lbf_chapter_t *lbc,
                 uint8_t *data_buf_addr,
                 uint32_t data_buf_size,
                 uint32_t *chapter_buf_addr,
                 uint32_t chapter_num)
{
    if (lbn_init(&(lbc->base_handle), data_buf_addr, data_buf_size))
        return LBF_E_NOT_OK;

    if (LBF_NULL == chapter_buf_addr || chapter_num < 2 || chapter_num == 0xFFFFFFFF)
        return LBF_E_NOT_OK;

    lbc->chapter_buf = chapter_buf_addr;
    lbc->chapter_max_num = chapter_num;
    lbc->chapter_rid = 0;
    lbc->chapter_wid = 0;
    lbc->chapter_full = 0;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Write data to the lite chapter buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    in_data: Data to be written
 *
 * @param[in]    length: Length of data to be written
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbc_write_data(lbf_chapter_t *lbc, void *in_data, uint32_t length)
{
    if (lbc_chapter_is_full(lbc))
        return LBF_E_NOT_OK;
    if (lbn_write_data(&(lbc->base_handle), in_data, length))
        return LBF_E_NOT_OK;

    lbc->chapter_buf[lbc->chapter_wid] = length;
    lbc->chapter_wid = (lbc->chapter_wid + 1) % lbc->chapter_max_num;
    lbc->chapter_full = lbc->chapter_wid == lbc->chapter_rid;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Read data from the lite chapter buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[out]   out_data: Store data to be read
 *
 * @param[out]   out_length: The length of data read
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbc_read_data(lbf_chapter_t *lbc, void *out_data, uint32_t *out_length)
{
    uint32_t data_len = 0;

    if (lbc_chapter_is_empty(lbc))
        return LBF_E_NOT_OK;

    data_len = lbc->chapter_buf[lbc->chapter_rid];
    if (out_length != LBF_NULL)
        *out_length = data_len;
    lbc->chapter_rid = (lbc->chapter_rid + 1) % lbc->chapter_max_num;
    lbc->chapter_full = 0;

    return lbn_read_data(&(lbc->base_handle), out_data, data_len);
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is full
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       True or False
 ******************************************************************************/
uint8_t lbc_chapter_is_full(lbf_chapter_t *lbc)
{
    return lbc->chapter_full;
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is empty
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       True or False
 ******************************************************************************/
uint8_t lbc_chapter_is_empty(lbf_chapter_t *lbc)
{
    return ((!lbc->chapter_full) && (lbc->chapter_rid == lbc->chapter_wid));
}

/*******************************************************************************
 * @brief        Get the number of chapters stored in the buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       chapter number
 ******************************************************************************/
uint32_t lbc_get_chapter_number(lbf_chapter_t *lbc)
{
    if (lbc->chapter_full)
        return lbc->chapter_max_num;

    if (lbc->chapter_rid <= lbc->chapter_wid)
        return (lbc->chapter_wid - lbc->chapter_rid);
    else
        return (lbc->chapter_max_num - lbc->chapter_rid + lbc->chapter_wid);
}

/*******************************************************************************
 * @brief        Get the remaining space of the chapter buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       chapter buffer free size
 ******************************************************************************/
uint32_t lbc_get_data_free_size(lbf_chapter_t *lbc)
{
    return lbn_get_free_size(&(lbc->base_handle));
}

/*******************************************************************************
 * @brief        Initialize a lite ringbuffer
 *
 * @param[in]    lbf: handle of ringbuffer lbf
 *
 * @param[in]    buf_addr: A buffer to store data
 *
 * @param[in]    buf_size: The size of the data that can be stored
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbn_init(lbf_node_t *lbf, uint8_t *buf_addr, uint32_t buf_size)
{
    if (LBF_NULL == buf_addr || buf_size < 2 || buf_size == 0xFFFFFFFF)
        return LBF_E_NOT_OK;

    lbf->head = 0;
    lbf->tail = 0;
    lbf->used_len = 0;
    lbf->data_buf = buf_addr;
    lbf->max_len = buf_size;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Write data to the lite ringbuffer
 *
 * @param[in]    lbf: lbf handle
 *
 * @param[in]    in_data: Data to be written
 *
 * @param[in]    length: Length of data to be written
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbn_write_data(lbf_node_t *lbf, void *in_data, uint32_t length)
{
    if (length > (lbf->max_len - lbf->used_len))
        return LBF_E_NOT_OK;
    else
    {
        uint8_t *p_data = (uint8_t *)in_data;
        if (length > (lbf->max_len - lbf->tail))
        {
            uint32_t write_size_a = 0, write_size_b = 0;
            write_size_a = lbf->max_len - lbf->tail;
            write_size_b = length - write_size_a;
            memcpy(&lbf->data_buf[lbf->tail], &p_data[0], write_size_a);
            memcpy(&lbf->data_buf[0], &p_data[write_size_a], write_size_b);
            lbf->used_len += length;
            lbf->tail = write_size_b;
        }
        else
        {
            memcpy(&lbf->data_buf[lbf->tail], &p_data[0], length);
            lbf->used_len += length;
            lbf->tail += length;
            if (lbf->tail == lbf->max_len)
                lbf->tail = 0;
        }

        return LBF_E_OK;
    }
}

/*******************************************************************************
 * @brief        Read data from the lite ringbuffer
 *
 * @param[in]    lbf: lbf handle
 *
 * @param[out]   out_data: Store data to be read
 *
 * @param[out]   out_length: The length of data read
 *
 * @return       LBF_E_OK - 1
 *               LBF_E_NOT_OK - 0
 ******************************************************************************/
uint8_t lbn_read_data(lbf_node_t *lbf, void *out_data, uint32_t length)
{
    if (length > lbf->used_len)
        return LBF_E_NOT_OK;
    else
    {
        uint8_t *p_data = (uint8_t *)out_data;
        if (length > (lbf->max_len - lbf->head))
        {
            uint32_t write_size_a = 0, write_size_b = 0;
            write_size_a = lbf->max_len - lbf->head;
            write_size_b = length - write_size_a;
            memcpy(&p_data[0], &lbf->data_buf[lbf->head], write_size_a);
            memcpy(&p_data[write_size_a], &lbf->data_buf[0], write_size_b);
            lbf->used_len -= length;
            lbf->head = write_size_b;
        }
        else
        {
            memcpy(&p_data[0], &lbf->data_buf[lbf->head], length);
            lbf->used_len -= length;
            lbf->head += length;
            if (lbf->head == lbf->max_len)
                lbf->head = 0;
        }

        return LBF_E_OK;
    }
}

/*******************************************************************************
 * @brief        Get the space used by ringbuffer
 *
 * @param[in]    lbf: lbf handle
 *
 * @return       ringbuffer used size
 ******************************************************************************/
uint32_t lbn_get_used_size(lbf_node_t *lbf)
{
    return lbf->used_len;
}

/*******************************************************************************
 * @brief        Get the remaining space of the lite ringbuffer
 *
 * @param[in]    lbf: lbf handle
 *
 * @return       ringbuffer free size
 ******************************************************************************/
uint32_t lbn_get_free_size(lbf_node_t *lbf)
{
    return (lbf->max_len - lbf->used_len);
}
