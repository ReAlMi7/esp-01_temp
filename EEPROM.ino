void loadConfig() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0, cfg);
  EEPROM.end();
  if (String(cfg.CFG) != "configured") { strcpy(cfg.WFAP, "ESP_Config"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.WFAP_PWD, "12345678"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.WFSSID, "WI-FI"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.WF_PWD, "wifipass"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT, "www.wqtt.ru"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_PORT, "14079"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_USER, "mqqt_user"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_PWD, "87654321"); } 
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_TOPIC, "/room/topic"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_TOPIC_NAME, "НАЗВАНИЕ ДАТЧИКА"); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.MQTT_CLIENT_STATUS, (String(cfg.MQTT_TOPIC) + "/status").c_str()); }
  if (String(cfg.CFG) != "configured") { strcpy(cfg.CFG, "configured"); }
  if (String(cfg.CFG) != "configured") {String mac = WiFi.macAddress(); mac.replace(":", ""); mac.toCharArray(cfg.mqttClientID, sizeof(cfg.mqttClientID));}

  /*
  if (strlen(cfg.WFAP) == 0) { strcpy(cfg.WFAP, "ESP_Config"); }
  if (strlen(cfg.WFAP_PWD) == 0) { strcpy(cfg.WFAP_PWD, "12345678"); }
  if (strlen(cfg.WFSSID) == 0) { strcpy(cfg.WFSSID, "WI-FI"); }
  if (strlen(cfg.WF_PWD) == 0) { strcpy(cfg.WFSSID, "wifipass"); }
  if (strlen(cfg.MQTT) == 0) { strcpy(cfg.MQTT, "www.wqtt.ru"); }
  if (strlen(cfg.MQTT_PORT) == 0) { strcpy(cfg.MQTT_PORT, "14079"); }
  if (strlen(cfg.MQTT_USER) == 0) { strcpy(cfg.MQTT_USER, "mqqt_user"); }
  if (strlen(cfg.MQTT_PWD) == 0) { strcpy(cfg.MQTT_PWD, "87654321"); } 
  if (strlen(cfg.MQTT_TOPIC) == 0) { strcpy(cfg.MQTT_TOPIC, "/room/topic"); }
  if (strlen(cfg.MQTT_TOPIC_NAME) == 0) { strcpy(cfg.MQTT_TOPIC_NAME, "ТЕМПЕРАТУРА В КУБЕ"); }
  if (strlen(cfg.MQTT_CLIENT_STATUS) == 0) { strcpy(cfg.MQTT_CLIENT_STATUS, (String(cfg.MQTT_TOPIC) + "/status").c_str()); }
  */
}

void saveConfig() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(0, cfg);
  EEPROM.commit();
  EEPROM.end();
}