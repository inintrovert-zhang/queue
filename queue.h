/**
  ******************************************************************************
  * ��Ȩ���У� 
  * �ļ���:   queue.c 
  * ���ߣ�    zwy
  * ��������: 2023.05.13
  * ������ 	���ĵ��ṩ�˶��еĻ������������������ڸ����������͡�
  * 
  ******************************************************************************
  */
#ifndef _QUEUE_H
#define _QUEUE_H

	
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

struct queue_record
{
    unsigned short capacity;            //�����ܹ����ɳ�Ա����Ŀ
    unsigned short front;               //ѭ�����е�ͷ��
    unsigned short rear;                //ѭ�����е�β��
    unsigned short counter;             //ѭ�������е�ǰ��Ա����
    unsigned short max_iterm_size;      //ѭ�����е�����Առ���ֽ���
    unsigned char *buf;                 //�������ݴ����
};

typedef struct queue_record  queue_t;

enum
{
	QUEUE_OP_SUCCESS = 0,          //�����ɹ�
	QUEUE_OP_FAIL = (-1),          //����ʧ��
	QUEUE_OP_ERR_NO_MEM = (-2),    //��������
	QUEUE_OP_ERR_EMPTY = (-3),     //�����ѿ�
};

int queue_init(queue_t * p_queue, unsigned short maxelements, unsigned char *buf, unsigned short max_iterm_size);
int queue_enqueue(queue_t * p_queue, const unsigned char *buf, unsigned short buf_size);
int queue_dequeue(queue_t * p_queue, unsigned char *buf, unsigned short buf_size);
bool queue_is_empty(queue_t * p_queue);
bool queue_is_full(queue_t * p_queue); 
void queue_make_empty(queue_t * p_queue);
#endif
