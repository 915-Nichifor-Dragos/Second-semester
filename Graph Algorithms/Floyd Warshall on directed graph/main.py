"""

@author : Nichifor Dragos

"""

import copy


class DirectedGraph:
    def __init__(self, validator, vertices_graph, edges_graph):
        self.__validator = validator
        self.__vertices = vertices_graph
        self.__edges = edges_graph
        self.__din = {}
        self.__dout = {}
        self.__cost = []
        self.__initialise_dictionaries()

    def __initialise_dictionaries(self):
        for i in range(self.__vertices):
            self.__din[i] = []
            self.__dout[i] = []

    def write(self):
        file = open("out", 'wt')
        file.write(str(self.__vertices) + " " + str(self.__edges) + '\n')
        for element in self.__cost:
            file.write(str(element[0]) + " " + str(element[1]) + " " + str(element[2]) + '\n')
        file.close()

    @property
    def vertices(self):
        return self.__vertices

    def inbound_vertex(self, vertex):
        return copy.copy(self.__din[vertex])

    def outbound_vertex(self, vertex):
        return copy.copy(self.__dout[vertex])

    def add_edge(self, source, destination, cost):
        self.__dout[int(source)].append(destination)
        self.__din[int(destination)].append(source)
        self.__cost.append([source, destination, cost])

    def remove_edge(self, source, destination):
        ok = 0
        for element in self.__cost:
            if element[0] == source and element[1] == destination:
                self.__cost.remove(element)
                ok = 1
                break
        if ok == 0:
            raise GraphException("Please enter a valid edge.")
        self.__dout[source].remove(destination)
        self.__din[destination].remove(source)

    def add_vertex(self, vertex):
        self.__din[vertex] = []
        self.__dout[vertex] = []

    def remove_vertex(self, vertex):
        outbound = self.outbound_vertex(vertex)
        inbound = self.inbound_vertex(vertex)
        for element in outbound:
            self.__din[element].remove(vertex)
        for element in inbound:
            self.__dout[element].remove(vertex)

        del self.__din[vertex]
        del self.__dout[vertex]

        i = 0
        while i < len(self.__cost):
            if self.__cost[i][0] == vertex or self.__cost[i][1] == vertex:
                self.__cost.remove(self.__cost[i])
                i -= 1
            i += 1

        self.__vertices -= 1

    def check_if_edge(self, source, destination):
        if destination in self.outbound_vertex(source):
            return True
        return False

    def retrieve_cost(self, source, destination):
        for edge in self.__cost:
            if edge[0] == source and edge[1] == destination:
                return edge[2]
        return False

    def modify_cost(self, source, destination, new_cost):
        for edge in self.__cost:
            if edge[0] == int(source) and edge[1] == int(destination):
                edge[2] = int(new_cost)
                return True
        return False

    def check_in_out_degree(self, vertex):
        out_vertex = self.outbound_vertex(vertex)
        in_vertex = self.inbound_vertex(vertex)
        return len(in_vertex), len(out_vertex)

    def all_vertices(self):
        return list(self.__din.keys())

    def number_of_edges(self):
        return len(self.__cost)

    def print_in_console(self):
        print("\nOutbound: ")
        for x in self.all_vertices():
            s = str(x) + ": "
            for y in self.__dout[x]:
                s += str(y) + " "
            print(s)
        print("Inbound: ")
        for x in self.all_vertices():
            s = str(x) + ": "
            for y in self.__din[x]:
                s += str(y) + " "
            print(s)

    def print_connected_component(self):
        for x in self.all_vertices():
            s = str(x) + ": "
            for y in self.__dout[x]:
                s += str(y) + " "
            print(s)

    def copy_graph(self):
        return copy.copy(self)


class GraphException(Exception):
    pass


class GraphValidator:
    @staticmethod
    def check_vertex(vertex, list_vertex):
        if vertex.isnumeric() is False:
            raise GraphException("The vertex does not exist.")
        vertex = int(vertex)
        if vertex not in list_vertex:
            raise GraphException("This vertex does not exist.")

    @staticmethod
    def check_cost(cost):
        try:
            int(cost)
        except ValueError:
            raise GraphException("The cost has to be a number.")


