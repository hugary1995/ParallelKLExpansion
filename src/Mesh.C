#include <iostream>
#include <sstream>
#include "Mesh.h"

void
Mesh::readMeshFromFile(const std::string fileName)
{
  std::ifstream meshFile(fileName);

  std::string line;
  while (std::getline(meshFile, line))
  {
    if (line == "$PhysicalNames")
      readDomains(&meshFile);
    if (line == "$Nodes")
      readNodes(&meshFile);
    if (line == "$Elements")
      readElements(&meshFile);
  }
}

void
Mesh::readDomains(std::ifstream * meshFile)
{
  std::cout << "\033[1;34mReading Domain Names...\033[0m";
  std::string line;
  std::getline(*meshFile, line);
  std::istringstream parser(line);
  unsigned int NDomains;
  parser >> NDomains;

  for (unsigned int i = 0; i < NDomains; i++)
  {
    std::getline(*meshFile, line);
    std::istringstream parser(line);
    unsigned int dim, domainID;
    std::string domainName;
    if (!(parser >> dim >> domainID >> domainName))
      std::cout << "\033[1;31mError in readDomains!\033[0m" << std::endl;

    domainName = domainName.substr(1, domainName.size() - 2);
    _domainMapping[domainName] = domainID;
  }

  std::getline(*meshFile, line);
  if (line != "$EndPhysicalNames")
    std::cout << "\033[1;31mError in readDomains!\033[0m" << std::endl;

  std::cout << "\033[1;34mDone\033[0m" << std::endl;
}

void
Mesh::readNodes(std::ifstream * meshFile)
{
  std::cout << "\033[1;34mReading Nodes...\033[0m";
  std::string line;
  std::getline(*meshFile, line);
  std::istringstream parser(line);
  unsigned int NNodes;
  parser >> NNodes;
  _nodes.resize(NNodes);

  for (unsigned int i = 0; i < NNodes; i++)
  {
    std::getline(*meshFile, line);
    std::istringstream parser(line);
    unsigned int nodeID;
    double x, y;
    if (!(parser >> nodeID >> x >> y))
      std::cout << "\033[1;31mError in readNodes!\033[0m" << std::endl;

    Node * node = new Node(nodeID, x, y);
    _nodes[i] = node;
  }

  std::getline(*meshFile, line);
  if (line != "$EndNodes")
    std::cout << "\033[1;31mError in readNodes!\033[0m" << std::endl;

  std::cout << "\033[1;34mDone\033[0m" << std::endl;
}

void
Mesh::readElements(std::ifstream * meshFile)
{
  std::cout << "\033[1;34mReading Elements...\033[0m";
  std::string line;
  std::getline(*meshFile, line);
  std::istringstream parser(line);
  unsigned int NElems;
  parser >> NElems;
  _elems.resize(NElems);

  for (unsigned int i = 0; i < NElems; i++)
  {
    std::getline(*meshFile, line);
    std::istringstream parser(line);
    unsigned int elemID, type, dim, domain, dummy2, n1, n2, n3;
    if (!(parser >> elemID >> type >> dim >> domain >> dummy2))
      std::cout << "\033[1;31mError in readElements!\033[0m" << std::endl;

    if (type == 1)
    {
      parser >> n1 >> n2;
      ElemB2 * elem = new ElemB2(domain, elemID, {getNodePtr(n1), getNodePtr(n2)});
      _elems[i] = elem;
    }
    else if (type == 2)
    {
      parser >> n1 >> n2 >> n3;
      ElemT3 * elem = new ElemT3(domain, elemID, {getNodePtr(n1), getNodePtr(n2), getNodePtr(n3)});
      _elems[i] = elem;
    }
  }

  std::getline(*meshFile, line);
  if (line != "$EndElements")
    std::cout << "\033[1;31mError in readElements!\033[0m" << std::endl;

  std::cout << "\033[1;34mDone\033[0m" << std::endl;
}

Node *
Mesh::getNodePtr(unsigned int node_id)
{
  for (auto node = _nodes.begin(); node != _nodes.end(); node++)
    if ((*node)->id() == node_id)
      return *node;
  return NULL;
}
