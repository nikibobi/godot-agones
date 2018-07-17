# Godot plugin for Agones

## Clone with submodules
`git clone --recurse-submodules https://github.com/nikibobi/godot-agones.git`

## Download Agones libs
First you need to [download](https://github.com/GoogleCloudPlatform/agones/releases/download/v0.2.0/agonessdk-0.2.0-dev-linux-arch_64.tar.gz) and extract the `lib/` folder to `example/bin/x11/lib/` and `include/` folder to `include/`

## Compile

### with Scons
To compile the library itself you need to have scons installed. Then to build just type `scons`
and it will use these defaults

`scons platform=linux bits=64 target=debug project=example/`

Since we will be running the server in a container you shouldn't change those parameters. You can pass `project` to your game's path and it will put the compiled library there.

### by hand
If you prefer not to use scons you can use these commands (or use them to make a proper Makefile)
```
g++ -o src/gdlibrary.os -c -fPIC -g -O3 -std=c++14 -fPIC -I. -Isrc -Iinclude -Igodot_headers -Igodot-cpp/include -Igodot-cpp/include/core src/gdlibrary.cpp

g++ -o src/agones.os -c -fPIC -g -O3 -std=c++14 -fPIC -I. -Isrc -Iinclude -Igodot_headers -Igodot-cpp/include -Igodot-cpp/include/core src/agones.cpp

g++ -o example/bin/x11/libagones.so -shared src/gdlibrary.os src/agones.os -Lgodot-cpp/bin -Lexample/bin/x11/lib -lgodot-cpp.linux.64 -lagonessdk -lgrpc++_unsecure -lgrpc -lprotobuf
```

## Export example
Next you need to export your game to `server` platform in `example/export/` folder.

## Build Docker image
I will asume you already have Docker installed. After the game is exported you can build an image from it.

`docker build -t <image> .`

`docker push <image>`

## Install Agones
Next you have to [install](https://github.com/GoogleCloudPlatform/agones/blob/master/install/README.md) Agones to your kubernetes cluster.

## Create a game server
Next use `kubectl` to create a single game server instance

`kubectl apply -f k8s/gameserver.yaml`

And check the results with

`watch kubectl describe gameserver`

until it's state becomes ready and it gets ip and port asigned.

You can read more detailed guides:
- [Create a Game Server](https://github.com/GoogleCloudPlatform/agones/blob/master/docs/create_gameserver.md)
- [Create a Game Server Fleet](https://github.com/GoogleCloudPlatform/agones/blob/master/docs/create_fleet.md)