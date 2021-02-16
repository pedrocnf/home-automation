# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):

  client.subscribe("#")
  print ("conectado")

def on_message(client, userdata, msg):

  print(msg.topic+" - "+str(msg.payload))
  
client = mqtt.Client()

client.on_connect = on_connect

client.on_message = on_message
  
client.username_pw_set(".....", password=".....")
  
client.connect("127.168.0.117", 1883, 60)
  
  
client.loop_forever()
