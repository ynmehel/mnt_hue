
void setBrightness(int lightNum, int brightness) {

  Serial.println("Setting brightness " + String(brightness));
  sendCommand(lightNum, "{\"bri\":" + String(brightness) + "}");
}

void setGroupBrightness(int brightness) {

  Serial.println("Setting group brightness " + String(brightness));
  sendGroupCommand("{\"bri\":" + String(brightness) + "}");
}

void turnOnOffGroup (bool isOn) {
  
  if (isOn) {

    Serial.println("Turning on group");
    sendGroupCommand("{\"on\": true}");
  }
  else {

    Serial.println("Turning off group ");
    sendGroupCommand("{\"on\": false}");
  }
}

void turnOnOffLamp(int lightNum, bool isOn) {

  if (isOn) {

    Serial.println("Turning on");
    sendCommand(lightNum, "{\"on\": true}");
  }
  else {

    Serial.println("Turning off");
    sendCommand(lightNum, "{\"on\": false}");
  }
}

void setRandomColorOnGroup() {

  String x = String(random(10, 80) / 100.0);
  String y = String(random(10, 80) / 100.0);
  String randomColorCommand = "{\"xy\":[ " + x + "," + y + "]}";

  sendGroupCommand(randomColorCommand );
  Serial.println("Sending random color to group: " + randomColorCommand);

}

void setRandomColorOnLamp(int lightNum) {

  String x = String(random(10, 80) / 100.0);
  String y = String(random(10, 80) / 100.0);
  String randomColorCommand = "{\"xy\":[ " + x + "," + y + "]}";

  sendCommand(lightNum, randomColorCommand );
  Serial.println("Sending random color: " + randomColorCommand);

}

boolean sendCommand(int lightNum, String command)
{
  if (client.connect(hueHubIP, hueHubPort))
  {
    while (client.connected())
    {
      client.print("PUT /api/");
      client.print(hueUsername);
      client.print("/lights/");
      client.print(lightNum);  // hueLight zero based, add 1
      client.println("/state HTTP/1.1");
      client.println("keep-alive");
      client.print("Host: ");
      client.println(hueHubIP);
      client.print("Content-Length: ");
      client.println(command.length());
      client.println("Content-Type: text/plain;charset=UTF-8");
      client.println();  // blank line before body
      client.println(command);  // Hue command
    }
    client.stop();
    return true;  // command executed
  }
  else
    return false;  // command failed
}


boolean sendGroupCommand(String command)
{
  if (client.connect(hueHubIP, hueHubPort))
  {
    while (client.connected())
    {
      client.print("PUT /api/");
      client.print(hueUsername);
      client.print("/groups/0");
      client.println("/action HTTP/1.1");
      client.println("keep-alive");
      client.print("Host: ");
      client.println(hueHubIP);
      client.print("Content-Length: ");
      client.println(command.length());
      client.println("Content-Type: text/plain;charset=UTF-8");
      client.println();  // blank line before body
      client.println(command);  // Hue command
    }
    client.stop();
    return true;  // command executed
  }
  else
    return false;  // command failed
}
