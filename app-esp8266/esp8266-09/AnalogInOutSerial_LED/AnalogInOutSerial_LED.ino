#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Sala 37"
#define STAPSK  ""
#endif

//sensor luz
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;
//fim sensor luz

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = LED_BUILTIN;
String postForms;

float lux=-1;

bool automatico=false;

void handleRoot() {
   
   postForms = "<html>\
  <head>\
    <title>LUZ!!</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\
    </style>\
  </head>\
  <body>\
    <h1>Luz da Sala</h1><br>\
    <div>";
    postForms += lux;
    postForms +="</div>\
    <h1>Controlo de Luminária</h1><br>\
    <form method=\"post\" enctype=\"text/plain\" action=\"/desliga/\">\
      <input type=\"submit\" value=\"Desliga\">\
    </form>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/liga/\">\
      <input type=\"submit\" value=\"Liga\">\
   </form>\
   <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/automatico/\">";
    
    if(automatico)
    {
      postForms += "<input type=\"submit\" value=\"Desliga Automático\">";
    }
    else
    {
      postForms += "<input type=\"submit\" value=\"Liga Automático\">";
    }

      
    postForms +="</form>\
  </body>\
</html>";
  server.send(200, "text/html", postForms);
  Serial.println("2");
}


void trataautomatico()
{
    automatico=!automatico;
    server.send(200, "text/html", "Alterou modo automático\n <script> setTimeout(function () { window.location.href = '/'; }, 2000);</script>"  );
   Serial.println("Automatico");
   Serial.println(automatico);
}
void liga()
{
  automatico=false;
   digitalWrite(led, HIGH);
   server.send(200, "text/html", "Ligou a luz\n <script> setTimeout(function () { window.location.href = '/'; }, 2000);</script>"  );
   Serial.println("Ligou");
}

void desliga()
{
  automatico=false;
  digitalWrite(led, LOW);
   server.send(200, "text/html", "Desligou a luz\n <script> setTimeout(function () { window.location.href = '/'; }, 2000);</script>"  );
   Serial.println("Desligou");
}


void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
  Serial.println("1");
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  //sensor luz
  Wire.begin();
  lightMeter.begin();
  //fim sersor luz

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/liga/", liga);

  server.on("/desliga/", desliga);
  
  server.on("/automatico/", trataautomatico);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  //server.close();
}

void loop(void) {
  server.handleClient();

  lux = lightMeter.readLightLevel();

  if(lux<100 && automatico)
  {
    digitalWrite(led, LOW);//Liga
  }else if(automatico)
  {
    digitalWrite(led, HIGH);
  }
  
}
