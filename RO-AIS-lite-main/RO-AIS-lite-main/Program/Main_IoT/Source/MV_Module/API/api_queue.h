/**
 * File : api_queue.h
 * 
 * Application Programming Interface
 * 
*/

#ifndef __API_QUEUE_H__
#define __API_QUEUE_H__

#include "hal_serial.h"

typedef struct {
    volatile uint8_t *buffer;
    uint16_t size;
    volatile uint16_t head;
    volatile uint16_t tail;
} CircularQueue;

void Queue_Init(CircularQueue* queue, uint8_t *buffer_array, uint16_t buffer_size);
uint8_t Queue_Enqueue(CircularQueue* queue, uint8_t data);
uint8_t Queue_Dequeue(CircularQueue* queue, uint8_t* data);
uint8_t Queue_IsEmpty(const CircularQueue* queue);
uint8_t Queue_IsFull(const CircularQueue* queue);


#endif /*__API_QUEUE_H__*/

