from flask import Flask, jsonify, render_template
import paho.mqtt.client as paho
from paho import mqtt
import json

app = Flask(__name__)

# Trang chủ của ứng dụng web
@app.route('/')
def index():
    return render_template('index.html')

# API trả về dữ liệu nhiệt độ và độ ẩm mới nhất
@app.route('/api/data')
def get_data():
    # Gửi yêu cầu lấy dữ liệu mới nhất tới MQTT broker
    client.publish("temperature_humidity/get_data", "get_data")
    print(temperature1, humidity1, temperature2, humidity2, sep=' - ')
    # Trả về dữ liệu dưới dạng JSON
    return jsonify({'temperature1': temperature1, 'humidity1': humidity1 , 'temperature2': temperature2, 'humidity2': humidity2})

# Hàm xử lý khi nhận được dữ liệu từ MQTT broker
def on_message(client, userdata, message):
    global temperature1, humidity1, temperature2, humidity2
    print("Received message: ", str(message.payload.decode("utf-8")))
    # Lấy dữ liệu từ message payload
    data = json.loads(str(message.payload.decode("utf-8")))
    print(type(data["node"]))
    if data["node"] == 1:
        temperature1 = data["temp"]
        humidity1 = data["humidity"]
    elif data["node"] == 2:
        temperature2 = data["temp"]
        humidity2 = data["humidity"]

# Kết nối tới MQTT broker
broker_address = "410e88d4c6f74067af21eb2712fbc8a4.s2.eu.hivemq.cloud"
# broker_address = "broker.hivemq.com"
client = paho.Client(client_id="webhost", userdata=None, protocol=paho.MQTTv5)
client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)
client.on_message = on_message # Thiết lập callback function cho MQTT client
client.username_pw_set("webserver", "47yX37^4")
client.connect(broker_address, port = 8883)

# Khởi tạo temperature và humidity

temperature1 = 0
humidity1 = 0

temperature2 = 0
humidity2 = 0

client.subscribe("temperature_humidity/data")

if __name__ == '__main__':
    # Start MQTT client
    client.loop_start()
    # Start Flask app
    app.run()