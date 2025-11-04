function atualizarTemperatura() {
  fetch("read.php?t=" + new Date().getTime()) // evita cache
    .then(response => response.text())
    .then(temp => {
      const tempSpan = document.getElementById("temp");
      const statusSpan = document.getElementById("status");
      const valor = parseFloat(temp);

      if (!isNaN(valor)) {
        tempSpan.textContent = valor.toFixed(1);

        if (valor > 30) {
          statusSpan.textContent = "🔥 Quente (ventilador ligado)";
          statusSpan.style.color = "red";
        } else {
          statusSpan.textContent = "❄️ Normal (ventilador desligado)";
          statusSpan.style.color = "green";
        }
      } else {
        tempSpan.textContent = "--";
        statusSpan.textContent = "Erro ao ler temperatura";
        statusSpan.style.color = "gray";
      }
    })
    .catch(error => {
      console.error("Erro ao atualizar:", error);
      document.getElementById("status").textContent = "⚠️ Erro de conexão";
    });
}

// Atualiza a cada meio segundo
setInterval(atualizarTemperatura, 500);
atualizarTemperatura();
