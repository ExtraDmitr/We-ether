const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const PORT = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public')); // Serve static files from the 'public' directory

let sensorData = {}; // Store sensor data globally
let connectionCount = 0; // Initialize connection count to track POST requests

app.post('/notify', (req, res) => {
    console.log('Received:', req.body);
    sensorData = req.body; // Update the global sensor data
    connectionCount++; // Increment connection count
    console.log('Connection count:', connectionCount); // Log the updated connection count
    res.send('Data received');
});

// SSE Setup to send sensor data and connection count to the client
app.get('/events', (req, res) => {
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');

    const sendData = () => {
        const data = {
            ...sensorData,
            connectionCount
        };
        res.write(`data: ${JSON.stringify(data)}\n\n`);
    };

    const intervalId = setInterval(sendData, 1000); // Send data every second

    req.on('close', () => {
        clearInterval(intervalId);
        res.end();
    });
});

app.listen(PORT, () => {
    console.log(`Server listening on http://localhost:${PORT}`);
});
