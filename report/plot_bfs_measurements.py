import json
import matplotlib.pyplot as plt
import matplotlib
import sys

"""
This script reads an input file (specified as a command-line argument)
containing timing measurements for the BFS algorithm. It produces
a plot of time (in milliseconds) versus the number of edges plus the
number of vertices in the randomly generated input graph.
"""
if __name__ == '__main__':

  # get path to input file
  filepath = sys.argv[1]

  # load the input file into a table
  x = []
  y = []
  with open(filepath, 'r') as input_file:
    bfs_measurements = json.load(input_file)
    num_samples = int(bfs_measurements['bfs']['num_samples'])
    for i in range(num_samples):
      node = bfs_measurements['bfs'][str(i)]
      v = int(node['num_vertices'])
      e = int(node['num_edges'])
      milliseconds = float(node['milliseconds'])
      x.append(v + e);
      y.append(milliseconds)

  # plot the data
  plt.plot(x, y, 'o')

  # adjust plot settings
  plt.title('Performance of Breadth-First Search\n(Note: E = V^2 for all samples)', fontsize='72')
  plt.xlabel('V + E', fontsize='48')
  plt.ylabel('Milliseconds', fontsize='48')
  plt.xticks(fontsize=28)
  plt.yticks(fontsize=28)

  # display the plot
  plt.show()
