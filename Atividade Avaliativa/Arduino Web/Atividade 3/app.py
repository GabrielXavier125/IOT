from flask import Flask, render_template, jsonify
import serial
import time

# Conexão com o Arduino
try:
    arduino = serial.Serial('COM4', 9600, timeout=1)
    time.sleep(2)
except serial.SerialException as e:
    print(f"Erro ao conectar com Arduino: {e}")
    arduino = None

# Estado atual dos LEDs
led_status = {'1': 'off', '2': 'off', '3': 'off'}

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

# Rota para controlar LEDs
@app.route('/control/<led_num>/<action>')
def control(led_num, action):
    if arduino and led_num in ['1','2','3'] and action in ['on','off']:
        command = ''
        if led_num == '1': command = 'A' if action=='on' else 'a'
        elif led_num == '2': command = 'B' if action=='on' else 'b'
        elif led_num == '3': command = 'C' if action=='on' else 'c'

        try:
            arduino.write(command.encode())
            led_status[led_num] = action
            return jsonify({'success': True, 'led': led_num, 'status': action})
        except:
            return jsonify({'success': False, 'message': 'Erro na comunicação com Arduino'})
    else:
        return jsonify({'success': False, 'message': 'Comando inválido'})

# Rota para obter status atual dos LEDs
@app.route('/status')
def status():
    return jsonify(led_status)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)
