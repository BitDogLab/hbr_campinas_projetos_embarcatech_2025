import serial
import time

PORTA = '/dev/ttyUSB0'   
BAUDRATE = 9600
def main():
    try:
        ser = serial.Serial(PORTA, BAUDRATE, timeout=1)
        time.sleep(2)  
        

        print("Digite 1 para enviar $START")
        print("Digite 2 para enviar $RESET")

        while True:
            user_input = input(">> ")

            if user_input == "1":
                ser.write(b"$START\n")
                print("[Python] Enviado: $START")

                resposta = None
                timeout = time.time() + 5  

                while time.time() < timeout:
                    linha = ser.readline().decode().strip()
                    if linha:  
                        resposta = linha
                        if resposta == "$ACK":
                            print(f"[Arduino] Respondeu: {resposta}")
                            temp = float(input(">> Insira a temperatura:"))
                            umi = float(input(">> Insira a umidade:"))
                            lux = float(input(">> Insira a luminosidade:"))
                            ser.write("$DATA,{},{},{}\n".format(temp, umi, lux).encode())
                            while linha != "$FINISH":
                                linha = ser.readline().decode().strip()
                            print("[Arduino] Calibração Finalizada")
                        else:
                            print(f"[Arduino] Respondeu algo diferente: {resposta}")
                        break  

                if not resposta:
                    print("Nenhuma resposta recebida em 5 segundos.")

            elif user_input == "2":
                ser.write(b"$RESET\n")
                print("[Python] Enviado: $RESET")

                resposta = None
                timeout = time.time() + 5

                while time.time() < timeout:
                    linha = ser.readline().decode().strip()
                    if linha:
                        resposta = linha
                        if resposta == "$ACK":
                            print(f"[Arduino] Respondeu: {resposta}")
                        else:
                            print(f"[Arduino] Respondeu algo diferente: {resposta}")
                        break

                if not resposta:
                    print("Nenhuma resposta recebida em 5 segundos.")

            else:
                print("Entrada inválida. Use 1 ou 2.")
                continue

    except serial.SerialException as e:
        print(f"Erro ao abrir a porta serial: {e}")
    except KeyboardInterrupt:
        print("\nEncerrando comunicação...")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()
