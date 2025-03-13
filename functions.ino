void getTemperature(){
  sensor.requestTemperatures();
  temp = sensor.getTempCByIndex(0);
}

int strStartPos (int fontS, String TXT){
    int textLength = utf8_strlen(TXT);
    int textWidth = textLength * (fontS * 6);  
    int dx = (SCREEN_WIDTH - textWidth) / 2;
  return dx;
}

int utf8_strlen(const String &str) {
    int len = 0;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] & 0xC0) != 0x80) len++;  // Считаем только первые байты символов UTF-8
    }
    return len;
}
