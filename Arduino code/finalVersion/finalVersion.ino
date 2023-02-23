#include <SPI.h> //BIBLIOTECA PARA INTERLIGAR ARDUINO A OUTROS PERIFERICOS COMO A ETHERNET SHIELD
#include <Ethernet.h> //INCLUSÃO DE BIBLIOTECA

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //ATRIBUIÇÃO DE ENDEREÇO MAC AO ETHERNET SHIELD W5100
byte ip[] = { 192, 168, 15, 2 }; 
byte gateway[] = {192, 168, 15, 1}; 
byte subnet[] = {255, 255, 255, 0};
EthernetServer server(80); 

const int ledPin = 9;
String readString = String(30); //VARIÁVEL PARA BUSCAR DADOS NO ENDEREÇO (URL)
int status = 0; 

void setup(){
  Ethernet.begin(mac, ip, gateway, subnet); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE
  server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA 80
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  }
void loop(){
EthernetClient client = server.available(); //CRIA UMA CONEXÃO COM O CLIENTE
  if (client) { // SE EXISTE CLIENTE, FAZ
    while (client.connected()) {//ENQUANTO EXISTIR CLIENTE CONECTADO, FAZ
   if (client.available()) { //SE O CLIENTE ESTÁ HABILITADO, FAZ
    char c = client.read(); //LÊ CARACTERE A CARACTERE DA REQUISIÇÃO HTTP
    if (readString.length() < 100) //SE O ARRAY FOR MENOR QUE 100, FAZ
      {
        readString += c; // "readstring" VAI RECEBER OS CARACTERES LIDO
      }  
        if (c == '\n') { //SE ENCONTRAR "\n" É O FINAL DO CABEÇALHO DA REQUISIÇÃO HTTP
          if (readString.indexOf("?") <0){ //SE ENCONTRAR O CARACTER "?", FAZ
          }
          else //SENÃO,FAZ
        if(readString.indexOf("ledParam=1") >0) //SE ENCONTRAR O PARÂMETRO "ledParam=1", FAZ
           {
             digitalWrite(ledPin, HIGH); //LIGA O LED
             status = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ LIGADO)
           }else{ //SENÃO, FAZ
             digitalWrite(ledPin, LOW); //DESLIGA O LED
             status = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ DESLIGADO)             
           }
          client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
          client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
          client.println("");
          client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
          client.println("<html lang='en'>"); //ABRE A TAG "html"
          client.println("<head>"); //ABRE A TAG "head"
          client.println("<meta charset='utf-8'>");
          client.println("<link rel='icon' type='image/jpg' href='https://st2.depositphotos.com/2274151/7118/v/950/depositphotos_71183821-stock-illustration-workshop-grunge-retro-blue-isolated.jpg'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
          client.println("<title>Workshop - Microcontrolador</title>"); //ESCREVE O TEXTO NA PÁGINA
          client.println("<meta name='theme-color' content='#1976d2'>");
          client.println("</head>"); //FECHA A TAG "head"

          client.println("<header><center><font color='#000080' background-color:'#f0ffff'><h1> LIGHTING IoT PROJECT </br> USING PHOTOVOLTAIC ENERGY</font></center></h1></header>"); //ESCREVE "MASTERWALKER SHOP" EM COR AZUL NA PÁGINA
          client.println("<hr/>");
         
          client.println("<body style=background-color:#f5f5f5>");  
          client.println("<table>");
          client.println("<tr>");
                     
          client.println("<td><img width='1000' height='1000' src='https://www.weg.net/tomadas/blog/wp-content/uploads/2020/07/4.-17_07-4-beneficios-da-automacao-residencial-casas-inteligentes-1-1026x480.jpg'></td>");
          client.println("</tr>");
          
          client.println("<tr>");
         
          client.println("<td>"); 

          client.println("</br>");
          client.println("</br>");
          client.println("</br>");
          client.println("</br>");
          client.println("</br>");
          client.println("</br>");

          client.println("<center><font color='black' size='8'>LIGHT SWITCH</center>");

          client.println("</br>");
          client.println("</br>");
          
          if (status == 1){ 
          client.println("<center><font-size='25'><form method=get name=LED><input type=hidden name=ledParam value=0 /><input type=submit value=TURN_OFF></form></center>");
          }else{ 
          client.println("<center><form method=get name=LED><input type=hidden name=ledParam value=1 /><input type=submit value=TURN_ON></form></center>");
          }

          client.println("</br>");
          client.println("</br>");

          if (status == 1){ 
              client.println("<center><font color='green' size='8'>LAMP ON</center>");
          }else{ //SENÃO, FAZ
              client.println("<center><font color='red' size='8'>LAMP OFF</center></td>");
          }    

          client.println("</tr>");
          client.println("</table>");
          client.println("</br>");
          client.println("</br>");
          client.println("</br>");
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
