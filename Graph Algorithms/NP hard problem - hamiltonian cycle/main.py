"""

@author : Nichifor Dragos

"""

import copy
import queue
import random


# Given an undirected graph with costs satisfying the triangle inequality, find a Hamiltonian cycle of no more than twice the minimum cost in O(m+n log n).

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
    def number_of_vertices(self):
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

    def in_degree(self, vertex):
        return len(self.inbound_vertex(vertex))

    def out_degree(self, vertex):
        return len(self.outbound_vertex(vertex))

    def all_vertices(self):
        return list(self.__din.keys())

    def number_of_edges(self):
        return len(self.__cost)

    def print_in_console(self):
        for x in self.all_vertices():
            s = str(x) + ": "
            for y in self.__dout[x]:
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
8. Given an undirected graph with costs satisfying the triangle inequality, find a Hamiltonian cycle of no
more than twice the minimum cost in O(m+n log n).
"""


def read():
    graph = None
    f = open("graph_execution2.txt")
    for line in f.readlines():
        line = line.split()
        if graph is None:
            val = GraphValidator()
            graph = DirectedGraph(val, int(line[0]), int(line[1]))
        else:
            graph.add_edge(int(line[0]), int(line[1]), int(line[2]))
            graph.add_edge(int(line[1]), int(line[0]), int(line[2]))
    return graph


def prim_algorithm(graph):
    q = queue.PriorityQueue()  # initialise the priority queue
    prev = {}  # initialise the previous position dictionary
    dist = {}  # initialise the minimum distance dictionary
    edges = []  # initialise the edge list as an empty list
    s = random.choice(graph.all_vertices())  # randomly choose the root
    vertices = [s]  # add the start vertex to the set of processed vertices
    for x in graph.outbound_vertex(s):  # we process all the outbound vertices of the source vertex
        dist[x] = graph.retrieve_cost(x, s)  # we update the distance to the vertex x
        prev[x] = s  # we update the previous vertex that has the minimum path leading to x
        q.put((dist[x], x))  # we add the pair <vertex,distance> to the priority queue
    while not q.empty():  # while the priority queue is not empty
        x = q.get()  # we pop the 1st element
        x = x[1]  # set x to the value of the edge, x[0] is the priority
        if x not in vertices:  # if it was not already processed
            edges.append([x, prev[x], gr.retrieve_cost(x, prev[x])])  # we add the pair <x,prev> to the edge list
            vertices.append(x)  # we add it to the set of processed vertices
            for y in graph.outbound_vertex(x):  # we parse all x's outbound vertices
                if y not in dist.keys() or graph.retrieve_cost(x, y) < dist[y]:
                    # if it's not processed or the current path is cheaper
                    dist[y] = graph.retrieve_cost(x, y)  # update the minimum distance
                    q.put((dist[y], y))  # place it in the priority queue
                    prev[y] = x  # we update the previous vertex that has the minimum path leading to x
    return s, edges


def recursive_tsp(tree_root, graph_tree, graph, way):
    for child in graph_tree.outbound_vertex(tree_root):  # for every outbound vertex of the popped vertex
        if child not in way:  # if the vertex does not take part of the path
            way.append(child)  # we add the vertex to the path
            recursive_tsp(child, graph_tree, graph, way)  # we continue our search


def recursive_start():
    min_path = [root]
    hamiltonian_cost = 0
    recursive_tsp(root, graph_prim, gr, min_path)  # we build the hamiltonian path
    min_path.append(root)  # we add the root at the end of the path so we get a cycle
    for i in range(1, len(min_path)):
        hamiltonian_cost = hamiltonian_cost + gr.retrieve_cost(min_path[i - 1], min_path[i])  # compute the cost

    print("The path is: ", min_path, "\nThe cost is: ", hamiltonian_cost)


def non_recursive_tsp(tree_root, graph_tree):
    way = []  # we add the root to the current path
    stack = queue.LifoQueue()   # we initialise the stack
    stack.put(tree_root)  # we add the root to the stack
    while stack.empty() is False:  # while the stack is not empty
        current = stack.get()  # pop the 1st element
        way.append(current)
        child = graph_tree.outbound_vertex(current)  # for every outbound vertex of the popped vertex
        for i in range(len(child) - 1, -1, -1):
            if child[i] not in way:
                stack.put(child[i])  # we add it on the stack
    return way


def non_recursive_start():
    min_path = non_recursive_tsp(root, graph_prim)  # we build the hamiltonian path
    min_path.append(root)  # we add the root at the end of the path so we get a cycle
    hamiltonian_cost = 0
    for i in range(1, len(min_path)):
        hamiltonian_cost = hamiltonian_cost + gr.retrieve_cost(min_path[i - 1], min_path[i])  # compute the cost

    print("The path is: ", min_path, "\nThe cost is: ", hamiltonian_cost)


if __name__ == '__main__':
    gr = read()  # initialise the graph
    print("\nInitial graph")
    gr.print_in_console()  # print the graph

    root, e = prim_algorithm(gr)  # get the root and the edges of the MST spanned by the graph
    graph_prim = DirectedGraph(GraphValidator, gr.number_of_vertices, len(e))  # initialise the MST
    cst = 0  # initialise the cost of the MST
    for element in e:
        cst += int(element[2])  # compute the cost of the MST
        graph_prim.add_edge(int(element[0]), int(element[1]), int(element[2]))  # add the edges to the MST
        graph_prim.add_edge(int(element[1]), int(element[0]), int(element[2]))  # add the edges to the MST

    print("\nThe MST with the cost", cst, "is")
    graph_prim.print_in_console()  # print the MST
    print("\nThe root is: ", root)

    # recursive_start()
    non_recursive_start()
