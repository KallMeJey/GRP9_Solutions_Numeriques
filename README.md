# GRP9_Solutions_Numeriques
## Membres du groupe :
-> Mohamed-Ali MOUSBAI <br />
-> Jeneifan CHATHIANATHAN <br />
-> Mohamed KHALLOUKI <br />
-> Eltan TASLI <br />

## Montage ESP8266 + DHT22

<img src="https://user-images.githubusercontent.com/83539183/215097901-4a0b7f8e-84f6-474f-a771-6dd42a4cc8b5.jpg" width="500" height="500">


## Flow sur Node-Red
![flow node-red](https://user-images.githubusercontent.com/83539183/215099292-2cc54914-5fdd-4dbb-b691-d75b25d336a6.png)

Ici nous faisons deux "MQTT IN" afin de récupérer pour chaque topic (temperature/humidity) les données depuis le broker du Edge Of Network. Puis un parsing de chaque valeur pour l'afficher dans un dashboard. Une conversion est faire en SparkPlug B pour faire au final un "MQTT out" vers le broker de l'hôte Scada.

## Affichage de ma température et taux d'humidité sur Node-Red
![dashboard nr](https://user-images.githubusercontent.com/83539183/215100042-0c0bc4ff-5f8a-42de-b89c-fe20828d8f98.png)

## Affichage des données de température et humidité sur Ignition
![Ignition](https://user-images.githubusercontent.com/83539183/215100499-13eda9f6-b313-4c3f-8fd0-eb163597f687.png)

Malheureusement lors de la capture d'écran, le Groovrio était en panne, nous avons donc pu afficher que la température.
