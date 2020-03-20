#include "road.h"

Road::Road(std::vector<Coordinate> nodes) :nodes_(nodes){
}

Coordinate Road::GetNode(int node_number) {
  return nodes_[node_number];
}
