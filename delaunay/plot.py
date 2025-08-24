import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import numpy as np
from matplotlib.animation import FuncAnimation, PillowWriter

df = pd.read_csv('path_to_csv_on_1185_trios') #we are not running on all the trios as computing them is too much computationally expensive 

points = []
triangles = []

point_index = {}
idx = 0

for _, row in df.iterrows():
    tri_pts = [(row['x1'], row['y1']), (row['x2'], row['y2']), (row['x3'], row['y3'])]
    tri_indices = []
    for p in tri_pts:
        if p not in point_index:
            point_index[p] = idx
            points.append(p)
            idx += 1
        tri_indices.append(point_index[p])
    triangles.append(tri_indices)

points = np.array(points)
triangles = np.array(triangles)

def side_length(p1, p2):
    return np.linalg.norm(p1 - p2)

max_length_values = np.linspace(10, 200, 30)  

fig, ax = plt.subplots(figsize=(10, 8))
cmap = plt.get_cmap('tab20')
np.random.seed(42)

def update(frame):
    ax.clear()
    limit = max_length_values[frame]

    filtered_triangles = []
    for tri_indices in triangles:
        p1, p2, p3 = points[tri_indices]
        lengths = [side_length(p1, p2), side_length(p2, p3), side_length(p3, p1)]
        if all(l <= limit for l in lengths):
            filtered_triangles.append(tri_indices)

    if len(filtered_triangles) == 0:
        return

    triang = tri.Triangulation(points[:, 0], points[:, 1], np.array(filtered_triangles))
    face_colors = np.random.permutation(len(filtered_triangles)) % cmap.N

    ax.tripcolor(triang, facecolors=face_colors, edgecolors='black', linewidth=1.0, cmap=cmap, alpha=0.8)
    ax.set_title(f"Side Length Filtering (limit = {limit:.1f})", fontsize=16, weight='bold')
    ax.set_aspect('equal', adjustable='box')
    ax.axis("off")

ani = FuncAnimation(fig, update, frames=len(max_length_values), interval=500, repeat=True)


writer = PillowWriter(fps=2)  
ani.save("side_length_simulation.gif", writer=writer)

plt.show()
