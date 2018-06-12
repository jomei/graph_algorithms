import networkx as nx
import matplotlib.pyplot as plt

FILE = "./graph.txt"
f = open(FILE)
lines = f.readlines()
list = map(lambda l: l.strip().split(" "), lines)


G = nx.DiGraph()
G.add_edges_from(list)

val_map = {'A': 1.0,
           'D': 0.5714285714285714,
           'H': 0.0}

pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'), 
                        node_size = 500)
nx.draw_networkx_labels(G, pos)
nx.draw_networkx_edges(G, pos, edgelist=list, arrows=True)
plt.show()