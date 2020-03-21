#include "road.h"

Road::Road(const std::vector<Coordinate>& nodes) : nodes_(nodes) {
}

Coordinate Road::GetNode(int node_number) const{
  return nodes_[node_number];
}
void Road::SetRoad(const std::vector<Coordinate>& nodes) {
  nodes_ = nodes;
}
