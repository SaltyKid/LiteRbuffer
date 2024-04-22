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
 *   2024-04-22  |  v0.2.0     |  SaltyKid   |  Create file
 * -----------------------------------------------------------------------------
 ******************************************************************************/

/*============================= INCLUDE FILES ================================*/
#include "lite_ring_buffer_types.h"
#include "lite_ring_buffer.h"
#include <string.h>

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
 * @param[in]    chapter_num: The maximum number of the chapter that can be
 *                            stored
 *
 * @return       0 - LBF_E_OK
 *               other - LBF_ERROR_CODE
 ******************************************************************************/
uint8_t lbc_init(lbc_t *lbc,
                 uint8_t *data_buf_addr,
                 uint32_t data_buf_size,
                 uint32_t *chapter_buf_addr,
                 uint32_t chapter_num)
{
    uint8_t ret = LBF_E_OK;

    do
    {
        if (LBF_NULL == lbc)
        {
            ret = LBF_E_LBC_NO_HANDLE;
            break;
        }

        if (LBF_NULL == chapter_buf_addr)
        {
            ret = LBF_E_CBUF_NUL;
            break;
        }

        if (2 > chapter_num)
        {
            ret = LBF_E_CBUF_SIZE_EXMINI;
            break;
        }

        if (LBF_MAX_SIZE <= chapter_num)
        {
            ret = LBF_E_CBUF_SIZE_EXMAXI;
            break;
        }

        ret = lbn_init(&(lbc->base_handle), data_buf_addr, data_buf_size);
        if (LBF_E_OK != ret)
        {
            break;
        }
        lbc->chapter_buf = chapter_buf_addr;
        lbc->chapter_max_num = chapter_num;
        lbc->chapter_rid = 0;
        lbc->chapter_wid = 0;
        lbc->chapter_full = 0;
    } while (0);

    return ret;
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
 * @return       0  - LBF_E_OK
 *               10 - LBF_E_DBUF_NOSPACE
 *               11 - LBF_E_CBUF_NOSPACE
 ******************************************************************************/
uint8_t lbc_write_data(lbc_t *lbc, void *in_data, uint32_t length)
{
    uint8_t ret = LBF_E_OK;

    if (!lbc_chapter_is_full(lbc))
    {
        ret = lbn_write_data(&(lbc->base_handle), in_data, length);
        if (LBF_E_OK == ret)
        {
            lbc->chapter_buf[lbc->chapter_wid] = length;
            lbc->chapter_wid = (lbc->chapter_wid + 1) % lbc->chapter_max_num;
            lbc->chapter_full = lbc->chapter_wid == lbc->chapter_rid;
        }
    }
    else
    {
        ret = LBF_E_CBUF_NOSPACE;
    }

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
 * @return       0  - LBF_E_OK
 *               12 - LBF_E_DBUF_NOENOUGH_DATA
 *               13 - LBF_E_CBUF_NOENOUGH_DATA
 ******************************************************************************/
uint8_t lbc_read_data(lbc_t *lbc, void *out_data, uint32_t *out_length)
{
    uint8_t ret = LBF_E_OK;
    uint32_t data_len = 0;

    if (!lbc_chapter_is_empty(lbc))
    {
        data_len = lbc->chapter_buf[lbc->chapter_rid];
        if (out_length != LBF_NULL)
            *out_length = data_len;
        ret = lbn_read_data(&(lbc->base_handle), out_data, data_len);
        if (LBF_E_OK == ret)
        {
            lbc->chapter_rid = (lbc->chapter_rid + 1) % lbc->chapter_max_num;
            lbc->chapter_full = 0;
        }
    }
    else
    {
        ret = LBF_E_CBUF_NOENOUGH_DATA;
    }

    return ret;
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is full
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       True or False
 ******************************************************************************/
bool lbc_chapter_is_full(lbc_t *lbc)
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
bool lbc_chapter_is_empty(lbc_t *lbc)
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
uint32_t lbc_get_chapter_number(lbc_t *lbc)
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
uint32_t lbc_get_data_free_size(lbc_t *lbc)
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
 * @return       0 - LBF_E_OK
 *               other - LBF_ERROR_CODE
 ******************************************************************************/
uint8_t lbn_init(lbn_t *lbf, uint8_t *buf_addr, uint32_t buf_size)
{
    uint8_t ret = LBF_E_OK;

    do
    {
        if (LBF_NULL == lbf)
        {
            ret = LBF_E_LBN_NO_HANDLE;
            break;
        }

        if (LBF_NULL == buf_addr)
        {
            ret = LBF_E_DBUF_NUL;
            break;
        }

        if (2 > buf_size)
        {
            ret = LBF_E_DBUF_SIZE_EXMINI;
            break;
        }

        if (LBF_MAX_SIZE <= buf_size)
        {
            ret = LBF_E_DBUF_SIZE_EXMAXI;
            break;
        }

        lbf->head = 0;
        lbf->tail = 0;
        lbf->used_len = 0;
        lbf->data_buf = buf_addr;
        lbf->max_len = buf_size;
    } while (0);

    return ret;
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
 * @return       0  - LBF_E_OK
 *               10 - LBF_E_DBUF_NOSPACE
 ******************************************************************************/
uint8_t lbn_write_data(lbn_t *lbf, void *in_data, uint32_t length)
{
    if (length > (lbf->max_len - lbf->used_len))
        return LBF_E_DBUF_NOSPACE;
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
            lbf->tail = write_size_b;
        }
        else
        {
            memcpy(&lbf->data_buf[lbf->tail], &p_data[0], length);
            lbf->tail += length;
            if (lbf->tail == lbf->max_len)
                lbf->tail = 0;
        }
        lbf->used_len += length;

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
 * @return       0  - LBF_E_OK
 *               12 - LBF_E_DBUF_NOENOUGH_DATA
 ******************************************************************************/
uint8_t lbn_read_data(lbn_t *lbf, void *out_data, uint32_t length)
{
    if (length > lbf->used_len)
        return LBF_E_DBUF_NOENOUGH_DATA;
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
            lbf->head = write_size_b;
        }
        else
        {
            memcpy(&p_data[0], &lbf->data_buf[lbf->head], length);
            lbf->head += length;
            if (lbf->head == lbf->max_len)
                lbf->head = 0;
        }
        lbf->used_len -= length;

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
uint32_t lbn_get_used_size(lbn_t *lbf)
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
uint32_t lbn_get_free_size(lbn_t *lbf)
{
    return (lbf->max_len - lbf->used_len);
}
