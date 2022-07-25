"""

@author: Nichifor Dragos

"""
import random
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

    def copy_graph(self):
        return copy.copy(self)

    @staticmethod
    def menu():
        print("\n1) Get the number of vertices.")
        print("2) Check if there is an edge between 2 vertices.")
        print("3) Get the in degree and the out degree of a vertex.")
        print("4) Retrieve the information (cost) of an edge.")
        print("5) Modify the information (cost) of an edge.")
        print("6) Add an edge.")
        print("7) Remove an edge.")
        print("8) Add vertex.")
        print("9) Remove vertex.")
        print("10) Write graph.")
        print("11) Show outbound edges of a vertex.")
        print("12) Show inbound edges of a vertex.")
        print("13) List all the vertices.")
        print("14) Get the number of edges.")
        print("p - Print in console.")
        print("x - Exit the program.\n")

    def start(self):
        while True:
            try:
                self.menu()
                command = input("Your command is: ")
                if command.lower() == 'x':
                    print("Exiting...")
                    break
                if command.lower() == 'p':
                    self.print_in_console()
                else:
                    command = command.strip()
                    if command == '1':
                        print("The number of vertices is:", self.__vertices)
                    elif command == '2':
                        first = input("The source vertex is: ")
                        second = input("The destination vertex is: ")
                        first = first.strip()
                        second = second.strip()
                        self.__validator.check_vertex(first, self.all_vertices())
                        self.__validator.check_vertex(second, self.all_vertices())
                        if self.check_if_edge(int(first), int(second)) is True:
                            print("There is a vertex between", first, "and", second, ".")
                        else:
                            raise GraphException("No vertex between " + str(first) + " and " + str(second) + ".")
                    elif command == '3':
                        vertex = input("The vertex is: ")
                        vertex = vertex.strip()
                        self.__validator.check_vertex(vertex, self.all_vertices())
                        in_vertex, out_vertex = self.check_in_out_degree(int(vertex))
                        print("The in degree of the vertex", vertex, "is", in_vertex, "and the out degree is",
                              out_vertex, ".")
                    elif command == '4':
                        first = input("The source vertex is: ")
                        second = input("The destination vertex is: ")
                        first = first.strip()
                        second = second.strip()
                        self.__validator.check_vertex(first, self.all_vertices())
                        self.__validator.check_vertex(second, self.all_vertices())
                        cost = self.retrieve_cost(int(first), int(second))
                        if cost is not False:
                            print("The cost of the edge", first, "->", second, "is", cost, ".")
                        else:
                            print("The given edge does not exist.")
                    elif command == '5':
                        first = input("The source vertex is: ")
                        second = input("The destination vertex is: ")
                        first = first.strip()
                        second = second.strip()
                        self.__validator.check_vertex(first, self.all_vertices())
                        self.__validator.check_vertex(second, self.all_vertices())
                        new_cost = input("The new cost is: ")
                        self.__validator.check_cost(new_cost)
                        if self.modify_cost(int(first), int(second), new_cost) is True:
                            print("The cost of the edge", first, "->", second, "has been updated to", new_cost, ".")
                        else:
                            print("The given edge does not exist.")
                    elif command == '6':
                        dat = input(
                            "Please enter the source vertex, the destination vertex and the information (cost) "
                            "with a space in between: ")
                        dat = dat.split(' ')
                        for i in range(len(dat)):
                            dat[i] = dat[i].strip()
                        if len(dat) < 3:
                            raise GraphException("Source, destination or cost missing.")
                        self.__validator.check_vertex(dat[0], self.all_vertices())
                        self.__validator.check_vertex(dat[1], self.all_vertices())
                        self.add_edge(int(dat[0]), int(dat[1]), int(dat[2]))
                        print("The edge", dat[0], "->", dat[1], "with the cost", dat[2], "has been added.")
                    elif command == '7':
                        dat = input(
                            "Please signal the edge you want to remove by writing the source and the destination "
                            "vertex with a space in between: ")
                        dat = dat.split(' ')
                        for i in range(len(dat)):
                            dat[i] = dat[i].strip()
                        if len(dat) < 2:
                            raise GraphException("Source or destination missing.")
                        self.__validator.check_vertex(dat[0], self.all_vertices())
                        self.__validator.check_vertex(dat[1], self.all_vertices())
                        self.remove_edge(int(dat[0]), int(dat[1]))
                        print("The edge", dat[0], "->", dat[1], "has been removed.")
                    elif command == '8':
                        vertex = input("The vertex you want to add is: ")
                        if vertex.isnumeric() is False:
                            raise GraphException("The vertex does not exist.")
                        if int(vertex) in self.all_vertices():
                            raise GraphException("This vertex already exists.")
                        self.add_vertex(int(vertex))
                        print("A new vertex has been added.")
                    elif command == '9':
                        vertex = input("The vertex you want to remove is: ")
                        self.__validator.check_vertex(vertex, self.all_vertices())
                        self.remove_vertex(int(vertex))
                        print("The vertex", vertex, "has been removed.")
                    elif command == '10':
                        self.write()
                        print("The graph was written in the output file 'out'.")
                    elif command == '11':
                        vertex = input("The vertex you want the list of outbound edges for is: ")
                        outbound_edges = self.outbound_vertex(int(vertex))
                        print("The outbound edges of", vertex, "are:", outbound_edges)
                    elif command == '12':
                        vertex = input("The vertex you want the list of inbound edges for is: ")
                        inbound_edges = self.inbound_vertex(int(vertex))
                        print("The inbound edges of", vertex, "are:", inbound_edges)
                    elif command == '13':
                        list_vertices = self.all_vertices()
                        print("The list of all vertices is:", list_vertices)
                    elif command == '14':
                        print("The number of edges is:", self.number_of_edges())
                    else:
                        raise GraphException("\nPlease enter a valid command!")
            except GraphException as ge:
                print(ge)


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


