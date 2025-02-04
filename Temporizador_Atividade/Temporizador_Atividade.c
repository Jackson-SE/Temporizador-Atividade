/*Atividade 2 realizada em atendimento à proposta de Tarefa em 29/01/2025
                       Semáforo
Residente: Jackson da Silva Carneiro
*/
#include <stdio.h>
#include "pico/time.h"
#include "pico/stdlib.h"


#define LED_PIN_RED 13      // led vermelho
#define LED_PIN_BLUE 12     //led azul
#define LED_PIN_GREEN 11  //led verde
#define BUTTON_A 5       //Push Button A
absolute_time_t turn_off_time; // tempo para desligar o led
bool led_ativo = false;   //indica estado do led, será usada no alarme.


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

int64_t turn_off_callback(alarm_id_t id, void *user_data){  // função do alarme, irá garantir que todos leds desliguem
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
            
}stdio_i

int main()                    
{
    stdio_init_all(); //inicializa as bibliotecas padrão
    configura_GPIO();//busca a função e configura os pinos GPIO's utilizados no código


    while (true) {
       if(gpio_get(BUTTON_A) == 0 && !led_ativo){  //verifica se o botão foi pressionado e se os leds estão desligados
       sleep_ms(50);  //debounce para garantir que o botão foi pressionado
       if (gpio_get(BUTTON_A) == 0){   
        liga_leds();
        led_ativo = true;  
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); //alarme adicionado só permitirá novo acionamento do botão após o tempo definido
       }
    }
    sleep_ms(10);
    }   
}