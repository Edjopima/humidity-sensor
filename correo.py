# Importamos las librerias
import time
import serial
import smtplib
import mimetypes
# Importamos los módulos necesarios
from email.MIMEText import MIMEText

#Declaramos las variables de el emisor y el receptor de el correo a enviar.
emisor = ""
receptor = ""

#Creamos el objeto "ser" para comunicarnos con Arduino, cambiar el puerto COM por el de tu arduino
ser = serial.Serial('COM4', 9600)

#Definimos la funciona que se encargara de mandar el mail
def envia_email():
    # Autenticamos
    mailServer = smtplib.SMTP('smtp.gmail.com',587)
    mailServer.ehlo()
    mailServer.starttls()
    mailServer.ehlo()
    mailServer.login(emisor,"")

    # Enviamos el mensaje
    mailServer.sendmail(emisor,receptor,mensaje.as_string())
    print("Mensaje Enviado!")

    # Cerramos conexión
    mailServer.close()


while True:
    lectura = ser.readline()
    print(lectura)
    #Este If se encarga de leer lo que entra por el puerto serie
    #Si la primer letra de lo que contiene el puerto seria es una "M" se cumple la condicion
    if lectura[0] == 'H' :
        #Declaramos las variables fecha y hora para enviarlas en el mail
        fecha = time.strftime("%d/%m/%y")
        hora = time.strftime("%H:%M:%S")
        # Configuracion del mensaje
        mensaje = MIMEText("""Se detectaron condiciones ambientales fuera de los parametros:""" + lectura)
        mensaje['From']=emisor
        mensaje['To']=receptor
        mensaje['Subject']="Alarma"
        #Se envia el mail
        envia_email()
        print(mensaje)
    time.sleep(0.5)