def print_main_menu():
    print("1) Read from file.")
    print("2) Create a random graph with a given number of vertices and edges.")


def check_command(cmd):
    if cmd != "2" and cmd != "1":
        return False
    return True


def check_vertices_edges(vert, edg):
    if vert.isnumeric() is False or edg.isnumeric() is False:
        return False
    return True


def create_graph():
    vertices_graph = input("Please enter the number of vertices: ")
    edges_graph = input("Please enter the number of edges: ")
    vertices_graph = vertices_graph.strip()
    edges_graph = edges_graph.strip()
    validator = GraphValidator()
    if check_vertices_edges(vertices_graph, edges_graph) is True:
        created_graph = DirectedGraph(validator, int(vertices_graph), int(edges_graph))
        for i in range(int(edges_graph)):
            source = random.randint(0, int(vertices_graph) - 1)
            destination = random.randint(0, int(vertices_graph) - 1)
            while created_graph.check_if_edge(source, destination):
                destination = random.randint(0, int(vertices_graph) - 1)
            cost = random.randint(-100, 100)
            created_graph.add_edge(source, destination, cost)
        return created_graph
    else:
        return None


if __name__ == '__main__':
    print_main_menu()
    command_start = input("Your command: ")
    if check_command(command_start) is True:
        if int(command_start) == 2:
            graph = create_graph()
            if graph is not None:
                print("\nGraph created successfully!")
                graph.start()
            else:
                print("The graph could not be created!")
        elif int(command_start) == 1:
            nr = 0
            vertices = 0
            edges = 0
            graph_validator = GraphValidator()
            graph = None
            f = open("random_graph1.txt")
            for line in f.readlines():
                if vertices == 0 and edges == 0:
                    line = line.split(" ")
                    vertices = line[0].strip()
                    edges = line[1].strip()
                    graph = DirectedGraph(graph_validator, int(vertices), int(edges))
                else:
                    if nr >= int(edges):
                        print("\nThe number of vertices exceeds the one specified. Exiting...")
                        exit()
                    nr += 1
                    line = line.split(" ")
                    line[0] = line[0].strip()
                    line[1] = line[1].strip()
                    line[2] = line[2].strip()
                    graph.add_edge(int(line[0]), int(line[1]), int(line[2]))
            f.close()
            print("\nGraph read successfully!")
            graph.start()
    else:
        print("\nInvalid command!", "Exiting...")
