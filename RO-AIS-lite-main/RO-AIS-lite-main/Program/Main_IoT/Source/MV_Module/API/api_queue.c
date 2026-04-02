/**
 * File : api_queue.c
 * 
 * 
 *
*/
#include "api_queue.h"
#include    "Global_Variable.h"
void Queue_Init(CircularQueue* queue, uint8_t *buffer_array, uint16_t buffer_size)
{
    queue->buffer = buffer_array;
    queue->size = buffer_size;
    queue->head = 0;
    queue->tail = 0;
}

uint8_t Queue_IsEmpty(const CircularQueue* queue)
{
    if(queue->head == queue->tail)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t Queue_IsFull(const CircularQueue* queue)
{
    if( ((queue->tail + 1) % queue->size) == (queue->head) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

uint8_t Queue_Enqueue(CircularQueue* queue, uint8_t data)
{
    if (Queue_IsFull(queue) == TRUE) 
    {
        return FALSE;
    }

    queue->tail = (queue->tail + 1) % queue->size;
    queue->buffer[queue->tail] = data;

    return TRUE;
}

uint8_t Queue_Dequeue(CircularQueue* queue, uint8_t* data)
{
    if (Queue_IsEmpty(queue) == TRUE)
    {
        return FALSE;
    }

    queue->head = (queue->head + 1) % queue->size;
    *data = queue->buffer[queue->head];

    return TRUE;
}


