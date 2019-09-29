import json
import matplotlib
import matplotlib.pyplot as plt

if __name__ == '__main__':

  # ----------------------------------------------------------------------------
  # plot the BFS measurements
  # ----------------------------------------------------------------------------
  x = []
  y = []
  with open('data.bfs.json', 'r') as stream:
    data = json.load(stream)
    num_samples = int(data['bfs']['num_samples'])
    for i in range(num_samples):
      node = data['bfs'][str(i)]
      v = int(node['num_vertices'])
      e = int(node['num_edges'])
      ms = float(node['milliseconds'])
      x.append(v + e)
      y.append(ms)
  plt.figure(0)
  plt.scatter(x, y, s=.8)
  plt.title('Performance of BFS Algorithm (Dense Graph)')
  plt.xlabel('V + E')
  plt.ylabel('Milliseconds')
  plt.savefig('plot.bfs.png')

  # ----------------------------------------------------------------------------
  # plot the FF measurements (for sparse graphs)
  # ----------------------------------------------------------------------------
  x = []
  y = []
  with open('data.ff.sparse.json', 'r') as stream:
    data = json.load(stream)
    num_samples = int(data['ff']['sparse']['num_samples'])
    for i in range(num_samples):
      node = data['ff']['sparse'][str(i)]
      v = int(node['num_vertices'])
      e = int(node['num_edges'])
      ms = float(node['milliseconds'])
      x.append(v * e * e)
      y.append(ms)
  plt.figure(1)
  plt.scatter(x, y, s=.8)
  plt.title('Performance of Edmonds-Karp Algorithm (Sparse Graph)')
  plt.xlabel('V * E^2')
  plt.ylabel('Milliseconds')
  plt.savefig('plot.ff.sparse.png')

  # ----------------------------------------------------------------------------
  # plot the FF measurements (for dense graphs)
  # ----------------------------------------------------------------------------
  x = []
  y = []
  with open('data.ff.dense.json', 'r') as stream:
    data = json.load(stream)
    num_samples = int(data['ff']['dense']['num_samples'])
    for i in range(num_samples):
      node = data['ff']['dense'][str(i)]
      v = int(node['num_vertices'])
      e = int(node['num_edges'])
      ms = float(node['milliseconds'])
      x.append(v * e * e)
      y.append(ms)
  plt.figure(2)
  plt.scatter(x, y, s=2)
  plt.title('Performance of Edmonds-Karp Algorithm (Dense Graph)')
  plt.xlabel('V * E^2')
  plt.ylabel('Milliseconds')
  plt.savefig('plot.ff.dense.png')
