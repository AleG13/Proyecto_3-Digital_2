#define A 23
#define B 22
#define C 21
#define D 19
#define E 18
#define F 5
#define G 4
#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

//Variables y Constantes para el display
const int segmentPins[] = {A, B, C, D, E, F, G};
int number = 0;
int intNum = 0;
int intNum1 = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
int p6 = 0;
int p7 = 0;
int p8 = 0;

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

int parqueos = 0;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Iniciar comunicación serial para ver en la terminal
  Serial2.begin(115200); //Habilitar el UART1 y cambiar los pins

  //Pines del Display
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);



  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  
}

void displayNumber(int number) {
  // Define el patrón de segmentos para cada número del 0 al 9
  const byte digitPatterns[] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111};   // 9
  if (number >= 0 && number <= 9) {
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], bitRead(digitPatterns[number], i));
    }
  }
}

void loop() {
    if (Serial2.available()) {
        intNum = Serial2.read(); // Lee los datos hasta encontrar un salto de línea
        Serial.println(intNum); // Imprime el valor entero obtenido desde los datos recibidos por el puerto seria
    }
    if (Serial.available()) {
        intNum1 = Serial.read(); // Lee los datos hasta encontrar un salto de línea
        Serial.println(intNum1); // Imprime el valor entero obtenido desde los datos recibidos por el puerto seria
    }
    
    if(intNum & 0b00000001){
      p5 = 1;}
    else{p5 = 0;}

    if(intNum & 0b00000010){
      p6 = 1;}
    else{p6 = 0;}

    if(intNum & 0b00000100){
      p7 = 1;}
    else{p7 = 0;}

    if(intNum & 0b00001000){
      p8 = 1;}
    else{p8 = 0;}

    if(intNum1 & 0b00000001){
      p1 = 1;}
    else{p1 = 0;}

    if(intNum1 & 0b00000010){
      p2 = 1;}
    else{p2 = 0;}

    if(intNum1 & 0b00000100){
      p3 = 1;}
    else{p3 = 0;}

    if(intNum1 & 0b00001000){
      p4 = 1;}
    else{p4 = 0;}

    parqueos= p1+p2+p3+p4+p5+p6+p7+p8;

    displayNumber(parqueos);
    //Programa de HTML
    server.handleClient();
    handle_OnConnect();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){

  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<html>\n";
  ptr += "<head>\n";
  ptr += "<meta name=viewport content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<link rel=stylesheet href=https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css integrity=sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk crossorigin=anonymous>\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center}body{margin-top:50px}h1{color:#add8e6;margin:50px auto 30px}h3{color:#d3d3d3;margin-bottom:50px}.button{display:block;width:40px;background-color:#191970;border:0;color:white;padding:10px 520px;text-decoration:none;font-size:25px;margin:0 auto 35px;cursor:pointer;border-radius:4px}.button-on{background-color:#ff4500}.button-on:active{background-color:#f00}.button-off{background-color:#f00}.button-off:active{background-color:#ff4500}p{font-size:14px;color:#888;margin-bottom:10px}</style>\n";
  ptr += "<script>function autoRefresh(){window.location=window.location.href}setInterval(autoRefresh,1000);</script>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1 style=\"border:2px solid Tomato\"> ------------------------ &#128664 Estado Parqueomatic &#128664 ------------------------ </h1>\n";
  ptr += "<br>\n";
  /*
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<img src=img_car.jpg alt=Bienvenido width=100 height=100>\n";
  ptr += "<a class=\"button button-off\" href=led1off>Actualizar</a>\n";*/
  ptr += "<progress value=50 max=100></progress>\n";
  ptr += "<br>\n";
  ptr += "<table class=table>\n";
  ptr += "<thead class=table-primary>\n";
  ptr += "<tr>\n";
  ptr += "<th scope=col>&#128129 # Parqueo &#128129</th>\n";
  ptr += "<th scope=col>&#128678 Disponibilidad &#128678</th>\n";
  ptr += "</tr>\n";
  ptr += "</thead>\n";
  ptr += "<tbody>\n";
  if(p1 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---1---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---1---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";
  if(p2 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---2---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---2---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";
  
  if(p3 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---3---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
   ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---3---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";

  if(p4 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---4---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---4---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";

  if(p5 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---5---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---5---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";

  if(p6 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---6---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---6---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";
 
  if(p7 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---7---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---7---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";

  if(p8 == 1){
  ptr += "<tr class=table-danger>\n";
  ptr += "<th scope=row>---8---</th>\n";
  ptr += "<td>Ocupado &#9940</td>\n";
  }
  else{
  ptr += "<tr class=table-info>\n";
  ptr += "<th scope=row>---8---</th>\n";
  ptr += "<td>Disponible &#128588</td>\n";}

  ptr += "</tr>\n";
  ptr += "</tbody>\n";
  ptr += "</table>\n";
  ptr += "<script src=https://code.jquery.com/jquery-3.5.1.slim.min.js integrity=sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj crossorigin=anonymous></script>\n";
  ptr += "<script src=https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js integrity=sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo crossorigin=anonymous></script>\n";
  ptr += "<script src=https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js integrity=sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI crossorigin=anonymous></script>\n";
  ptr += "</body>\n";
  ptr += "</html>";
  return ptr;
}


