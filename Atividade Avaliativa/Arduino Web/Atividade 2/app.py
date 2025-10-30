from flask import Flask, render_template, jsonify
import serial
import time
import re
import threading

app = Flask(__name__)

# Configuração da porta serial
try:
    arduino = serial.Serial('COM3', 9600, timeout=1)
    time.sleep(2)
    print("✅ Arduino conectado na porta COM3")
except Exception as e:
    print(f"❌ Erro ao conectar com Arduino: {e}")
    arduino = None

# Dados compartilhados
dados_sensor = {'temperatura': '--', 'umidade': '--'}
ultima_leitura = ''

# Thread para ler dados do sensor continuamente
def ler_dados_sensor():
    global dados_sensor, ultima_leitura
    
    while True:
        if arduino and arduino.in_waiting > 0:
            try:
                linha = arduino.readline().decode().strip()
                ultima_leitura = linha
                print(f"Dados recebidos: {linha}")
                
                # Verifica se é dado do sensor DHT (T: e U:)
                if 'T:' in linha and 'U:' in linha:
                    temp_match = re.search(r'T:([\d.]+)', linha)
                    umid_match = re.search(r'U:([\d.]+)', linha)
                    
                    if temp_match and umid_match:
                        dados_sensor['temperatura'] = float(temp_match.group(1))
                        dados_sensor['umidade'] = float(umid_match.group(1))
                        print(f"✅ Sensor: {dados_sensor['temperatura']}°C, {dados_sensor['umidade']}%")
                
            except Exception as e:
                print(f"Erro na leitura serial: {e}")
        
        time.sleep(2)

# Inicia a thread de leitura
if arduino:
    thread_sensor = threading.Thread(target=ler_dados_sensor, daemon=True)
    thread_sensor.start()

# Rotas Flask
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_data')
def get_data():
    """Retorna os dados do sensor para a página web"""
    return jsonify(dados_sensor)

@app.route('/controlar/<led_num>/<action>')
def controlar_led(led_num, action):
    """Controla os LEDs via Arduino"""
    if arduino:
        command = ''
        if led_num == '1':
            command = 'A' if action == 'on' else 'a'
        elif led_num == '2':
            command = 'B' if action == 'on' else 'b'
        elif led_num == '3':
            command = 'C' if action == 'on' else 'c'

        if command:
            try:
                arduino.write(command.encode())
                print(f"✅ Comando '{command}' enviado para LED {led_num}")
                return f"Comando '{command}' enviado para LED {led_num}"
            except Exception as e:
                return f"Erro ao enviar comando: {e}"
        else:
            return "Comando inválido"
    else:
        return "Arduino não conectado"

@app.route('/status')
def status():
    """Retorna o status do sistema"""
    return jsonify({
        'arduino_conectado': arduino is not None,
        'ultima_leitura': ultima_leitura,
        'dados_sensor': dados_sensor
    })

if __name__ == '__main__':
    print("🚀 Sistema IoT Iniciado!")
    print("📊 Acesse: http://localhost:5000")
    print("📡 Aguardando dados do sensor...")
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)