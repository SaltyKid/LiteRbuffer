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
 * @brief        Initialize the lite queue buffer
 *
 * @param[in]    lbq: lbq handle
 *
 * @param[in]    data_buf: A buffer to store data
 *
 * @param[in]    data_bufsize: The size of the data that can be stored
 *
 * @param[in]    element_size: The size of the elements to be stored
 *
 * @return       0 - LBF_E_OK
 *               other - LBF_ERROR_CODE
 ******************************************************************************/
uint8_t lbq_init(lbqcb_t *lbq,
                 void *data_buf,
                 uint32_t data_bufsize,
                 uint32_t element_size)
{
    uint8_t ret = LBF_E_OK;

    do
    {
        if (LBF_NULL == lbq)
        {
            ret = LBF_E_LBQ_NO_HANDLE;
            break;
        }

        if (LBF_NULL == data_buf)
        {
            ret = LBF_E_QBUF_NUL;
            break;
        }

        if (LBF_MIN_SIZE > data_bufsize)
        {
            ret = LBF_E_QBUF_SIZE_EXMINI;
            break;
        }

        if (LBF_MAX_SIZE <= data_bufsize)
        {
            ret = LBF_E_QBUF_SIZE_EXMAXI;
            break;
        }

        if (0u == element_size)
        {
            ret = LBF_E_QBUF_ELEMENT_ERROR_SIZE;
            break;
        }

        lbq->element_maxnum = data_bufsize / element_size;

        if (LBF_MIN_SIZE > lbq->element_maxnum)
        {
            ret = LBF_E_QBUF_ELEMENT_NUM_EXMINI;
            break;
        }

        lbq->buf = data_buf;
        lbq->buf_maxsize = data_bufsize;
        lbq->element_size = element_size;
        lbq->ridx = 0u;
        lbq->widx = 0u;
        lbq->full = false;
    } while (0);

    return ret;
}

/*******************************************************************************
 * @brief        Get the lite queue write buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    element: A pointer to the element buf
 *
 * @return       0 - LBF_E_OK
 *               40 - LBF_E_QBUF_NOSPACE
 ******************************************************************************/
