<h1>Estacacao Meteorologica Microcontrolada</h1>
<div  align="center">
    <img src="Imagens/Estacao.jpeg" width=250px>
</div>

Falar brevemente do projeto....

<h2>MQTT</h2>
https://mosquitto.org/
test.mosquitto.org


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
<h2>Microcontroladores</h2>
