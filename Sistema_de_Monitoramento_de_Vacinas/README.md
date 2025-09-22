# Sistema de Monitoramento de Vacinas

Este projeto implementa um **sistema embarcado de monitoramento de vacinas** utilizando a **BitDogLab (Raspberry Pi Pico W)** com **FreeRTOS**.  
Ele realiza a leitura de dados de sensores de temperatura, exibe informações em um display OLED, e, quando a temperatura medida excede o limite estipulado, envia os registros para a nuvem via **ThingSpeak** e gerencia automaticamente um **buffer local** para evitar perda de dados em caso de desconexão Wi-Fi. 

---

## Funcionalidades

- **Leitura de Sensores**  
  Coleta de temperatura, umidade e outros dados por meio da tarefa `sensors_task`.

- **Envio para ThingSpeak**  
  Comunicação com a nuvem para armazenamento e visualização dos dados.

- **Gerenciamento de Buffer**  
  - Quando o **Wi-Fi está desconectado**, os dados são salvos localmente no buffer.  
  - Quando o **Wi-Fi reconecta**, os dados acumulados são enviados em lote para o ThingSpeak.  

- **Interface de Usuário**  
  - **Botão** para iniciar/parar leituras.  
  - **Joystick** para navegação no display OLED.  
  - **Display OLED** exibe status do sistema e dados coletados.  
  - **LED RGB** e **Buzzer** para feedback visual e sonoro.

- **Sincronização de Horário via NTP**  
  Atualização automática do **RTC** para registro confiável de data/hora.

- **Logger**  
  Registro de eventos e depuração.

---

## Fluxo de Execução

1. Inicialização dos periféricos e bibliotecas (`logger`, `rtc_ntp`, `button`, `joystick`, `led`, `buzzer`, etc).
2. Criação das tarefas principais:  
   - `wifi_task` → Conexão Wi-Fi.  
   - `sensors_task` → Leitura dos sensores.  
   - `display_task` → Interface OLED.  
   - `thingspeak_task` → Envio de dados à nuvem.  
   - `buffer_manager_task` → Controle do buffer de dados.
3. Execução do **scheduler do FreeRTOS**.

---

## Requisitos

- **Placa:** Raspberry Pi Pico W (BitDogLab compatível).  
- **SO:** FreeRTOS para RP2040.  
- **Bibliotecas utilizadas:**  
  - `pico/stdlib.h`  
  - `FreeRTOS.h`, `task.h`, `queue.h`  
  - Drivers personalizados (`button`, `joystick`, `led`, `buzzer`, `display`, etc.).  

---

## Funcionamento do Buffer

- Se **Wi-Fi desconectar**:
  - Novas leituras são salvas no buffer a cada 3 minutos (180 s).  
- Se **Wi-Fi reconectar**:
  - Dados acumulados são enviados em lote para o ThingSpeak.  
  - Após envio, o buffer é limpo.  

---


