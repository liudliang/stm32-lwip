/**
  *****************************************************************************
  * @file    ethernet_test.c
  * @author  Zorb
  * @version V1.0.0
  * @date    2018-09-04
  * @brief   ��̫��֡���ݷ�������ղ��Ե�ʵ��
  *****************************************************************************
  * @history
  *
  * 1. Date:2018-09-04
  *    Author:Zorb
  *    Modification:�����ļ�
  *
  *****************************************************************************
  */

#include "stm32f4xx_hal.h"
#include "lwip.h"

/******************************************************************************
 * ����  : ��̫��֡���Ͳ���1
 * ����  : ��
 * ����  : ��
******************************************************************************/
void ethernet_sendtest1(void)
{
    uint8_t frame_data[] =
    {
        /* ��̫��֡��ʽ */
        0x50,0xFA,0x84,0x15,0x3C,0x3C,                            /* Զ��MAC */
        0x0,0x80,0xE1,0x0,0x0,0x0,                                /* ����MAC */
        0x8,0x0,                                                  /* ip���� */
        0x45,0x0,0x0,0x26/*l*/,0x0,0x0,0x0,0x0,0xFF,0x11,0x0,0x0, /* UDP��ͷ */
        0xC0,0xA8,0x2,0x8,                                        /* ����IP */
        0xC0,0xA8,0x2,0xC2,                                       /* Զ��IP */
        0x22,0xB0,0x22,0xB1,0x0,0x12,0x0,0x0,0x68,                /* ���� */
        0x65,0x6C,0x6C,0x6F,0x20,0x7A,0x6F,0x72,0x62              /* ���� */
    };
        
    struct pbuf *p;
    
    /* ���仺�����ռ� */
    p = pbuf_alloc(PBUF_TRANSPORT, 0x26 + 14, PBUF_POOL);
    
    if (p != NULL)
    {
        /* ��仺�������� */
        pbuf_take(p, frame_data, 0x26 + 14);

        /* ������ֱ��ͨ���ײ㷢�� */
        gnetif.linkoutput(&gnetif, p);

        /* �ͷŻ������ռ� */
        pbuf_free(p);
    }
}

/******************************************************************************
 * ����  : ��̫��֡���Ͳ���2
 * ����  : ��
 * ����  : ��
******************************************************************************/
void ethernet_sendtest2(void)
{
    uint8_t dstAddr[6] = {0x50,0xFA,0x84,0x15,0x3C,0x3C};         /* Զ��MAC */
    
    uint8_t frame_data[] =
    {
        /* UDP֡��ʽ */
        0x45,0x0,0x0,0x26/*l*/,0x0,0x0,0x0,0x0,0xFF,0x11,0x0,0x0, /* UDP��ͷ */
        0xC0,0xA8,0x2,0x8,                                        /* ����IP */
        0xC0,0xA8,0x2,0xC2,                                       /* Զ��IP */
        0x22,0xB0,0x22,0xB1,0x0,0x12,0x0,0x0,0x68,                /* ���� */
        0x65,0x6C,0x6C,0x6F,0x20,0x7A,0x6F,0x72,0x62              /* ���� */
    };
        
    struct pbuf *p;
    
    /* ���仺�����ռ� */
    p = pbuf_alloc(PBUF_TRANSPORT, 0x26, PBUF_POOL);
    
    if (p != NULL)
    {
        /* ��仺�������� */
        pbuf_take(p, frame_data, 0x26);
        
        /* �����ݽ�����̫����װ����ͨ���ײ㷢�� */
        ethernet_output(&gnetif, p, (const struct eth_addr*)gnetif.hwaddr,
            (const struct eth_addr*)dstAddr, ETHTYPE_IP);

        /* �ͷŻ������ռ� */
        pbuf_free(p);
    }
}

/******************************** END OF FILE ********************************/