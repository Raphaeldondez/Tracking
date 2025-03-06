 python -m pip install -e git+https://github.com/pybluez/pybluez.git#egg=pybluez



import bluetooth
import socket
import time





def parse (data):
    parsed = spl
return parsed_data



''' On suppose qu'on reçoit sous la forme "Distance|Angle"  '''
test = "365|78"


target_name = "ESP32BT" #ID Bluetooth du robot
target_address = None

nearby_devices = bluetooth.discover_devices(lookup_names=True,lookup_class=True)  #Activation de la recherche Bluetooth 
print(nearby_devices)
for btaddr, btname, btclass in nearby_devices:  #On parcourt les appareils dispos et se connecte à celui voulu
    if target_name == btname:
        target_address = btaddr
        break

if target_address is not None:
    print("Connection à  {} d'addresse Bluetooth {} ...".format(target_name,target_address))
    
    serverMACAddress = target_address
    port = 1
    s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    s.connect((serverMACAddress,port))
    print("Connecté à : {}".format(target_name))
    
    while 1:
        time.sleep(1); # Attente de 1s

        text = "HI"
        s.send(bytes(text, 'UTF-8'))
        
        data = s.recv(1024)
        if data:
            print(data)
    s.close()

else:
    print("could not find target bluetooth device nearby")