#include "queue.h"
#include "stdio.h"
#include <string.h>

//测试结构体1
typedef struct 
{
    int a;
    int b;
    int c;
}test_1_t;

//测试结构体2
typedef struct 
{
    short d;
    char e;
    int f;
}test_2_t;

//队列1缓存区数组大小
#define TEST_1_BUF_SIZE  20
//队列2缓存区数组大小
#define TEST_2_BUF_SIZE  10

//队列1缓存区
test_1_t m_test_1_buf[TEST_1_BUF_SIZE];

//队列2缓存区
test_2_t m_test_2_buf[TEST_2_BUF_SIZE];

//队列1
queue_t m_test_1_queue;
//队列2
queue_t m_test_2_queue;

int main()
{
    //队列初始化
    queue_init(&m_test_1_queue, TEST_1_BUF_SIZE, (unsigned char *)&m_test_1_buf, sizeof(test_1_t));
    queue_init(&m_test_2_queue, TEST_2_BUF_SIZE, (unsigned char *)&m_test_2_buf, sizeof(test_2_t));
    while(1)
    {
        char ch = getchar();
        unsigned char key_code = 0;
        switch(ch)
        {   
            case '1': 
            {
                //入列操作
                test_1_t dat = {1,2,3};
                int ret = queue_enqueue(&m_test_1_queue, (unsigned char *)&dat, sizeof(test_1_t));  
                if(ret == QUEUE_OP_SUCCESS)
                {
                    printf("1 enqueue ok!\n");
                }
                else
                {
                    printf("1 enqueue fail..%d\n", ret);
                }
                break;
            }   
            case '2': 
            {
                 //入列操作
                test_2_t dat = {4,5,6};
                int ret = queue_enqueue(&m_test_2_queue, (unsigned char *)&dat, sizeof(test_2_t));  
                if(ret == QUEUE_OP_SUCCESS)
                {
                    printf("2 enqueue ok!\n");
                }
                else
                {
                    printf("2 enqueue fail..%d\n", ret);
                }
                break;
            }               
            case 'd': 
            {
                 //出列操作
                test_1_t dat1;
                int ret = queue_dequeue(&m_test_1_queue, (unsigned char *)&dat1, sizeof(test_1_t));
                if(ret == QUEUE_OP_SUCCESS)
                {
                    printf("1 dequeue ok!\n");
                }
                else
                {
                    printf("1 dequeue fail..%d\n", ret);
                }                
                break;
            }   
            case 'f': 
            {
                //出列操作
                test_2_t dat2;
                int ret = queue_dequeue(&m_test_2_queue, (unsigned char *)&dat2, sizeof(test_2_t));
                if(ret == QUEUE_OP_SUCCESS)
                {
                    printf("2 dequeue ok!\n");
                }
                else
                {
                    printf("2 dequeue fail..%d\n", ret);
                }              
                break;
            }                                                
        }

        if(ch == 'b')
        {
            break;
        }

    }

    printf("hahahhah\n");
    return 0;
}




