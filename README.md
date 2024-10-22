<h1>Estacacao Meteorológica Microcontrolada</h1>
<div  align="center">
    <img src="Imagens/Estacao.jpeg" width=250px>
</div>

As estações meteorológicas são equipamentos para monitoramento e registro de condições climáticas com sensores configuráveis para análise de parâmetros atmosféricos e outras variáveis que afetam as rotinas climatológicas. 
O processo de coleta de dados acontece de forma automática - os sensores ligados a um microcontrolador receberão os dados e enviaram para um servidor (Datalogger). 

<h2>MQTT</h2>
O broker utilizado nesse projeto foi o Eclipse Mosquitto. Usamos o mosquitto o qual é muito utilizado para IOT, pois possui servidor aberto para projetos leves. Nesse caso, o endereço usado foi test.mosquitto.org.

<h2>NODE JS</h2>
Caso nao tenha o Node...

```
curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash
```
```
sudo apt install nodejs
```

<h2>Node-Red</h2>
Instalacao:

```
sudo npm install -g --unsafe-perm node-red
```
Caso use docker:
```
docker run -it -p 1880:1880 --name StationNode nodered/node-red
```
To run node-red locally, in terminal:
```
node-red
```
Em seu navegador, acesse:
```
http://localhost:1880
```
<h2>InfluxDB</h2>
Instalacao:

```
curl -O https://download.influxdata.com/influxdb/releases/influxdb2_2.7.6-1_amd64.deb
```
```
sudo dpkg -i influxdb2_2.7.6-1_amd64.deb
```
Para iniciar localmente, no seu terminal:
```
influxd
```

Em seu navegador, acesse:
```
http://localhost:8086
```

<h2>Grafana</h2>
Para instalar e rodar o grafana localmente:

```
sudo apt-get install -y adduser libfontconfig1 musl
```
```
wget https://dl.grafana.com/enterprise/release/grafana-enterprise_10.4.2_amd64.deb
```
```
sudo dpkg -i grafana-enterprise_10.4.2_amd64.deb
```
Depois de instalado, voce pode dar acesso ao grafana da seguinte forma:

```
sudo systemctl enable grafana-server
```
E para iniciar o grafana:
```
sudo systemctl start grafana-server
```

Para checar se esta tudo certo, o status deve ser de ATIVO:
```
sudo systemctl status grafana-server
```
Em seu navegador, acesse:
```
http://localhost:3000
```


##

Referencias:

NODE.JS. Node.js. Disponível em: https://nodejs.org/en. Acesso em: 19 maio 2023. 

MOSQUITTO. Mosquitto. Disponível em: https://mosquitto.org/. Acesso em: 19 maio 2023.

NODE-RED. Node-RED. Disponível em: https://nodered.org/. Acesso em: 19 maio 2023.

INFLUXDATA. Documentation. Disponível em: https://docs.influxdata.com/. Acesso em: 19 maio 2023.

GRAFANA LABS. Grafana. Disponível em: https://grafana.com/. Acesso em: 19 maio 2023.
