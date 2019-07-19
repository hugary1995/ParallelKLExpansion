#pragma once

#include <vector>
#include <fstream>
#include <map>
#include "Type.h"
#include "ElemB2.h"
#include "ElemT3.h"

// Forward Declarations
class Mesh;

class Mesh
{
public:
  Mesh(std::string file_name) { readMeshFromFile(file_name); }

  void readMeshFromFile(std::string file_name);

  void printDomainMapping()
  {
    for (auto map = _domainMapping.begin(); map != _domainMapping.end(); map++)
      std::cout << map->second << " <-- " << map->first << std::endl;
  }
  void printNodes()
  {
    for (auto node = _nodes.begin(); node != _nodes.end(); node++)
      std::cout << **node << std::endl;
  }
  void printElements()
  {
    for (auto elem = _elems.begin(); elem != _elems.end(); elem++)
      std::cout << **elem << std::endl;
  }

private:
  void readDomains(std::ifstream *);
  void readNodes(std::ifstream *);
  void readElements(std::ifstream *);
  Node * getNodePtr(unsigned int);

  std::map<std::string, unsigned int> _domainMapping;
  std::vector<Elem *> _elems;
  std::vector<Node *> _nodes;
};
