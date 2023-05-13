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
#include "queue.h"

/******************************************************************************
 * ������:	succ 
 * ����: 
 *            -��������ֵ������һλ
 * �������: 
 * �������: 
 * ����ֵ: 
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
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
 * ������:	queue_is_empty 
 * ����: 
 *            -�ж϶����Ƿ��ѿ�
 * �������: 
 * �������: 
 * ����ֵ: 
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
 ******************************************************************************/
bool queue_is_empty(queue_t * q)
{
	return q->counter == 0;
}

/******************************************************************************
 * ������:	queue_is_full 
 * ����: 
 *            -�ж϶����Ƿ�����
 * �������: 
 * �������: 
 * ����ֵ: 
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
 ******************************************************************************/
bool queue_is_full(queue_t * q)
{
	return q->counter == q->capacity;
}

/******************************************************************************
 * ������:	queue_init 
 * ����: 
 *            -�������
 * �������: 
 * �������: 
 * ����ֵ: 
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
 ******************************************************************************/
void queue_make_empty( queue_t * q )
{
	q->counter = 0;
	q->front = 1;
	q->rear = 0;
}

/******************************************************************************
 * ������:	queue_init 
 * ����: 
 *            -���г�ʼ��
 * �������: 
 *  			p_queue-����ָ��
 * 				maxelements-�����ܹ����ɳ�Ա����Ŀ
 * 				buf-�������ݴ��λ��
 * 				max_iterm_size-���е�����Առ���ֽ���
 * �������: 
 * ����ֵ: 		���ز������
 * 				QUEUE_OP_SUCCESS-�����ɹ�
 * 				QUEUE_OP_FAIL-����ʧ��
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
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
 * ������:	queue_enqueue 
 * ����: 
 *            -�������в���
 * �������: 
 *  			p_queue-����ָ��
 * 				buf-��������
 * 				buf_size-���������ֽ�������С��type_size
 * �������: 
 * ����ֵ: 		���ز������
 * 				QUEUE_OP_SUCCESS-�����ɹ�
 *				QUEUE_OP_FAIL-����ʧ�ܣ���������
 * 				QUEUE_OP_ERR_NO_MEM-����ʧ�ܣ���������
 * 
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
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
 * ������:	queue_dequeue 
 * ����: 
 *            -���г��в���
 * �������: 
 * 				p_queue-����ָ��
 * 				buf_size-���������ֽ�����С��type_size
 * �������: 
 *				buf-��������
 * ����ֵ: 
 * 				QUEUE_OP_SUCCESS-�����ɹ�
 *				QUEUE_OP_FAIL-����ʧ�ܣ��������� 
 * 				QUEUE_OP_ERR_EMPTY-����ʧ�ܣ������ѿ�
 * ����: 
 * ��������:
 * 
 *------------------------
 * �޸���:
 * �޸�����:
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
