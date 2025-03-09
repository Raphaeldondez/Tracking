
import bluetooth
import socket
import time


#initialisation des variables : 
distance = 0
angle = 0



''' On suppose qu'on reçoit sous la forme "Distance|Angle"  '''
test = "365|78"

def parse_data(data): # Cette fonction prends le message envoyé par le robot et en renvoie eux entiers : distance, angle
    decoded_data = data.decode() # Convertie binaire -> str
    distance, angle = decoded_data.split('|') # Isole les données de chaque côté du |
    print (distance)
    print(angle)
    return int(distance), int(angle)  # Converti les sotries en entier



target_name = "Tracking" #ID Bluetooth du robot
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
        
        received_data = s.recv(1024)
        if received_data != "" : #On vérifie si la donnée reçu est nul
            distance, angle = parse_data(received_data)
            print("New_Distance: ", distance, " | New_Angle: ", angle)

        #Ici tu peux mettre les conditions sur la distance par exemple :
        if distance < 50 :
            print("get out of here!!!")
        else :
            print("nice")

        #Fin


    s.close()

else:
    print("could not find target bluetooth device nearby")