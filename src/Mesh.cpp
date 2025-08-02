#include "Mesh.h"

namespace mesh {

void Mesh::begin() {
  Dispatcher::begin();
}

void Mesh::loop() {
  Dispatcher::loop();
}

DispatcherAction Mesh::onRecvPacket(Packet* pkt) {
    return 0;
}

}