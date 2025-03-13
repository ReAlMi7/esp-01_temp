void drawScreen(String sysTray){
  uint8_t fontSize = 1;
  oled.clear();
  oled.setScale(fontSize);
  oled.setCursorXY(strStartPos(fontSize, sysTray), 0);
  oled.print(sysTray);
  fontSize = 3;
  String TXT;
  TXT = String(temp);
  oled.setCursorXY(strStartPos(fontSize, TXT), 30);
  oled.setScale(fontSize);
  oled.print(TXT);
  oled.update();
  delay(1000);
} 

void drawSetupScreen(String sysTray){
  uint8_t fontSize = 1;
  String TXT;
  TXT = sysTray;
  oled.clear();
  oled.setScale(fontSize);
  oled.setCursorXY(strStartPos(fontSize, TXT), 0);
  oled.print(sysTray);
  TXT = "Подключитесь к WI-FI";
  oled.setCursorXY(strStartPos(fontSize, TXT), 16);
  oled.print(TXT);
  TXT = String (cfg.WFAP);
  oled.setCursorXY(strStartPos(fontSize, TXT), 29);
  oled.print(TXT);
  TXT = "Откройте в браузере";
  oled.setCursorXY(strStartPos(fontSize, TXT), 41);
  oled.print(TXT);
  TXT = /*String (cfg.WFAP_PWD);//*/"http://" +  WiFi.softAPIP().toString();
  oled.setCursorXY(strStartPos(fontSize, TXT), 55);
  oled.print(TXT);
  oled.update();
  delay(1000);
}