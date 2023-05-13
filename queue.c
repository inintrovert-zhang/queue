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
#include "queue.h"

/******************************************************************************
 * 函数名:	succ 
 * 描述: 
 *            -队列索引值往后移一位
 * 输入参数: 
 * 输出参数: 
 * 返回值: 
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
static unsigned short succ( unsigned short value, queue_t * q )
{
	if ( ++value == q->capacity )
	{
		value = 0;
	}
	return value;
}

/******************************************************************************
 * 函数名:	queue_is_empty 
 * 描述: 
 *            -判断队列是否已空
 * 输入参数: 
 * 输出参数: 
 * 返回值: 
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
bool queue_is_empty(queue_t * q)
{
	return q->counter == 0;
}

/******************************************************************************
 * 函数名:	queue_is_full 
 * 描述: 
 *            -判断队列是否已满
 * 输入参数: 
 * 输出参数: 
 * 返回值: 
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
bool queue_is_full(queue_t * q)
{
	return q->counter == q->capacity;
}

/******************************************************************************
 * 函数名:	queue_init 
 * 描述: 
 *            -队列清空
 * 输入参数: 
 * 输出参数: 
 * 返回值: 
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
void queue_make_empty( queue_t * q )
{
	q->counter = 0;
	q->front = 1;
	q->rear = 0;
}

/******************************************************************************
 * 函数名:	queue_init 
 * 描述: 
 *            -队列初始化
 * 输入参数: 
 *  			p_queue-队列指针
 * 				maxelements-队列能够容纳成员的数目
 * 				buf-队列数据存放位置
 * 				max_iterm_size-队列单个成员占用字节数
 * 输出参数: 
 * 返回值: 		返回操作结果
 * 				QUEUE_OP_SUCCESS-操作成功
 * 				QUEUE_OP_FAIL-操作失败
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
int queue_init(queue_t *p_queue, unsigned short maxelements, unsigned char *buf, unsigned short max_iterm_size)
{
	if(p_queue == NULL || buf == NULL || maxelements < 2 || max_iterm_size < 1)
	{
		return QUEUE_OP_FAIL;
	}
	p_queue->buf = buf;
	p_queue->capacity = maxelements;
	p_queue->max_iterm_size = max_iterm_size;
	queue_make_empty(p_queue);

	return QUEUE_OP_SUCCESS;
}

/******************************************************************************
 * 函数名:	queue_enqueue 
 * 描述: 
 *            -队列入列操作
 * 输入参数: 
 *  			p_queue-队列指针
 * 				buf-入列数据
 * 				buf_size-入列数据字节数，需小于type_size
 * 输出参数: 
 * 返回值: 		返回操作结果
 * 				QUEUE_OP_SUCCESS-操作成功
 *				QUEUE_OP_FAIL-操作失败，参数有误
 * 				QUEUE_OP_ERR_NO_MEM-操作失败，队列已满
 * 
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
int queue_enqueue(queue_t *p_queue, const unsigned char *buf, unsigned short buf_size)
{
	if(p_queue == NULL || buf == NULL || buf_size > p_queue->max_iterm_size)
	{
		return QUEUE_OP_FAIL;
	}	

	if(queue_is_full( p_queue ))
	{
		return QUEUE_OP_ERR_NO_MEM;
	}

	p_queue->counter++;
	p_queue->rear = succ( p_queue->rear, p_queue );	
	memcpy(p_queue->buf + p_queue->rear * p_queue->max_iterm_size, buf, p_queue->max_iterm_size);

	return QUEUE_OP_SUCCESS;
}

/******************************************************************************
 * 函数名:	queue_dequeue 
 * 描述: 
 *            -队列出列操作
 * 输入参数: 
 * 				p_queue-队列指针
 * 				buf_size-出列数据字节数，小于type_size
 * 输出参数: 
 *				buf-出列数据
 * 返回值: 
 * 				QUEUE_OP_SUCCESS-操作成功
 *				QUEUE_OP_FAIL-操作失败，参数有误 
 * 				QUEUE_OP_ERR_EMPTY-操作失败，队列已空
 * 作者: 
 * 创建日期:
 * 
 *------------------------
 * 修改人:
 * 修改日期:
 ******************************************************************************/
int queue_dequeue(queue_t * p_queue, unsigned char *buf, unsigned short buf_size)
{
	if(p_queue == NULL || buf == NULL || buf_size > p_queue->max_iterm_size)
	{
		return QUEUE_OP_FAIL;
	}	

	if (queue_is_empty( p_queue ))
	{
		return QUEUE_OP_ERR_EMPTY;
	}	

	memcpy(buf, p_queue->buf + p_queue->front * p_queue->max_iterm_size, buf_size);
	p_queue->counter--;
	p_queue->front = succ( p_queue->front, p_queue );	

	return QUEUE_OP_SUCCESS;	
}
