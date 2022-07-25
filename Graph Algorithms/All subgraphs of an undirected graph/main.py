"""

@author: Nichifor Dragos

"""
import copy

from collections import deque


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


def search_nodes(graph, vertex, visited, processed):
    """
    Searches the neighbours of a given vertex

    :param graph: the graph the search is being made on
    :param vertex: the vertex
    :param visited: the list of already visited nodes
    :param processed: the list of nodes that already are part of a connected component
    :return:
    """
    queue = deque()
    queue.append(vertex)
    while len(queue) != 0:
        node = queue.popleft()
        for v in graph.outbound_vertex(node):
            if v not in visited:
                queue.append(v)
                processed.append(v)
                visited.append(v)

    """
    for v in graph.outbound_vertex(vertex):
        if v not in visited:
            visited.append(v)
            processed.append(v)
            search_nodes(graph, v, visited, processed)
    """


def breadth_first_search(graph):
    """
    Does a BFS on the graph

    :param graph: the graph we work with
    :return: a list of connected components of type 'graph'
    """
    visited = []
    processed = []
    list_graphs = []
    validator = GraphValidator()
    for vertex in graph.all_vertices():
        if vertex not in visited:
            visited.append(vertex)
            processed.append(vertex)
            search_nodes(graph, vertex, visited, processed)
            subgraph = DirectedGraph(validator, 0, 0)
            for source in processed:
                subgraph.add_vertex(source)
            for source in processed:
                for destination in graph.outbound_vertex(source):
                    if subgraph.check_if_edge(source, destination) is False:
                        subgraph.add_edge(source, destination, 0)
                    if subgraph.check_if_edge(destination, source) is False:
                        subgraph.add_edge(destination, source, 0)
            list_graphs.append(subgraph)
            processed = []

    return list_graphs


def read():
    graph = None
    f = open("graph1.in")
    for line in f.readlines():
        line = line.split()
        if graph is None:
            val = GraphValidator()
            graph = DirectedGraph(val, int(line[0]), int(line[1]))
        else:
            graph.add_edge(int(line[0]), int(line[1]), 0)
            graph.add_edge(int(line[1]), int(line[0]), 0)
    return graph


if __name__ == '__main__':
    """
    val = GraphValidator()
    gr = DirectedGraph(val, 6, 0)
    gr.add_edge(0, 1, 0)
    gr.add_edge(1, 0, 0)
    gr.add_edge(0, 2, 0)
    gr.add_edge(2, 0, 0)
    gr.add_edge(4, 5, 0)
    gr.add_edge(5, 4, 0)
    """
    gr = read()
    print("\nInitial graph")
    gr.print_connected_component()
    print("\n========================")
    for el in breadth_first_search(gr):
        print("\nSubgraph")
        el.print_connected_component()
