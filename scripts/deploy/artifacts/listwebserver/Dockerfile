# This is the LIST server's runtime Dockerfile

FROM gcc:10.2

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -yq \
        wireshark-common \
        nginx

# Install node
RUN curl -sL https://deb.nodesource.com/setup_12.x -o nodesource_setup.sh
RUN bash nodesource_setup.sh
RUN apt-get install -y \
        ffmpeg \
        zip \
        nodejs

RUN npm install -g serve
RUN npm install -g lerna

ENV LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/local/lib/

ADD app/ /app
ADD js/ /js
ADD lib/ /usr/local/lib
# nginx Configuration
ADD data/config/ /etc/nginx/
# nginx certs
ADD data/certs/ /etc/ssl/certs/

WORKDIR /app/listwebserver/

CMD bash /app/sedstaticconfig.sh & service nginx start & serve -s /app/gui -p 8080 & npm start -- config.yml --dev & ../bin/stream_pre_processor amqp://rabbitmq:5672
