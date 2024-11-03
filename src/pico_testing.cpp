#include <stdio.h>
#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include "FreeRTOSConfig.h"

#include "task.h"
#include "queue.h"



QueueHandle_t xQueue = NULL;

TaskHandle_t led_task_handle = NULL;
TaskHandle_t print_task_handle = NULL;


void receive_task(void *pvParameters) {

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    int data;

    while(true) {
        // gpio_put(PICO_DEFAULT_LED_PIN, !gpio_get(PICO_DEFAULT_LED_PIN));
        if (xQueueReceive(xQueue, &data, portMAX_DELAY) == pdPASS) {
            printf("Received data: %d\n", data);
        }

        // vTaskDelay(10);
    }
}

void send_task(void *pvParameters) {

    while(true) {
        for(int i = 0; i != 5000; i++) {
            xQueueSend(xQueue, &i, 0);
            // vTaskDelay(10);
        }
    }
}


int main() {
    stdio_init_all();

    sleep_ms(5000);


    xQueue = xQueueCreate(1, sizeof(int));


    xTaskCreate(receive_task,
                "Receivy",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY+1,
                &led_task_handle);

    xTaskCreate(send_task,
                "Sendy",
                configMINIMAL_STACK_SIZE,
                NULL,
                tskIDLE_PRIORITY,
                &print_task_handle);


    vTaskStartScheduler();

    while(true) {
        printf("Scheduler exits\n");
        sleep_ms(200);
    }
}
