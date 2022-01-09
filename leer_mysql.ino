
/*
 Circuito:
 Pin usados por el escudo ethernet 10, 11, 12, 13
 Tampoco usar el pin 4 ya que es para la parte del lector sd
 */
//-------LIBRERIAS DE LA PLACA ETHERNET-----------------------
#include <SPI.h>
#include <Ethernet.h>
//------------------------------------------------------------
String codigo;        //Aquí se almacena la respuesta del servidor
String nombre;        //Aquí se almacena el nombre que recuperamos de MySQL
boolean fin = false;
//-----------------------------------------------------------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Dirección MAC de nuestro módulo ethernet
char server[] = "192.168.10.8"; //URL DEL SERVIDOR O IP EN CASO DE SER LOCAL  
IPAddress ip(192,168,10,78);// IP QUE OCUPARA LA PLACA
EthernetClient client; //CREAMOS EL CLIENTE
//-----------------------------------------------------------------------------------

void setup() {
  pinMode(7, OUTPUT);    // configura pin 13 como salida
  Serial.begin(9600);//Velocidad del puerto serie
  
  while (!Serial) {
    ; 
  }
   Serial.println("Sistema Listo");//Nos indica que ya estamos en condiciones de enviar un correo

}

void loop() {

  if(nombre == "on"){
    digitalWrite(7, HIGH); // pone en alto el pin 13
  }else{
    digitalWrite(7, LOW); // pone en alto el pin 13
  }

Envio_mail();//Llama a la función Envio_mail     
 
}
//////////////////////////////////
void Envio_mail() {
  
 delay(300);
////////////DHCP Activado////////////////////////////////   
  if (Ethernet.begin(mac) == 0) {
    Serial.println("No se pudo configurar Ethernet mediante DHCP");
    
    Ethernet.begin(mac, ip);
  }
  delay(100);
  Serial.println("conectando espere...");
 
  if (client.connect(server, 80)) {

      Serial.println("connectado :-)");//Si se establece la conexión
      // Make a HTTP request:
      client.println("GET /arduino/led.php?t=1");// Colocar la dirección del archivo que se va a leer en el servidor
      //client.println(valorPulsador);
      client.println("HTTP/1.1");
      client.println("Host: 192.168.10.8");//Dirección del servidor
      client.println();
      delay(500);
      Serial.println("Mail Enviado");
    delay(500);
///-------------------------------------------------------------------------------------
while (client.available()) {
char c = client.read();
codigo += c;
//Habilitamos la comprobación del código recibido
fin = true;
}
//Si está habilitada la comprobación del código entramos en el IF
if (fin)  {
// Serial.println(codigo);
//Analizamos la longitud del código recibido
int longitud = codigo.length();
//Buscamos en que posición del string se encuentra nuestra variable
int posicion = codigo.indexOf("valor=");
//Borramos lo que haya almacenado en el string nombre
nombre = "";
//Analizamos el código obtenido y almacenamos el nombre en el string nombre
for (int i = posicion + 6; i < longitud; i ++){
if (codigo[i] == ';') i = longitud;
else nombre += codigo[i];
}
//Deshabilitamos el análisis del código
fin = false;
//Imprimir el nombre obtenido
Serial.println("Valor de la variable nombre: " + nombre);
delay(2000);
client.stop();
}
//Borrar código y salir de la función//Dirección IP del servidor
codigo="";
    
  }
}
