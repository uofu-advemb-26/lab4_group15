#include <signaling.h>
#include <FreeRTOS.h>
#include <stdio.h>

void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data) {
    xSemaphoreTake(request, portMAX_DELAY);
    data->output = (int32_t)(data->input) + 5;

    // Signal that calculation request in done
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data) {
    
    if (xSemaphoreGive(request) == pdTRUE) {
        // Wait for calcualtion to be signaled as complete
        if (xSemaphoreTake(response, portMAX_DELAY) == pdTRUE)
            return pdTRUE;
    }
    return pdFALSE;
}