"""
7. Write a program that, given a graph with costs that has no negative cost cycles and two vertices, finds a 
  lowest cost walk between the given vertices. The program shall use the Floyd-Warshall algorithm.
"""


def read():
    graph = None
    f = open("graph_execution1.txt")
    for line in f.readlines():
        line = line.split()
        if graph is None:
            val = GraphValidator()
            graph = DirectedGraph(val, int(line[0]), int(line[1]))
        else:
            graph.add_edge(int(line[0]), int(line[1]), int(line[2]))
    return graph


def write_matrix(matrix_cost, matrix_position):
    print("\nTHE COST MATRIX\n")
    for line in matrix_cost:
        for element in line:
            if element == 'inf':
                print('i', end=' ')
            elif element == 'null':
                print('n', end=' ')
            else:
                print(element, end=' ')
        print("")

    print("\nTHE POSITION MATRIX\n")
    for line in matrix_position:
        for element in line:
            if element == 'null' or element == -1:
                print('n', end=' ')
            else:
                print(element, end=' ')
        print("")


def floyd_warshall(graph):
    cost = []
    distance = []
    for source_node in graph.all_vertices():
        node_cost_line = []
        node_distance_line = []
        for destination_node in graph.all_vertices():
            current_cost = graph.retrieve_cost(source_node, destination_node)
            if destination_node == source_node:
                node_distance_line.append('null')
                node_cost_line.append('null')
            else:
                if current_cost is False:
                    node_cost_line.append('inf')
                    node_distance_line.append(-1)
                else:
                    node_distance_line.append(source_node)
                    node_cost_line.append(current_cost)
        cost.append(node_cost_line)
        distance.append(node_distance_line)

    print("\n\n======== INITIAL STATE ========\n")

    write_matrix(cost, distance)

    for k in graph.all_vertices():
        for i in graph.all_vertices():
            for j in graph.all_vertices():
                if (cost[i][k] != 'null' and cost[i][k] != 'inf') and (cost[k][j] != 'null' and cost[k][j] != 'inf'):
                    if (cost[i][j] != 'inf' and cost[i][j] != 'null') and cost[i][j] > cost[i][k] + cost[k][j]:
                        cost[i][j] = cost[i][k] + cost[k][j]
                        distance[i][j] = distance[k][j]
                    elif cost[i][j] == 'inf':
                        cost[i][j] = cost[i][k] + cost[k][j]
                        distance[i][j] = distance[k][j]
        print("\n\n======== INTERMEDIATE STATE with k =", k, "as intermediate vertex ========\n")
        write_matrix(cost, distance)

    print("\n\n======== FINAL STATE ========\n")

    write_matrix(cost, distance)

    while True:
        nodes = input("\nx - Exit.\nThe nodes you want the minimum path for: ")
        if nodes.lower() == 'x':
            break
        nodes = nodes.strip()
        nodes = nodes.split(' ')
        if int(nodes[0]) > len(cost[1]) or int(nodes[1]) > len(cost[1]) or int(nodes[0]) < 0 or int(nodes[1]) < 0:
            print("Index too big or too low")
        else:
            if cost[int(nodes[0])][int(nodes[1])] == 'inf' or cost[int(nodes[0])][int(nodes[1])] == 'null':
                print("No path between", nodes[0], "and", nodes[1])
            else:
                print("The cost of the minimum path between", nodes[0], "and", nodes[1], "is",
                      cost[int(nodes[0])][int(nodes[1])])
                index = int(nodes[1])
                path = str(index)
                while True:
                    index = distance[int(nodes[0])][index]
                    if index == 'null':
                        break
                    index = int(index)
                    path = path + " >- " + str(index)
                path = path[::-1]
                print(path)


if __name__ == '__main__':
    gr = read()
    print("\nInitial graph")
    gr.print_in_console()
    floyd_warshall(gr)
