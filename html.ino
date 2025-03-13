void handleRoot() {
  String mac = WiFi.macAddress();
  mac.replace(":", ""); // Убираем двоеточия для удобства
  String html = R"rawliteral(
  <!DOCTYPE html> 
    <html lang="ru">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Конфигурация датчика</title>
      <style>
         html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
         body {margin-top: 50px;} 
         h1 {color: #444444; margin: 50px auto 30px;} 
         h3 {color: #444444; margin-bottom: 50px;}
        .button { display: block; width: 80px; background-color: #3498db; border: none; color: white; padding: 13px 30px; text-decoration: none; font-size: 25px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; }
        {font-size: 14px;color: #888;margin-bottom: 10px;}
          input[type="text"], 
          input[type="password"] {
                 height: 14px; 
                 text-align: center;
                 padding: 5px 10px; 
                 font-size: 14px;
                 line-height: normal;
             }
        .password-container {
                  display: flex;
                  position: relative;
                  display: inline-block;
                  gap: 5px;
             }
        .toggle-password {
                   position: absolute;
                    right: 10px;
                    background: none;
                    border: none;
                    cursor: pointer;
                    width: 25px;
                    height: 37px;
             }
         .password-container input { flex: 1; padding: 8px; font-size: 14px; }
         .toggle-password svg { width: 20px; height: 20px; fill: #333; }
          svg { width: 20px; height: 20px; fill: #555; }
      </style>
    </head>
  <body>
  <form action="/save" method="POST">
  <h1>Датчик температуры ESP-01</h1>
  <h3>Режим точки доступа WiFi (AP)<br>Конфигурирование сетевых настроек датчика</h3>
  <h4>WI-FI AP ДАТЧИКА<br>(название точки доступа, создаваемой датчиком в режиме конфигурирования)<br><input type="text" name="apssid" value= ")rawliteral" + String(cfg.WFAP) + R"rawliteral("></h4>
  <h4>ПАРОЛЬ К WI-FI AP ДАТЧИКА<br>(пароль к точке доступа, создаваемой датчиком в режиме конфигурирования)<br>
    <div class="password-container">
     <input type="password" id="password1" name="appass" value= ")rawliteral" + String(cfg.WFAP_PWD) + R"rawliteral(">
     <button type="button" class="toggle-password" onclick="togglePassword(this)">
                                <svg class="eye-open" viewBox="0 0 24 24">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5z"/><path d="M4.22 4.22a1 1 0 00-1.42 1.42l15.56 15.56a1 1 0 001.42-1.42L4.22 4.22z"/>
        </svg>
          <svg class="eye-closed" viewBox="0 0 24 24" style="display: none;">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8a3 3 0 100 6 3 3 0 000-6z"/>
        </svg>
      </button>
      </div></h5>  
  <h4>WI-FI<br>(точка доступа для выхода датчика в Интернет)<br><input type="text" name="ssid" value=")rawliteral" + String(cfg.WFSSID) + R"rawliteral("><br></h4>
  <h4>ПАРОЛЬ К WI-FI<br>(пароль точки доступа для выхода датчика в Интернет)<br>
   <div class="password-container">
   <input type="password" id="password2" name="pass" value= ")rawliteral" + String(cfg.WF_PWD) + R"rawliteral(">
   <button type="button" class="toggle-password" onclick="togglePassword(this)">
            <svg class="eye-open" viewBox="0 0 24 24">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5z"/><path d="M4.22 4.22a1 1 0 00-1.42 1.42l15.56 15.56a1 1 0 001.42-1.42L4.22 4.22z"/>
        </svg>
        <svg class="eye-closed" viewBox="0 0 24 24" style="display: none;">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8a3 3 0 100 6 3 3 0 000-6z"/>
        </svg>
      </button>
      </div></h4>
  <h4>MQTT БРОКЕР<br>(адрес брокера для подключения к нему датчика)<br><input type="text" name="mqtt" value=")rawliteral" + String(cfg.MQTT) + R"rawliteral("><br></h4>
  <h4>MQTT ПОРТ<br>(порт брокера (не TLS) для подключения к нему датчика)<br><input type="text" name="mqtt_port" value=")rawliteral" + String(cfg.MQTT_PORT) + R"rawliteral("><br></h4>
  <h4>ЛОГИН MQTT<br>(логин для подключения датчика к брокеру)<br><input type="text" name="mqtt_user" value=")rawliteral" + String(cfg.MQTT_USER) + R"rawliteral("><br></h4>
  <h4>ПАРОЛЬ MQTT<br>(пароль для подключения датчика к брокеру)<br>
  <div class="password-container">
  <input type="password" id="password3" name="mqtt_pwd" value= ")rawliteral" + String(cfg.MQTT_PWD) + R"rawliteral(">
  <button type="button" class="toggle-password" onclick="togglePassword(this)">
                                <svg class="eye-open" viewBox="0 0 24 24">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5z"/><path d="M4.22 4.22a1 1 0 00-1.42 1.42l15.56 15.56a1 1 0 001.42-1.42L4.22 4.22z"/>
        </svg>
        <svg class="eye-closed" viewBox="0 0 24 24" style="display: none;">
            <path d="M12 4.5C7 4.5 2.7 7.61 1 12c1.7 4.39 6 7.5 11 7.5s9.3-3.11 11-7.5c-1.7-4.39-6-7.5-11-7.5zm0 12c-2.76 0-5-2.24-5-5s2.24-5 5-5 5 2.24 5 5-2.24 5-5 5zm0-8a3 3 0 100 6 3 3 0 000-6z"/>
        </svg>
      </button>
      </div></h4>
  <h4>ТОПИК MQTT<br>(топик брокера, куда датчик будет публиковать свои данные)<br><input type="text" name="topic" value=")rawliteral" + String(cfg.MQTT_TOPIC) + R"rawliteral("><br></h4>
  <h4>НАЗВАНИЕ ТОПИКА MQTT<br>(название параметра измеряемого датчиком для отображения на дисплее датчика)<br><input type="text" name="topic_name" value=")rawliteral" + String(cfg.MQTT_TOPIC_NAME) + R"rawliteral("><br></h4>
  <h4>MQTT Client ID<br>(инеднтификатор mqtt клиента)<br><input type="text" name="mqttID" value=")rawliteral" + mac + R"rawliteral("><br></h4>
  <button type="submit">Сохранить</button>
  </form>
 <script>
  function togglePassword(button) {
    var passwordInput = button.previousElementSibling;
    var eyeOpen = button.querySelector(".eye-open");
    var eyeClosed = button.querySelector(".eye-closed");
    if (passwordInput.type === "password") {
        passwordInput.type = "text";
        eyeOpen.style.display = "none";
        eyeClosed.style.display = "inline";
    } else {
        passwordInput.type = "password";
        eyeOpen.style.display = "inline";
        eyeClosed.style.display = "none";
      }
 }
</script>

  </body>
  </html>)rawliteral";
  server.send(200, "text/html", html);
}

void handleSave() {
  strcpy(cfg.WFAP, server.arg("apssid").c_str());
  strcpy(cfg.WFAP_PWD, server.arg("appass").c_str());
  strcpy(cfg.WFSSID, server.arg("ssid").c_str());
  strcpy(cfg.WF_PWD, server.arg("pass").c_str());
  strcpy(cfg.MQTT, server.arg("mqtt").c_str());
  strcpy(cfg.MQTT_PORT, server.arg("mqtt_port").c_str());
  strcpy(cfg.MQTT_USER, server.arg("mqtt_user").c_str());
  strcpy(cfg.MQTT_PWD, server.arg("mqtt_pwd").c_str());
  strcpy(cfg.MQTT_TOPIC, server.arg("topic").c_str());
  strcpy(cfg.MQTT_TOPIC_NAME, server.arg("topic_name").c_str());
  //strcpy(cfg.MQTT_CLIENT_STATUS, server.arg("status_topic").c_str());
  strcpy(cfg.MQTT_CLIENT_STATUS, (String(cfg.MQTT_TOPIC) + "_status").c_str());
  strcpy(cfg.mqttClientID, server.arg("mqttID").c_str());
  saveConfig();
  String html = R"rawliteral(
  <!DOCTYPE html> 
    <html lang="ru">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <meta http-equiv="Content-type" content="text/html charset=utf-8">
      <title>Конфигурация датчика</title>
      <style>
         html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
         body {margin-top: 50px;} 
         h3 {color: #444444; margin-bottom: 50px;}
      </style>
    </head>
  <body>
 
  <h3>НАСТРОЙКИ СОХРАНЕНЫ!<br>отключите датчик от питания, установите перемычку выбора режима<br>и снова подключите питание к датчику<br>для перевода его в режим работы датчиком</h3>
  <p>WI-FI AP ДАТЧИКА:  )rawliteral" + String(cfg.WFAP) + R"rawliteral(</p>
  <p>WI-FI точки доступа: )rawliteral" + String(cfg.WFSSID) + R"rawliteral(</p>
  <p>MQTT брокер: )rawliteral" + String(cfg.MQTT) + R"rawliteral(</p>
  <p>MQTT юзер: )rawliteral" + String(cfg.MQTT_USER) + R"rawliteral(</p>
  <p>MQTT топик: )rawliteral" + String(cfg.MQTT_TOPIC) + R"rawliteral(</p>
  <p>Название: )rawliteral" + String(cfg.MQTT_TOPIC_NAME) + R"rawliteral(</p>
  <p>MQTT топик статуса: )rawliteral" + String(cfg.MQTT_CLIENT_STATUS) + R"rawliteral(</p>
  <p>MQTT Client ID: )rawliteral" + String(cfg.mqttClientID) + R"rawliteral(</p>
  </body>
  </html>)rawliteral";
  server.send(200, "text/html", html);
}

