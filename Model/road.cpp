#include "road.h"

#include <utility>

Road::Road(std::vector<Coordinate>  nodes) : nodes_(std::move(nodes)) {}

Coordinate Road::GetNode(int node_number) const {
  return nodes_[node_number];
}

bool Road::IsEnd(int node_number) const {
  return node_number == static_cast<int>(nodes_.size());
}
