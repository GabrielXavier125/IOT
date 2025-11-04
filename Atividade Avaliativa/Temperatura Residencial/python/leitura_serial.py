import serial
import time

porta = "COM3"   # ajuste conforme a porta do seu Arduino
baud = 9600

try:
    arduino = serial.Serial(porta, baud, timeout=2)
    print(f"Lendo dados da porta {porta}...")
    time.sleep(2)

    while True:
        if arduino.in_waiting > 0:
            linha = arduino.readline().decode('utf-8').strip()
            print("Temperatura:", linha)
            with open("../web/dados.txt", "w") as arquivo:
                arquivo.write(linha)
        time.sleep(0.5)  # Atualiza a cada meio segundo

except serial.SerialException as e:
    print(f"Erro na porta serial: {e}")
except KeyboardInterrupt:
    print("Leitura encerrada.")
