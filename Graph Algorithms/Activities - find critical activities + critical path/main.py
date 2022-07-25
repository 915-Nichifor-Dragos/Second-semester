"""

@author : Nichifor Dragos

"""

import copy


class DirectedGraph:
    def __init__(self, validator, vertices_graph=0, edges_graph=0):
        self.__validator = validator
        self.__vertices = vertices_graph
        self.__edges = edges_graph
        self.__din = {}
        self.__dout = {}
        self.__activities_duration = {}
        self.__initialise_dictionaries()

    def __initialise_dictionaries(self):
        for i in range(self.__vertices):
            self.__din[i] = []
            self.__dout[i] = []

    def write(self):
        file = open("out", 'wt')
        file.write(str(self.__vertices) + " " + str(self.__edges) + '\n')

    @property
    def number_of_edges(self):
        return self.__edges

    @property
    def number_of_vertices(self):
        return self.__vertices

    def inbound_vertex(self, vertex):
        return copy.copy(self.__din[vertex])

    def outbound_vertex(self, vertex):
        return copy.copy(self.__dout[vertex])

    def add_edge(self, source, destination):
        self.__dout[int(source)].append(destination)
        self.__din[int(destination)].append(source)

    def remove_edge(self, source, destination):
        try:
            self.__dout[source].remove(destination)
            self.__din[destination].remove(source)
        except IndexError as ie:
            return False

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
        self.__vertices -= 1

    def check_if_edge(self, source, destination):
        if destination in self.outbound_vertex(source):
            return True
        return False

    def set_activity_duration(self, activity, duration):
        self.__activities_duration[activity] = duration

    def get_all_activities_duration(self):
        return self.__activities_duration

    def check_in_degree(self, vertex):
        in_vertex = self.inbound_vertex(vertex)
        return len(in_vertex)

    def check_out_degree(self, vertex):
        out_vertex = self.outbound_vertex(vertex)
        return len(out_vertex)

    def all_vertices(self):
        return list(self.__din.keys())

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

    def topological_sort_dfs(self, x, sorted_list, fully_processed, in_process):
        in_process.add(x)
        for inbound_neighbour in self.inbound_vertex(x):
            if inbound_neighbour in in_process:
                return False
            else:
                if inbound_neighbour not in fully_processed:
                    ok = self.topological_sort_dfs(inbound_neighbour, sorted_list, fully_processed, in_process)
                    if not ok:
                        return False
        in_process.remove(x)
        sorted_list.append(x)
        fully_processed.add(x)
        return True

    def dag(self):
        sorted_list = []
        fully_processed = set()
        in_process = set()
        for vertex in self.all_vertices():
            if vertex not in fully_processed:
                ok = self.topological_sort_dfs(vertex, sorted_list, fully_processed, in_process)
                if not ok:
                    return []
        return sorted_list

    def compute_times(self, sorted_list):
        first = -1
        last = len(sorted_list)
        inf = 999

        self.add_vertex(first)
        self.add_vertex(last)

        sorted_list.insert(0, first)
        self.__activities_duration[first] = 0
        for vertex in self.all_vertices():
            if self.check_in_degree(vertex) == 0 and vertex != first and vertex != last:
                self.add_edge(first, vertex)

        sorted_list.append(last)
        self.__activities_duration[last] = 0
        for vertex in self.all_vertices():
            if self.check_out_degree(vertex) == 0 and vertex != first and vertex != last:
                self.add_edge(vertex, last)

        earliest_start_time = {}
        earliest_end_time = {}
        for vertex in self.all_vertices():
            earliest_start_time[vertex] = 0
            earliest_end_time[vertex] = 0

        latest_start_time = {}
        latest_end_time = {}
        for vertex in self.all_vertices():
            latest_start_time[vertex] = inf
            latest_end_time[vertex] = inf

        for i in range(1, len(sorted_list)):
            for predecessor in self.inbound_vertex(sorted_list[i]):
                earliest_start_time[sorted_list[i]] = max(earliest_start_time[sorted_list[i]],
                                                          earliest_end_time[predecessor])
            earliest_end_time[sorted_list[i]] = earliest_start_time[sorted_list[i]] + self.__activities_duration[
                sorted_list[i]]

        latest_end_time[last] = earliest_end_time[last]
        latest_start_time[last] = latest_end_time[last] - self.__activities_duration[last]
        latest_start_time[first] = 0
        latest_end_time[first] = 0

        for i in range(len(sorted_list) - 1, 0, -1):
            for successor in self.outbound_vertex(sorted_list[i]):
                latest_end_time[sorted_list[i]] = min(latest_end_time[sorted_list[i]], latest_start_time[successor])
            latest_start_time[sorted_list[i]] = latest_end_time[sorted_list[i]] - self.__activities_duration[
                sorted_list[i]]

        sorted_list.pop(0)
        sorted_list.pop()
        self.remove_vertex(first)
        self.remove_vertex(last)

        critical_activities = []
        for activity in sorted_list:
            if earliest_start_time[activity] == latest_start_time[activity]:
                critical_activities.append(activity)

        return earliest_start_time, earliest_end_time, latest_start_time, latest_end_time, critical_activities

    def activities_scheduling(self):
        sorted_list = self.dag()
        if len(sorted_list) == 0:
            raise GraphException("The graph is not DAG")
        print("The result of topological sorting: ", sorted_list)

        earliest_start_time, earliest_end_time, latest_start_time, latest_end_time, critical_activities = \
            self.compute_times(sorted_list)

        for vertex in sorted_list:
            print(f"Activity {vertex}: earliest starting time: {earliest_start_time[vertex]} - "
                  f"earliest ending time {earliest_start_time[vertex] + self.__activities_duration[vertex]} | "
                  f"latest starting time: {latest_start_time[vertex]} - "
                  f"latest ending time {latest_start_time[vertex] + self.__activities_duration[vertex]}")
        print(f"Total cost of the project: {earliest_start_time[len(sorted_list)]}")
        print("Critical activities: ", end="")
        for activity in critical_activities:
            print(activity, end=" ")
        print("")


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


""" ================================================================================================ """


def read():
    graph = None
    f = open("my_exec.txt")
    for line in f.readlines():
        line = line.split()
        if graph is None:
            val = GraphValidator()
            graph = DirectedGraph(val, int(line[0]), int(line[1]))
        else:
            if len(line) == 2:
                graph.add_edge(int(line[0]), int(line[1]))
            else:
                for i in range(len(line)):
                    graph.set_activity_duration(i, int(line[i]))
    return graph


if __name__ == '__main__':
    gr = read()
    print("\nInitial graph")
    gr.print_in_console()
    gr.activities_scheduling()
