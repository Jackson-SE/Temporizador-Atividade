/*Atividade realizada em atendimento à proposta de Tarefa em 29/01/2025
                       Semáforo
Residente: Jackson da Silva Carneiro
*/
#include <stdio.h>
#include "pico/time.h"
#include "pico/stdlib.h"
//#include "hardware/clocks.h"
#//include "hardware/timer.h"

#define LED_PIN_RED 13      // led vermelho
#define LED_PIN_BLUE 12     //led azul
#define LED_PIN_GREEN 11  //led verde
#define BUTTON_A 5       //Push Button A
absolute_time_t turn_off_time; // tempo para desligar o led
bool led_ativo = false;
// Variáveis para controlar o estado dos LEDs e o tempo
volatile int led_state = 0; // 0: vermelho, 1: amarelo, 2: verde
volatile uint32_t timer_start_time;

void configura_GPIO(){ //CONFIGURAÇÃO DOS PINOS GPIO

    gpio_init(LED_PIN_RED);          // Inicializa o pino do LED VERMELHO
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);   // Configura como saída

    gpio_init(LED_PIN_BLUE);          // Inicializa o pino do LED AMARELO
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);   // Configura como saída

    gpio_init(LED_PIN_GREEN);        // Inicializa o pino do LED VERDE
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);   // Configura como saída

    gpio_init(BUTTON_A);                //Inicializa o pino do Push BUtton
    gpio_set_dir(BUTTON_A, GPIO_IN);   //Configura como entrada
    gpio_pull_up(BUTTON_A);           //Habilita pull up interno
}

int64_t turn_off_callback(alarm_id_t id, void *user_data){
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_BLUE, 0);
    gpio_put(LED_PIN_GREEN, 0);
    led_ativo = false;
    return 0;
}
    
void liga_leds(){
       
            gpio_put(LED_PIN_RED, true);        //liga led vermelho
            gpio_put(LED_PIN_BLUE, true);      //liga led azul
            gpio_put(LED_PIN_GREEN, true);   //liga led verde
            sleep_ms(1000);     // período de 1 segundo
                                    
            gpio_put(LED_PIN_RED, false);     //desliga led vermelho    
            gpio_put(LED_PIN_BLUE, true);   //desliga led azul        
            gpio_put(LED_PIN_GREEN, true); //desliga led verde        
            sleep_ms(1000);      //período de 1 segundo
             
            gpio_put(LED_PIN_RED, false);    //desliga led vermelho
            gpio_put(LED_PIN_BLUE, false);   //desliga led amarelo
            gpio_put(LED_PIN_GREEN, true); //liga led verde
            
    
   // return 0; // Indica que o timer deve continuar repetindo
}

int main()                    // usar turn_off_callback &  add_alarm_in_ms()
{
    stdio_init_all();
    configura_GPIO();

   // struct repeating_timer timer;
    //timer_start_time = time_us_32(); // Inicializa o tempo de início

    
    while (true) {
       if(gpio_get(BUTTON_A) == 0 && !led_ativo){
       sleep_ms(50);
       if (gpio_get(BUTTON_A) == 0){
        liga_leds();
        led_ativo = true;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
       }
    }
    sleep_ms(10);
    }
        //sleep_ms(1000);  //intervalo de impressão da mensagem no loop
    
}