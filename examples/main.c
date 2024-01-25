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

/*============================ GLOBAL VARIABLES ==============================*/

#define BASE_SIZE 512
#define CHAPTER_SIZE 4

static uint8_t buffer_base[BASE_SIZE];
static uint32_t buffer_chapter[CHAPTER_SIZE];
static lbf_chapter_t rbc;

/*========================== FUNCTION PROTOTYPES =============================*/

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
int main(int argc, char *argv[])
{
    uint8_t rd_data[32];
    uint32_t num = 0;

    lbc_init(&rbc, buffer_base, BASE_SIZE, buffer_chapter, CHAPTER_SIZE);

    lbc_write_data(&rbc, "string1", 8);
    lbc_write_data(&rbc, "string2", 8);
    lbc_write_data(&rbc, "string3", 8);
    lbc_write_data(&rbc, "string4", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    lbc_write_data(&rbc, "string5", 8);
    lbc_write_data(&rbc, "string6", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    lbc_write_data(&rbc, "string7", 8);
    lbc_write_data(&rbc, "string8", 8);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    lbc_write_data(&rbc, "string9", 8);
    lbc_write_data(&rbc, "string10", 9);
    lbc_write_data(&rbc, "string11", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    lbc_write_data(&rbc, "string12", 9);
    lbc_write_data(&rbc, "string13", 9);
    lbc_write_data(&rbc, "string14", 9);
    lbc_write_data(&rbc, "string15", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    lbc_write_data(&rbc, "string16", 9);
    lbc_write_data(&rbc, "string17", 9);
    lbc_write_data(&rbc, "string18", 9);
    lbc_write_data(&rbc, "string19", 9);

    num = lbc_get_chapter_number(&rbc);
    for (uint32_t i = 0; i < num; i++)
    {
        lbc_read_data(&rbc, rd_data, NULL);
        printf("%s\r\n", rd_data);
    }

    return 0;
}
