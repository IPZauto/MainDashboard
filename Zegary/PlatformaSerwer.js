  const status = document.getElementById('status');
  const receivedData = document.getElementById('receivedData');

  const socket = new WebSocket('ws://192.168.56.1:8080'); // <- IP serwera

  socket.addEventListener('open', () => {
    status.textContent = 'Połączono z serwerem WebSocket.';
  });

  socket.addEventListener('message', (event) => {
    try {
      const data = JSON.parse(event.data);
      if (data.type === 'formData') {
        receivedData.textContent += `Wybrano: ${data.value}\n`;
      } else {
        receivedData.textContent += `Inna wiadomość: ${event.data}\n`;
      }
    } catch (e) {
      receivedData.textContent += `Tekst: ${event.data}\n`;
    }
  });

  socket.addEventListener('close', () => {
    status.textContent = 'Połączenie zamknięte.';
  });

  socket.addEventListener('error', (err) => {
    status.textContent = 'Błąd połączenia.';
    console.error(err);
  });