uint8_t lbq_get_wbuf(lbqcb_t *lbq, void **element)
{
    if (true == lbq_is_full(lbq))
        return LBF_E_QBUF_NOSPACE;

    *element =
        (void *)(((uint8_t *)lbq->buf) + (lbq->widx * lbq->element_size));
    lbq->widx = (lbq->widx + 1u) % lbq->element_maxnum;
    lbq->full = lbq->widx == lbq->ridx;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Get the lite queue read buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    element: A pointer to the element buf
 *
 * @return       0 - LBF_E_OK
 *               41 - LBF_E_QBUF_NOENOUGH_DATA
 ******************************************************************************/
uint8_t lbq_get_rbuf(lbqcb_t *lbq, void **element)
{
    if (true == lbq_is_empty(lbq))
        return LBF_E_QBUF_NOENOUGH_DATA;

    *element =
        (void *)(((uint8_t *)lbq->buf) + (lbq->ridx * lbq->element_size));
    lbq->ridx = (lbq->ridx + 1u) % lbq->element_maxnum;
    lbq->full = false;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Get the lite queue write buffer without update write idx
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    element: A pointer to the element buf
 *
 * @return       0 - LBF_E_OK
 *               40 - LBF_E_QBUF_NOSPACE
 ******************************************************************************/
uint8_t lbq_get_wbuf_noupdate(lbqcb_t *lbq, void **element)
{
    if (true == lbq_is_full(lbq))
        return LBF_E_QBUF_NOSPACE;

    *element =
        (void *)(((uint8_t *)lbq->buf) + (lbq->widx * lbq->element_size));

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Get the lite queue read buffer without update read idx
 *
 * @param[in]    lbc: lbc handle
 *
 * @param[in]    element: A pointer to the element buf
 *
 * @return       0 - LBF_E_OK
 *               41 - LBF_E_QBUF_NOENOUGH_DATA
 ******************************************************************************/
uint8_t lbq_get_rbuf_noupdate(lbqcb_t *lbq, void **element)
{
    if (true == lbq_is_empty(lbq))
        return LBF_E_QBUF_NOENOUGH_DATA;

    *element =
        (void *)(((uint8_t *)lbq->buf) + (lbq->ridx * lbq->element_size));

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Update the lite queue write buffer idx
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       0 - LBF_E_OK
 *               1 - LBF_E_NOT_OK
 ******************************************************************************/
uint8_t lbq_wbuf_update(lbqcb_t *lbq)
{
    lbq->widx = (lbq->widx + 1u) % lbq->element_maxnum;
    lbq->full = lbq->widx == lbq->ridx;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Update the lite queue read buffer idx
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       0 - LBF_E_OK
 *               1 - LBF_E_NOT_OK
 ******************************************************************************/
uint8_t lbq_rbuf_update(lbqcb_t *lbq)
{
    lbq->ridx = (lbq->ridx + 1u) % lbq->element_maxnum;
    lbq->full = false;

    return LBF_E_OK;
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is full
 *
 * @param[in]    lbq: lbq handle
 *
 * @return       true or false
 ******************************************************************************/
bool lbq_is_full(lbqcb_t *lbq)
{
    return lbq->full;
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is empty
 *
 * @param[in]    lbq: lbq handle
 *
 * @return       true or false
 ******************************************************************************/
bool lbq_is_empty(lbqcb_t *lbq)
{
    return ((true != lbq->full) && (lbq->ridx == lbq->widx));
}

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
uint8_t lbc_init(lbccb_t *lbc,
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

        if (LBF_MIN_SIZE > chapter_num)
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
        lbc->chapter_maxnum = chapter_num;
        lbc->ridx = 0u;
        lbc->widx = 0u;
        lbc->full = false;
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
uint8_t lbc_write_data(lbccb_t *lbc, void *in_data, uint32_t length)
{
    uint8_t ret = LBF_E_OK;

    if (true != lbc_chapter_is_full(lbc))
    {
        ret = lbn_write_data(&(lbc->base_handle), in_data, length);
        if (LBF_E_OK == ret)
        {
            lbc->chapter_buf[lbc->widx] = length;
            lbc->widx = (lbc->widx + 1u) % lbc->chapter_maxnum;
            lbc->full = lbc->widx == lbc->ridx;
        }
    }
    else
    {
        ret = LBF_E_CBUF_NOSPACE;
    }

    return ret;
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
uint8_t lbc_read_data(lbccb_t *lbc,
                      void *out_data,
                      uint32_t *out_length,
                      uint32_t outbuf_size)
{
    uint8_t ret = LBF_E_OK;
    uint32_t data_len = 0;

    if (true != lbc_chapter_is_empty(lbc))
    {
        data_len = lbc->chapter_buf[lbc->ridx];
        if (LBF_NULL != out_length)
            *out_length = data_len > outbuf_size ? outbuf_size : data_len;
        lbc->ridx = (lbc->ridx + 1u) % lbc->chapter_maxnum;
        lbc->full = false;
        ret =
            lbn_read_data(&(lbc->base_handle), out_data, data_len, outbuf_size);
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
bool lbc_chapter_is_full(lbccb_t *lbc)
{
    return lbc->full;
}

/*******************************************************************************
 * @brief        Determine whether the chapter buffer is empty
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       True or False
 ******************************************************************************/
bool lbc_chapter_is_empty(lbccb_t *lbc)
{
    return ((true != lbc->full) && (lbc->ridx == lbc->widx));
}

/*******************************************************************************
 * @brief        Get the number of chapters stored in the buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       chapter number
 ******************************************************************************/
uint32_t lbc_get_chapter_number(lbccb_t *lbc)
{
    if (true == lbc->full)
        return lbc->chapter_maxnum;

    if (lbc->ridx <= lbc->widx)
        return (lbc->widx - lbc->ridx);
    else
        return (lbc->chapter_maxnum - lbc->ridx + lbc->widx);
}

/*******************************************************************************
 * @brief        Get the remaining space of the chapter buffer
 *
 * @param[in]    lbc: lbc handle
 *
 * @return       chapter buffer free size
 ******************************************************************************/
uint32_t lbc_get_data_free_size(lbccb_t *lbc)
{
    return lbn_get_free_size(&(lbc->base_handle));
}

/*******************************************************************************
 * @brief        Initialize a lite ringbuffer
 *
 * @param[in]    lbn: handle of ringbuffer lbn
 *
 * @param[in]    buf_addr: A buffer to store data
 *
 * @param[in]    buf_size: The size of the data that can be stored
 *
 * @return       0 - LBF_E_OK
 *               other - LBF_ERROR_CODE
 ******************************************************************************/
uint8_t lbn_init(lbncb_t *lbn, uint8_t *buf_addr, uint32_t buf_size)
{
    uint8_t ret = LBF_E_OK;

    do
    {
        if (LBF_NULL == lbn)
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

        lbn->head = 0;
        lbn->tail = 0;
        lbn->used_len = 0;
        lbn->data_buf = buf_addr;
        lbn->max_len = buf_size;
    } while (0);

    return ret;
}

/*******************************************************************************
 * @brief        Write data to the lite ringbuffer
 *
 * @param[in]    lbn: lbn handle
 *
 * @param[in]    in_data: Data to be written
 *
 * @param[in]    length: Length of data to be written
 *
 * @return       0  - LBF_E_OK
 *               10 - LBF_E_DBUF_NOSPACE
 ******************************************************************************/
uint8_t lbn_write_data(lbncb_t *lbn, void *in_data, uint32_t length)
{
    if (length > (lbn->max_len - lbn->used_len))
        return LBF_E_DBUF_NOSPACE;
    else
    {
        uint8_t *p_data = (uint8_t *)in_data;
        if (length > (lbn->max_len - lbn->tail))
        {
            uint32_t write_size_a = 0, write_size_b = 0;
            write_size_a = lbn->max_len - lbn->tail;
            write_size_b = length - write_size_a;
            memcpy(&lbn->data_buf[lbn->tail], &p_data[0], write_size_a);
            memcpy(&lbn->data_buf[0], &p_data[write_size_a], write_size_b);
            lbn->tail = write_size_b;
        }
        else
        {
            memcpy(&lbn->data_buf[lbn->tail], &p_data[0], length);
            lbn->tail += length;
            if (lbn->tail == lbn->max_len)
                lbn->tail = 0;
        }
        lbn->used_len += length;

        return LBF_E_OK;
    }
}

/*******************************************************************************
 * @brief        Read data from the lite ringbuffer
 *
 * @param[in]    lbn: lbn handle
 *
 * @param[out]   out_data: Store data to be read
 *
 * @param[out]   out_length: The length of data read
 *
 * @param[in]    outbuf_size: out data buf max size
 *
 * @return       0  - LBF_E_OK
 *               12 - LBF_E_DBUF_NOENOUGH_DATA
 ******************************************************************************/
uint8_t lbn_read_data(lbncb_t *lbn,
                      void *out_data,
                      uint32_t length,
                      uint32_t outbuf_size)
{
    uint32_t tmp_length = 0u;

    if (length > lbn->used_len)
        return LBF_E_DBUF_NOENOUGH_DATA;
    else
    {
        uint8_t *p_data = (uint8_t *)out_data;
        if (length > (lbn->max_len - lbn->head))
        {
            uint32_t write_size_a = 0, write_size_b = 0;
            write_size_a = lbn->max_len - lbn->head;
            write_size_b = length - write_size_a;
            if (write_size_a > outbuf_size)
            {
                memcpy(&p_data[0], &lbn->data_buf[lbn->head], outbuf_size);
            }
            else
            {
                memcpy(&p_data[0], &lbn->data_buf[lbn->head], write_size_a);
                tmp_length = outbuf_size - write_size_a;
                tmp_length =
                    write_size_b > tmp_length ? tmp_length : write_size_b;
                memcpy(&p_data[write_size_a], &lbn->data_buf[0], tmp_length);
            }
            lbn->head = write_size_b;
        }
        else
        {
            memcpy(&p_data[0], &lbn->data_buf[lbn->head], length);
            lbn->head += length;
            if (lbn->head == lbn->max_len)
                lbn->head = 0;
        }
        lbn->used_len -= length;

        return LBF_E_OK;
    }
}

/*******************************************************************************
 * @brief        Get the space used by ringbuffer
 *
 * @param[in]    lbn: lbn handle
 *
 * @return       ringbuffer used size
 ******************************************************************************/
uint32_t lbn_get_used_size(lbncb_t *lbn)
{
    return lbn->used_len;
}

/*******************************************************************************
 * @brief        Get the remaining space of the lite ringbuffer
 *
 * @param[in]    lbn: lbn handle
 *
 * @return       ringbuffer free size
 ******************************************************************************/
uint32_t lbn_get_free_size(lbncb_t *lbn)
{
    return (lbn->max_len - lbn->used_len);
}
