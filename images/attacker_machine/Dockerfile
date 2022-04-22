FROM "kathara/base"

RUN apt-get update -y && apt-get install -y libpcap-dev libssl-dev cmake git
RUN git clone https://github.com/mfontanini/libtins.git
WORKDIR /libtins
RUN mkdir build && cd build && cmake ../ && make && make install
WORKDIR /
RUN ldconfig
COPY --chown=root:root exploit.cpp /
COPY --chown=root:root exploit-poisoning.cpp /
RUN g++ -o exploit exploit.cpp -ltins
RUN g++ -o exploit-poisoning exploit-poisoning.cpp -ltins
