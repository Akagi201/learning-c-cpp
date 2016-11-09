# protobuf-c

## Build
* `./genpb.sh`
* `gcc sender.c ./mpb/amessage.pb-c.c -lprotobuf-c -o sender`
* `gcc receiver.c ./mpb/amessage.pb-c.c -lprotobuf-c -o receiver`

## Run
* `./sender 1 2 | ./receiver`

## Refs
* <https://github.com/protobuf-c/protobuf-c/wiki/Examples>
