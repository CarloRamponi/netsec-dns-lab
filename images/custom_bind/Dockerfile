FROM "kathara/base"

COPY --chown=root:root sources.list /etc/apt/sources.list
RUN apt-get update -y && apt-get install bind9 -y