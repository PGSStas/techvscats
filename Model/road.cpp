#include "road.h"
Road::Road(const std::vector<Coordinate>& nodes) : nodes_(nodes) {}

Coordinate Road::GetNode(int node_number) const {
  return nodes_[node_number];
}

bool Road::IsEnd(int node_number) const {
  return node_number == static_cast<int>(nodes_.size());
}
