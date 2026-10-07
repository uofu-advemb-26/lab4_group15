#include <fifo.h>

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id) {
    for (;;) {
        struct request_msg data_buffer;
        if (xQueueReceive(requests, &data_buffer, portMAX_DELAY) == pdPASS) {
            data_buffer.output = data_buffer.input + 5;
            data_buffer.handled_by = id;
            
            if (xQueueSendToBack(results, &data_buffer, portMAX_DELAY) == errQUEUE_FULL) {
                printf("Results Thread is Full");
            }
        } else { printf("Failed to Pull from Requests Queue"); }
    }
}