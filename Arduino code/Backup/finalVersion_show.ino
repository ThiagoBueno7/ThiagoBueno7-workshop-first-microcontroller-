#include <SPI.h> 
#include <Ethernet.h> 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 15, 2 }; 
byte gateway[] = {192, 168, 15, 1}; 
byte subnet[] = {255, 255, 255, 0};
EthernetServer server(80); 

const int ledPin = 9;
String readString = String(30);
int status = 0; 

void setup(){
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  }
void loop(){
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
   if (client.available()) {
    char c = client.read();
    if (readString.length() < 100)
      {
        readString += c; 
      }  
        if (c == '\n') {
          if (readString.indexOf("?") <0){
          }
          else
        if(readString.indexOf("ledParam=1") >0)
           {
             digitalWrite(ledPin, HIGH); 
             status = 1;
           }else{
             digitalWrite(ledPin, LOW);
             status = 0;             
           }
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("<!DOCTYPE HTML>"); 
          client.println("<html lang='en'>");
          client.println("<head>"); 
          client.println("<meta charset='utf-8'>");
          client.println("<link rel='icon' type='image/jpg' href='https://st2.depositphotos.com/2274151/7118/v/950/depositphotos_71183821-stock-illustration-workshop-grunge-retro-blue-isolated.jpg'/>");
          client.println("<title>Workshop - Microcontrolador</title>");
          client.println("<meta name='theme-color' content='#1976d2'>");
          client.println("</head>");

          client.println("<header><center><font color='#000080' background-color:'#f0ffff'><h1> LIGHTING IoT PROJECT </br> USING PHOTOVOLTAIC ENERGY</font></center></h1></header>");
          client.println("<hr/>");
         
          client.println("<body style=background-color:#f5f5f5>");  
          client.println("<table>");
          client.println("<tr>");
                     
          client.println("<td><img width='1000' height='1000' src='https://www.weg.net/tomadas/blog/wp-content/uploads/2020/07/4.-17_07-4-beneficios-da-automacao-residencial-casas-inteligentes-1-1026x480.jpg'></td>");
          client.println("</tr>");
          
          client.println("<tr>");
      
          client.println("<td>"); 

          client.println("<center><font color='black' size='8'>LIGHT SWITCH</center>");
          
          if (status == 1){ 
          client.println("<center><font-size='25'><form method=get name=LED><input type=hidden name=ledParam value=0 /><input type=submit value=TURN_OFF></form></center>");
          }else{ 
          client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=1 /><input type=submit value=TURN_ON></form></center>");
          }
          
          if (status == 1){ 
              client.println("<center><font color='green' size='8'>LAMP ON</center>");
          }else{ //SENÃO, FAZ
              client.println("<center><font color='red' size='8'>LAMP OFF</center></td>");
          }    

          client.println("</tr>");
          client.println("</table>");
          client.println("</br>");
          client.println("</body>"); 
          
          client.println("<hr/>");
          
          client.println("<footer><h4 style=color:#000000 background-color:#A9A9A9><center>©2022 Lenovo - Microcontrollers Workshop.</center></h4>"); 
          client.println("<h4 style=color:#000000><center>All rights reserved to the developer Thiago Bueno de Oliveira</center></h4></footer>"); 
          client.println("<hr/>"); //
          
          
          client.println("</html>"); 
          readString=""; 
          client.stop();
            }
          }
        }
      }
 }
