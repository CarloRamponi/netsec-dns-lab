FROM "kathara/base"

RUN apt-get update -y && apt-get install -y libpcap-dev libssl-dev cmake git
RUN git clone https://github.com/mfontanini/libtins.git
WORKDIR /libtins
RUN mkdir build && cd build && cmake ../ && make && make install
WORKDIR /
RUN ldconfig
COPY --chown=root:root kaminsky.cpp /
COPY --chown=root:root cache-poisoning.cpp /
RUN g++ -o kaminsky kaminsky.cpp -ltins
RUN g++ -o cache-poisoning cache-poisoning.cpp -ltins
