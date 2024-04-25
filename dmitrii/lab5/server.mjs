// Importing modules using ESM syntax
import express from 'express';
import bodyParser from 'body-parser';
import fetch from 'node-fetch';  // Importing fetch directly using ESM

const app = express();
const PORT = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public'));

let sensorData = {};
let connectionCount = 0;

app.post('/notify', async (req, res) => {
    const ip = extractIP(req);
    console.log('Received from IP:', ip);

    await updateGeolocation(ip);

    updateSensorData(req.body);
    connectionCount++;
    console.log('Connection count:', connectionCount);
    res.send('Data received');
});

const extractIP = (req) => {
    return req.headers['x-forwarded-for'] || req.connection.remoteAddress;
};

const updateGeolocation = async (ip) => {
    const geoUrl = `http://ip-api.com/json/${ip}`;
    try {
        const response = await fetch(geoUrl);
        const geoData = await response.json();
        console.log('Geolocation data:', geoData);
        sensorData.geo = geoData;
    } catch (error) {
        console.error('Failed to fetch geolocation data:', error);
    }
};

const updateSensorData = (data) => {
    console.log('Received body:', data);
    sensorData.lastUpdate = data;
    console.log('Sensor Data Updated:', sensorData.lastUpdate);
};

app.get('/events', (req, res) => {
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');

    const intervalId = setInterval(() => {
        const data = {
            ...sensorData,
            connectionCount
        };
        res.write(`data: ${JSON.stringify(data)}\n\n`);
    }, 1000);

    req.on('close', () => {
        clearInterval(intervalId);
        res.end();
    });
});

app.get('/data', (req, res) => {
    res.json(sensorData);
});

app.listen(PORT, () => {
    console.log(`Server listening on http://localhost:${PORT}`);
});
