# ============================================================
# Mock OPS Server สำหรับทดสอบ Lab 14 (จำลอง OPS Server 10.5.15.5)
# AtSoftMaker | Embedded System - Arduino
#
# วิธีใช้:
#   pip install flask
#   sudo python3 mock_ops_server.py      (พอร์ต 80 ต้องสิทธิ์ admin)
#   แก้ OPS_URL/OPS_ALERT ในโค้ด ESP32 ให้ชี้มาที่ IP ของเครื่องนี้
# ============================================================
from flask import Flask, request
from datetime import datetime

app = Flask(__name__)

@app.route('/api/data', methods=['POST'])
def data():
    print(f"[{datetime.now():%H:%M:%S}] DATA :", request.json)
    return {"status": "ok"}, 200

@app.route('/api/alert', methods=['POST'])
def alert():
    print(f"[{datetime.now():%H:%M:%S}] ALERT:", request.json)
    return {"status": "ok"}, 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
