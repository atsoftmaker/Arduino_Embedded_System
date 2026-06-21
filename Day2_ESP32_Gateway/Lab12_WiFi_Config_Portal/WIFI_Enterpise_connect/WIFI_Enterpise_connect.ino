#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* ap_ssid = "ESP32_Auto_Detect";

WebServer server(80);
DNSServer dnsServer;

String selected_ssid = "";
String wifi_type = "";
String eap_identity = "";
String eap_password = "";

String global_wifi_options = "";

// ฟังก์ชันสแกนรอบตัว และดึงค่า Encryption Type ออกมาด้วย
void scanNetworksToGlobal() {
  Serial.println("\n[SCAN] กำลังสแกนหาคลื่น Wi-Fi และวิเคราะห์ประเภทความปลอดภัย...");
  global_wifi_options = "";
 
  int n = WiFi.scanNetworks(false, false, false, 150);
  Serial.print("[SCAN] พบทั้งหมด: "); Serial.print(n); Serial.println(" เครือข่าย");

  if (n <= 0) {
    global_wifi_options += "<option value='' data-auth='normal'>-- ไม่พบสัญญาณ Wi-Fi --</option>";
  } else {
    for (int i = 0; i < n; ++i) {
      String ssid_item = WiFi.SSID(i);
      int rssi = WiFi.RSSI(i);
     
      // ดักจับประเภทความปลอดภัย (บนบอร์ด Core เวอร์ชันต่างๆ)
      int auth_type = WiFi.encryptionType(i);
     
      // เช็กว่าเป็นระบบ Enterprise หรือไม่ (ค่ามาตรฐานของ ESP32 Enterprise มักจะเป็นเลข 5 หรือ พารามิเตอร์ WIFI_AUTH_WPA2_ENTERPRISE)
      String mode = "normal";
      if (auth_type == 5 || auth_type == WIFI_AUTH_WPA2_ENTERPRISE) {
        mode = "enterprise";
      }


      if(ssid_item.length() > 0) {
        // ใช้ HTML5 data attribute (data-auth) ฝังประเภทความปลอดภัยไว้ใน Option แต่ละตัว
        global_wifi_options += "<option value='" + ssid_item + "' data-auth='" + mode + "'>"
                            + ssid_item + " [" + mode + "] (" + String(rssi) + " dBm)</option>";
      }
    }
  }
  WiFi.scanDelete();
}


String getHtmlPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8">
  <title>ESP32 Intelligent Wi-Fi Setup</title>
  <style>
    body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background-color: #f4f5f7; color: #333; }
    .card { background: white; padding: 25px; border-radius: 12px; box-shadow: 0 4px 12px rgba(0,0,0,0.1); max-width: 400px; margin: 20px auto; }
    h2 { color: #0066cc; margin-top: 0; text-align: center; font-size: 20px; }
    .form-group { margin-bottom: 15px; }
    label { display: block; margin-bottom: 6px; font-weight: bold; font-size: 14px; }
    input[type="text"], input[type="password"], select { width: 100%; padding: 10px; border: 1px solid #ccc; border-radius: 6px; box-sizing: border-box; font-size: 15px; }
    button { width: 100%; padding: 12px; background-color: #0066cc; border: none; border-radius: 6px; color: white; font-size: 16px; font-weight: bold; cursor: pointer; margin-top: 10px; }
    button:hover { background-color: #0052a3; }
    .btn-scan { background-color: #6c757d; font-size: 13px; padding: 8px; width: auto; margin: 0 0 15px auto; display: block; }
    .hidden { display: none; }
    .badge { background: #e1f0ff; color: #0066cc; padding: 3px 8px; border-radius: 4px; font-size: 12px; display: inline-block; margin-bottom: 10px; }
  </style>
  <script>
    // ฟังก์ชันอัจฉริยะ ตรวจสอบประเภท Wi-Fi อัตโนมัติเมื่อเลือก SSID
    function checkWiFiType() {
      var select = document.getElementById("ssid_select");
      var selectedOption = select.options[select.selectedIndex];
      // ดึงค่าที่เราแอบฝังไว้ใน data-auth ออกมาดู
      var authMode = selectedOption.getAttribute("data-auth");
     
      var entFields = document.getElementById("enterprise_fields");
      var normFields = document.getElementById("normal_fields");
      var typeInput = document.getElementById("wifi_type_hidden");
      var modeBadge = document.getElementById("mode_badge");


      typeInput.value = authMode; // บันทึกค่าลงฟอร์มส่งกลับไปให้ ESP32


      if (authMode === "enterprise") {
        entFields.classList.remove("hidden");
        normFields.classList.add("hidden");
        modeBadge.innerHTML = "ระบบตรวจพบ: 🏢 Wi-Fi องค์กร (WPA2-Enterprise)";
      } else {
        entFields.classList.add("hidden");
        normFields.classList.remove("hidden");
        modeBadge.innerHTML = "ระบบตรวจพบ: 🏠 Wi-Fi บ้านทั่วไป (WPA2-PSK)";
      }
    }
   
    // สั่งให้ทำงานครั้งแรกตอนโหลดหน้าเว็บเสร็จทันที
    window.onload = function() {
      checkWiFiType();
    };
  </script>
</head>
<body>
  <div class="card">
    <h2>📡 Smart Wi-Fi Setup</h2>
   
    <form action="/scan" method="GET">
      <button type="submit" class="btn-scan">🔄 สแกนหาไวไฟใหม่</button>
    </form>
   
    <form action="/save" method="POST">
      <input type="hidden" name="type" id="wifi_type_hidden" value="normal">


      <div class="form-group">
        <label>เลือกเครือข่าย Wi-Fi:</label>
        <select name="ssid" id="ssid_select" onchange="checkWiFiType()" required>
  )rawliteral";
 
  html += global_wifi_options;
 
  html += R"rawliteral(
        </select>
      </div>
     
      <div id="mode_badge" class="badge">กำลังวิเคราะห์เครือข่าย...</div>


      <div id="normal_fields" class="form-group">
        <label>รหัสผ่าน (Password):</label>
        <input type="password" name="password" placeholder="ใส่รหัสผ่าน Wi-Fi">
      </div>


      <div id="enterprise_fields" class="form-group hidden">
        <label>Identity (Username):</label>
        <input type="text" name="identity" placeholder="เช่น sermsukplc\ptops004">
        <label style="margin-top:10px;">Password:</label>
        <input type="password" name="ent_password" placeholder="ใส่รหัสผ่าน Enterprise">
      </div>


      <button type="submit">🚀 บันทึกและเชื่อมต่อทันที</button>
    </form>
  </div>
</body>
</html>
  )rawliteral";


  return html;
}


void handleRoot() {
  server.send(200, "text/html", getHtmlPage());
}


void handleScan() {
  scanNetworksToGlobal();
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}


void handleSave() {
  if (server.hasArg("ssid")) selected_ssid = server.arg("ssid");
  if (server.hasArg("type")) wifi_type = server.arg("type"); // รับค่าประเภทออโต้จากหน้าเว็บ
 
  if (wifi_type == "enterprise") {
    eap_identity = server.arg("identity");
    eap_password = server.arg("ent_password");
  } else {
    eap_password = server.arg("password");
  }


  String response = "<html><head><meta charset='utf-8'></head><body><center><br><br><h2>กำลังบันทึกข้อมูลและเชื่อมต่อ...</h2><p>กรุณาเช็คผลการล็อกอินที่หน้าจอ Serial Monitor</p></center></body></html>";
  server.send(200, "text/html", response);
  delay(2000);
 
  server.stop();
  dnsServer.stop();
 
  connectToWiFi();
}


void connectToWiFi() {
  Serial.println("\n-----------------------------------------");
  Serial.print("Connecting to: "); Serial.println(selected_ssid);
  Serial.print("Detected Type: "); Serial.println(wifi_type);
 
  WiFi.disconnect(true, true);
  delay(1000);
  WiFi.mode(WIFI_STA);


  if (wifi_type == "enterprise") {
    Serial.println("Mode: WPA2-Enterprise (PEAP)");
    Serial.print("Identity: "); Serial.println(eap_identity);
    WiFi.begin(selected_ssid.c_str(), WPA2_AUTH_PEAP, eap_identity.c_str(), eap_identity.c_str(), eap_password.c_str());
  } else {
    Serial.println("Mode: WPA2-PSK (Home)");
    WiFi.begin(selected_ssid.c_str(), eap_password.c_str());
  }


  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    counter++;
    Serial.print(".");
   
    if (counter >= 45) {
      Serial.println("\n[ERROR] ต่อไม่สำเร็จ! กลับไปเปิดโหมด Config...");
      startAP();
      return;
    }
  }


  Serial.println("\n=========================================");
  Serial.println("[SUCCESS] ESP32 Connected Successfully!");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  Serial.println("=========================================");
}


void startAP() {
  scanNetworksToGlobal();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid);
  delay(500);
 
  dnsServer.start(53, "*", WiFi.softAPIP());
 
  server.on("/", handleRoot);
  server.on("/scan", handleScan);
  server.on("/save", HTTP_POST, handleSave);
  server.onNotFound(handleRoot);
 
  server.begin();
  Serial.print("\nHotspot Ready! Connect to SSID: "); Serial.println(ap_ssid);
}


void setup() {
  Serial.begin(115200);
  delay(1000);
  startAP();
}


void loop() {
  if (WiFi.getMode() == WIFI_MODE_AP) {
    dnsServer.processNextRequest();
    server.handleClient();
  }
 
  if (WiFi.getMode() == WIFI_MODE_STA && WiFi.status() != WL_CONNECTED) {
    Serial.println("[WARN] Connection lost! Re-opening Config AP...");
    startAP();
  }
  delay(10);
}
