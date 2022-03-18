# wwws

This example is designed to test whether the WS protocol running in a browser can bypass certificate detection.

## Run Server
* Install and run echo ws server.
```
git clone https://github.com/vi/wsmirror.git
cd wsmirror
cargo run 0.0.0.0:8888
```

* Set nginx for ws with Self signed Cert.
```
openssl genrsa -out server.key 2048
openssl req -new -key server.key -out server.csr
openssl x509 -req -in server.csr -out server.crt -signkey server.key -days 3650

docker run --name nginx -d -p 80:80 -p 443:443 -v `pwd`/nginx.conf:/etc/nginx/nginx.conf -v `pwd`/server.crt:/ssl/server.crt -v `pwd`/server.key:/ssl/server.key nginx
```

* Set local domain 
```
sudo echo "<you ip> demo.safematrix.io" >> /etc/hosts
```

## Run web

* Install emcc
```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

* Build and run wasm html.
```
emcc main.cpp -lwebsocket.js -o main.html
emrun --port 8080 ./main.html
```

We're going to get a connection error.

## Tools test

* Netcat, curl and socat for WebSockets.
```
wget https://github.com/vi/websocat/releases/download/v1.9.0/websocat_linux64

sudo cp websocat_linux64 /usr/bin/websocat

websocat -v -k wss://demo.safematrix.io
```

Can communicate with the server.

## conclusion
Even if you put websocket links into WASM, you end up calling the browser's kernel, which validates the certificate. So you need another TLS+TCP connection that is independent of the browser kernel.