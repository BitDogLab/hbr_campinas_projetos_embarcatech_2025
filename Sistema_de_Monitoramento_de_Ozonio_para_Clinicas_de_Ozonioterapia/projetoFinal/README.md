Link do repositórios do projeto: https://github.com/mauriciolasgon/monitoramento_O3/tree/sistema_medica_O3_v1.2

Projetos de Sistemas Embarcados - EmbarcaTech 2025

# 🏥 Sistema de Monitoramento de Ozônio para Clínicas de Ozonioterapia
 
**Equipe:**  Jorge Wilker Mamede de Andrade, Mauricio Gonçales, Roger de Lima Araujo de Melo, Guilherme Alves dos Santos  
**Curso:** Residência Tecnológica em Sistemas Embarcados  
**Instituição:** EmbarcaTech - Instituto Hardware BR  
**Local:** Campinas, Setembro de 2025

## 🎯 Objetivo

Este projeto desenvolve um sistema IoT de baixo custo para monitoramento contínuo da concentração de ozônio em clínicas de ozonioterapia. O sistema visa garantir a segurança de profissionais e pacientes através do controle automatizado dos níveis de O3, implementando alertas visuais, sonoros e ventilação automática quando necessário.

O dispositivo monitora os níveis de ozônio em tempo real, classificando-os em 6 níveis de risco (0,1-100 ppm) conforme normas regulamentadoras, e ativa automaticamente sistemas de segurança quando detectadas concentrações perigosas.

## 🔧 Componentes Usados

### Hardware Principal
- **Microcontrolador:** Raspberry Pi Pico (RP2040)
- **Sensor:** ZE14-O3 (sensor eletroquímico de ozônio com interface UART)
- **Display:** OLED SSD1306 128x64 (interface I2C)
- **Atuadores:**
  - Servo SG90 (controle de abertura/fechamento de saídas de ar)
  - Cooler PWM (ventilação forçada via driver L9110-S)
  - LED RGB (indicação visual por cores)
  - Buzzer MLT-8530 (alertas sonoros diferenciados)

### Software e Ferramentas
- **SDK:** Raspberry Pi Pico SDK 2.1.1
- **Compilador:** ARM GCC Toolchain 14.2
- **Build System:** CMake + Ninja
- **Linguagem:** C11/C++17

## ⚡ Pinagem dos Dispositivos

| Componente | Pino GPIO | Função | Observações |
|------------|-----------|---------|-------------|
| **Sensor ZE14-O3** | | |
| - TX | GPIO 8 | UART1 TX | Comunicação serial |
| - RX | GPIO 9 | UART1 RX | Comunicação serial |
| **Display OLED SSD1306** | | |
| - SDA | GPIO 14 | I2C1 SDA | Interface I2C |
| - SCL | GPIO 15 | I2C1 SCL | Interface I2C |
| **Servo SG90** | GPIO 16 | PWM | Controle de posição |
| **Cooler PWM** | GPIO 4 | PWM | Ventilação (IN1 L9110-S) |
| **LED RGB** | | |
| - Verde | GPIO 11 | Digital Out | Indicação níveis seguros |
| - Azul | GPIO 12 | Digital Out | Indicação sistema ativo |
| - Vermelho | GPIO 13 | Digital Out | Indicação níveis críticos |
| **Buzzer** | GPIO 10 | PWM | Alertas sonoros |
| **LED Onboard** | GPIO 25 | Digital Out | Status do sistema |

## 📈 Resultados Esperados

### Funcionamento Normal
- **Display OLED:** Mostra concentração atual, nível de risco e status do sistema
- **LED RGB:** Indica visualmente o nível de ozônio por cores
- **Monitoramento:** Leituras contínuas a cada segundo via sensor ZE14-O3

### Ativação de Segurança (≥5.0 ppm)
- **Servo:** Abre automaticamente para ventilação
- **Cooler:** Liga em velocidade máxima para circulação de ar
- **LED:** Pisca vermelho indicando nível crítico
- **Buzzer:** Emite alertas sonoros diferenciados por nível

### Desativação Segura (≤0.2 ppm)
- **Servo:** Fecha quando ozônio atinge nível seguro
- **Cooler:** Para ventilação
- **LED:** Retorna à cor verde (nível seguro)
- **Sistema:** Volta ao monitoramento normal

## 📂 Estrutura do Projeto

```

## 🔒 Níveis de Segurança Implementados

| Nível | Concentração | Cor LED | Ação do Sistema | Risco |
|-------|-------------|---------|----------------|-------|
| 0 | < 0.1 ppm | Branco piscante | Monitoramento | Sem detecção |
| 1 | 0.1-1.0 ppm | Verde fixo | Monitoramento | Detectável |
| 2 | 1.0-2.0 ppm | Verde fixo | Monitoramento | Baixo |
| 3 | 2.0-5.0 ppm | Amarelo fixo | Monitoramento | Moderado |
| 4 | 5.0-8.0 ppm | Vermelho piscante | **Servo + Cooler ON** | Alto |
| 5 | 8.0-10.0 ppm | Vermelho fixo | **Servo + Cooler ON** | Crítico |
| 6 | 10.0-100 ppm | Vermelho piscante | **Servo + Cooler ON** | Letal |

## 📜 Licença

Este projeto é licenciado sob GNU General Public License v3.0 (GPL-3.0).
Para mais detalhes, consulte o arquivo [LICENSE](LICENSE) ou visite 
<https://www.gnu.org/licenses/gpl-3.0.html>.

---

**Nota:** Este sistema foi desenvolvido para fins educacionais e de pesquisa no programa EmbarcaTech. Para uso em aplicações médicas reais, consulte profissionais especializados e normas regulamentadoras específicas.