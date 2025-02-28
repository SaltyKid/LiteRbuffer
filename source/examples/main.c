/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    main.c
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
#include <stdint.h>
#include <stdio.h>
#include "lite_ring_buffer.h"

/*========================= PERIPHERAL DECLARATION ===========================*/
#define DEBUG_LBN_DATA_SIZE (512u)

#define DEBUG_LBC_DATA_SIZE    (512u)
#define DEBUG_LBC_CHAPTER_SIZE (4u)

#define DEBUG_LBQ_DATA_SIZE (512u)

/*============================ GLOBAL VARIABLES ==============================*/

DECLARE_LBN_BUFFER(rbn, DEBUG_LBN_DATA_SIZE);
DECLARE_LBC_BUFFER(rbc, DEBUG_LBC_DATA_SIZE, DEBUG_LBC_CHAPTER_SIZE);
DECLARE_LBQ_BUFFER(rbq, DEBUG_LBQ_DATA_SIZE);

/*========================== FUNCTION PROTOTYPES =============================*/
static void debug_lbc_test(void);
static void debug_lbn_test(void);
static void debug_lbq_test(void);

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
int main(int argc, char *argv[])
{
    debug_lbn_test();
    debug_lbc_test();
    debug_lbq_test();

    return 0;
}

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void debug_lbn_test(void)
{
    uint8_t rd_data[64];
    uint32_t num = 0;

    printf("\r\n==== lbn test ==== \r\n");
    LBN_BUFFER_INIT(rbn, DEBUG_LBN_DATA_SIZE);

    lbn_write_data(&rbn, "string1", 8);
    lbn_write_data(&rbn, "string2", 8);
    lbn_write_data(&rbn, "string3", 8);
    lbn_write_data(&rbn, "string4", 8);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");

    lbn_write_data(&rbn, "string5", 8);
    lbn_write_data(&rbn, "string6", 8);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");

    lbn_write_data(&rbn, "string7", 8);
    lbn_write_data(&rbn, "string8", 8);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");

    lbn_write_data(&rbn, "string9", 8);
    lbn_write_data(&rbn, "string10", 9);
    lbn_write_data(&rbn, "string11", 9);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");

    lbn_write_data(&rbn, "string12", 9);
    lbn_write_data(&rbn, "string13", 9);
    lbn_write_data(&rbn, "string14", 9);
    lbn_write_data(&rbn, "string15", 9);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");

    lbn_write_data(&rbn, "string16", 9);
    lbn_write_data(&rbn, "string17", 9);
    lbn_write_data(&rbn, "string18", 9);
    lbn_write_data(&rbn, "string19", 9);

    num = lbn_get_used_size(&rbn);
    lbn_read_data(&rbn, rd_data, num, sizeof(rd_data));
    for (uint32_t i = 0u; i < num && i < sizeof(rd_data); i++)
    {
        printf("%c", rd_data[i]);
    }
    printf("\r\n");
}

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void debug_lbc_test(void)
{
    uint8_t rd_data[32];
    uint32_t num = 0u, rd_len = 0u;

    printf("\r\n==== lbc test ==== \r\n");
    LBC_BUFFER_INIT(rbc, DEBUG_LBC_DATA_SIZE, DEBUG_LBC_CHAPTER_SIZE);

    lbc_write_data(&rbc, "string1", 8);
    lbc_write_data(&rbc, "string2", 8);
    lbc_write_data(&rbc, "string3", 8);
    lbc_write_data(&rbc, "string4", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }

    lbc_write_data(&rbc, "string5", 8);
    lbc_write_data(&rbc, "string6", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }

    lbc_write_data(&rbc, "string7", 8);
    lbc_write_data(&rbc, "string8", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }

    lbc_write_data(&rbc, "string9", 8);
    lbc_write_data(&rbc, "string10", 9);
    lbc_write_data(&rbc, "string11", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }

    lbc_write_data(&rbc, "string12", 9);
    lbc_write_data(&rbc, "string13", 9);
    lbc_write_data(&rbc, "string14", 9);
    lbc_write_data(&rbc, "string15", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }

    lbc_write_data(&rbc, "string16", 9);
    lbc_write_data(&rbc, "string17", 9);
    lbc_write_data(&rbc, "string18", 9);
    lbc_write_data(&rbc, "string19", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, &rd_len, sizeof(rd_data));
        for (uint32_t i = 0u; i < rd_len && i < sizeof(rd_data); i++)
        {
            printf("%c", rd_data[i]);
        }
        printf("\r\n");
    }
}

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void debug_lbq_test(void)
{
    struct delqb_test
    {
        uint16_t len;
        char data[30];
    } *p_buf;
    int fmtret = 0;

    printf("\r\n==== lbq test ==== \r\n");
    LBQ_BUFFER_INIT(rbq, DEBUG_LBQ_DATA_SIZE, sizeof(struct delqb_test));

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string1");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string2");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string3");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string4");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string5");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string6");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string7");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string8");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string9");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string10");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string11");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string12");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string13");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string14");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string15");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string16");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string17");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string18");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    lbq_get_wbuf(&rbq, (void *)&p_buf);
    fmtret = snprintf(&p_buf->data[0], sizeof(p_buf->data), "string19");
    if (0 < fmtret)
    {
        p_buf->len = fmtret;
    }

    while (true != lbq_is_empty(&rbq))
    {
        if (LBF_E_OK != lbq_get_rbuf(&rbq, (void *)&p_buf))
        {
            break;
        }

        for (uint16_t i = 0u; i < p_buf->len; i++)
        {
            printf("%c", p_buf->data[i]);
        }
        printf("\r\n");
    }
}
