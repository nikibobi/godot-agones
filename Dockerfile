FROM debian:stretch-slim

RUN useradd -m godot

WORKDIR /home/godot

COPY --chown=godot example/export/ .

RUN ldconfig `pwd`

USER godot

ENTRYPOINT ./game.x86_64
