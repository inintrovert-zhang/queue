/**
  ******************************************************************************
  * 版权所有： 
  * 文件名:   queue.c 
  * 作者：    zwy
  * 创建日期: 2023.05.13
  * 描述： 	此文档提供了队列的基本操作，可以适用于各种数据类型。
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
    unsigned short capacity;            //队列能够容纳成员的数目
    unsigned short front;               //循环队列的头部
    unsigned short rear;                //循环队列的尾部
    unsigned short counter;             //循环队列中当前成员个数
    unsigned short max_iterm_size;      //循环队列单个成员占用字节数
    unsigned char *buf;                 //队列数据存放区
};

typedef struct queue_record  queue_t;

enum
{
	QUEUE_OP_SUCCESS = 0,          //操作成功
	QUEUE_OP_FAIL = (-1),          //操作失败
	QUEUE_OP_ERR_NO_MEM = (-2),    //队列已满
	QUEUE_OP_ERR_EMPTY = (-3),     //队列已空
};

int queue_init(queue_t * p_queue, unsigned short maxelements, unsigned char *buf, unsigned short max_iterm_size);
int queue_enqueue(queue_t * p_queue, const unsigned char *buf, unsigned short buf_size);
int queue_dequeue(queue_t * p_queue, unsigned char *buf, unsigned short buf_size);
bool queue_is_empty(queue_t * p_queue);
bool queue_is_full(queue_t * p_queue); 
void queue_make_empty(queue_t * p_queue);
#endif
