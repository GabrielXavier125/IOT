let redState = false;
let greenState = false;

function toggleLED(color, state) {
    if (color === 'red') {
        redState = state;
        const ledRed = document.getElementById('ledRed');
        const redStatus = document.getElementById('redStatus');
        
        if (redState) {
            ledRed.classList.add('active');
            redStatus.textContent = 'LED Vermelho Ligado';
            redStatus.classList.add('text-success');
            redStatus.classList.remove('text-light');
        } else {
            ledRed.classList.remove('active');
            redStatus.textContent = 'LED Vermelho Desligado';
            redStatus.classList.add('text-light');
            redStatus.classList.remove('text-success');
        }
        console.log('LED Vermelho: ' + (redState ? 'Ligado' : 'Desligado'));
    }

    if (color === 'green') {
        greenState = state;
        const ledGreen = document.getElementById('ledGreen');
        const greenStatus = document.getElementById('greenStatus');
        
        if (greenState) {
            ledGreen.classList.add('active');
            greenStatus.textContent = 'LED Verde Ligado';
            greenStatus.classList.add('text-success');
            greenStatus.classList.remove('text-light');
        } else {
            ledGreen.classList.remove('active');
            greenStatus.textContent = 'LED Verde Desligado';
            greenStatus.classList.add('text-light');
            greenStatus.classList.remove('text-success');
        }
        console.log('LED Verde: ' + (greenState ? 'Ligado' : 'Desligado'));
    }
}
