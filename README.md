# 💧 Water Quality Monitor

Check if water is safe to drink based on pH, turbidity, and temperature.

## Files
```
water-quality/
├── app.py                     ← Flask backend
├── requirements.txt
├── templates/
│   └── index.html             ← Frontend (HTML + CSS)
└── hardware/
    └── water_sensor.ino       ← Arduino code (ESP32)
```

## Run the Web App
```bash
pip install -r requirements.txt
python app.py
```
Then open http://localhost:5000 and type in your sensor values.

## Hardware (ESP32)
Sensors used:
- pH sensor → analog pin 36
- Turbidity sensor → analog pin 39
- DS18B20 temperature sensor → pin 4

The Arduino code prints readings to the Serial Monitor every 3 seconds.

## Safe Ranges
| Parameter   | Safe Range     |
|-------------|----------------|
| pH          | 6.5 – 8.5      |
| Turbidity   | < 1 NTU        |
| Temperature | 0°C – 35°C     |
