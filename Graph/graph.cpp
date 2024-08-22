#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <vector>

using namespace std;

class Edge {
public:
  int id;
  int weight;

  Edge(int id, int weight) {
    this->id = id;
    this->weight = weight;
  }

  void setId(int id) { this->id = id; }
  void setWeight(int weight) { this->weight = weight; }

  int getId() { return this->id; }
  int getWeight() { return this->weight; }
};

class Node {
public:
  int id;
  list<Edge> edgeList;

  Node() { this->id = 0; }
  Node(int id) { this->id = id; }

  void setId(int id) { this->id = id; }

  int getId() { return this->id; }
  list<Edge> getEdgeList() { return this->edgeList; }
};

class Graph {
public:
  vector<Node> nodeList;

  bool nodeExists(int nodeID) {
    for (auto &node : nodeList) {
      if (node.getId() == nodeID) {
        return true;
      }
    }
    return false;
  }

  void addNode(int newNodeID) {
    if (!nodeExists(newNodeID)) {
      Node newNode(newNodeID);
      nodeList.push_back(newNode);
      cout << "Node with id: " << newNodeID << " added successfully." << endl;
    } else {
      cout << "Node with id: " << newNodeID << " already exists." << endl;
    }
  }

  void updateNode(int nodeID, int newNodeID) {
    for (auto &node : nodeList) {
      if (node.getId() == nodeID) {
        node.setId(newNodeID);
        cout << "Node with id: " << nodeID << " updated to id: " << newNodeID
             << endl;
        return;
      }
    }
    cout << "Node with id: " << nodeID << " does not exist.";
  }

  void deleteNode(int nodeID) {
    for (auto it = nodeList.begin(); it != nodeList.end(); ++it) {
      if (it->getId() == nodeID) {
        nodeList.erase(it);
        cout << "Node with id: " << nodeID << " deleted successfully." << endl;
        return;
      }
    }
    cout << "Node with id: " << nodeID << " does not exist." << endl;
  }

  void addEdge(int fromNode, int toNode, int weight) {
    if (nodeExists(fromNode) && nodeExists(toNode)) {
      for (auto &node : nodeList) {
        if (node.getId() == fromNode) {
          node.edgeList.push_back(Edge(toNode, weight));
          cout << "Edge from node " << fromNode << " to node " << toNode
               << " with weight " << weight << " added." << endl;
          return;
        }
      }
    }
  }

  void updateEdge(int fromNode, int toNode, int weight) {
    if (!nodeExists(fromNode) || !nodeExists(toNode)) {
      cout << "One or both nodes do not exist." << endl;
      return;
    }
    for (auto &node : nodeList) {
      if (node.getId() == fromNode) {
        for (auto &edge : node.edgeList) {
          if (edge.getId() == toNode) {
            edge.setWeight(weight);
            cout << "Edge weight from node " << fromNode << " to node "
                 << toNode << " updated to " << weight << "." << endl;
            return;
          }
        }
      }
    }
  }

  void deleteEdge(int fromNode, int toNode) {
    if (!nodeExists(fromNode) || !nodeExists(toNode)) {
      cout << "One or both nodes do not exist." << endl;
      return;
    }
    for (auto &node : nodeList) {
      if (node.getId() == fromNode) {
        for (auto it = node.edgeList.begin(); it != node.edgeList.end(); ++it) {
          if (it->getId() == toNode) {
            node.edgeList.erase(it);
            cout << "Edge from node " << fromNode << " to node " << toNode
                 << " deleted." << endl;
            return;
          }
        }
      }
    }
  }

  void printGraph() {
    for (auto &node : nodeList) {
      cout << "Node " << node.getId() << " has edges to: ";
      for (auto &edge : node.edgeList) {
        cout << edge.getId() << " (weight: " << edge.getWeight() << "), ";
      }
      cout << endl;
    }
  }

  void BFS(int startNodeID) {
    vector<int> visited;
    queue<int> q;

    // Add the starting node to the queue and mark it as visited
    q.push(startNodeID);
    visited.push_back(startNodeID);

    while (!q.empty()) {
      int currentNodeID = q.front();
      q.pop();

      // Traverse the neighbors of the current node
      for (auto &node : nodeList) {
        if (node.getId() == currentNodeID) {
          for (auto &edge : node.edgeList) {
            int neighborID = edge.getId();
            q.push(neighborID);
            visited.push_back(neighborID);
          }
          break;
        }
      }
    }

    // Print the visited nodes in the order they were visited
    cout << "BFS Traversal Order: ";
    for (int nodeID : visited) {
      cout << nodeID << " ";
    }
    cout << endl;
  }
};

int main() {
  int option, nodeID, nodeID2, newID, weight;
  Graph graph;

  do {
    cout << "\nSelect an option:" << endl;

    cout << "1. Add Node" << endl;
    cout << "2. Update Node" << endl;
    cout << "3. Delete Node" << endl;
    cout << "4. Add Edge" << endl;
    cout << "5. Update Edge" << endl;
    cout << "6. Delete Edge" << endl;
    cout << "7. Print Graph" << endl;
    cout << "8. BFS" << endl;
    cout << "0. Exit" << endl;

    cout << "Enter your option: ";
    cin >> option;

    switch (option) {

    case 1:
      cout << "\nAdd Node" << endl;
      cout << "Enter node ID: ";
      cin >> nodeID;
      graph.addNode(nodeID);
      break;

    case 2:
      cout << "\nUpdate Node" << endl;
      cout << "Enter current node ID: ";
      cin >> nodeID;
      cout << "Enter new node ID: ";
      cin >> newID;
      graph.updateNode(nodeID, newID);
      break;

    case 3:
      cout << "\nDelete Node" << endl;
      cout << "Enter node ID to delete: ";
      cin >> nodeID;
      graph.deleteNode(nodeID);
      break;

    case 4:
      cout << "\nAdd Edge" << endl;
      cout << "Enter from node ID: ";
      cin >> nodeID;
      cout << "Enter to node ID: ";
      cin >> nodeID2;
      cout << "Enter edge weight: ";
      cin >> weight;
      graph.addEdge(nodeID, nodeID2, weight);
      break;

    case 5:
      cout << "\nUpdate Edge" << endl;
      cout << "Enter from node ID: ";
      cin >> nodeID;
      cout << "Enter to node ID: ";
      cin >> nodeID2;
      cout << "Enter new edge weight: ";
      cin >> weight;
      graph.updateEdge(nodeID, nodeID2, weight);
      break;

    case 6:
      cout << "\nDelete Edge" << endl;
      cout << "Enter from node ID: ";
      cin >> nodeID;
      cout << "Enter to node ID: ";
      cin >> nodeID2;
      graph.deleteEdge(nodeID, nodeID2);
      break;

    case 7:
      cout << "\nPrint Graph" << endl;
      graph.printGraph();
      break;

    case 8:
      cout << "\nBFS" << endl;
      cout << "Enter starting node ID: ";
      cin >> nodeID;
      graph.BFS(nodeID);
      break;

    case 0:
      cout << "\nExit..." << endl;
      break;

    default:
      cout << "\nInvalid option" << endl;
      break;
    }

  } while (option != 0);
  return 0;
}