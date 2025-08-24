import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import numpy as np

df = pd.read_csv('delaunay_output.csv')

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

plt.figure(figsize=(12, 10))
triang = tri.Triangulation(points[:, 0], points[:, 1], triangles)

cmap = plt.get_cmap('tab20')
np.random.seed(42) 
face_colors = np.random.permutation(len(triangles)) % cmap.N


plt.tripcolor(triang, facecolors=face_colors, edgecolors='black', linewidth=1.2, cmap=cmap, alpha=0.75)

# # Plot points with shadow and labels
# plt.scatter(points[:, 0], points[:, 1], s=75, color='white', edgecolor='black', zorder=10)
# for i, (x, y) in enumerate(points):
#     plt.text(x, y, f'{i}', fontsize=9, ha='center', va='center', color='black', weight='bold', zorder=11)

plt.title("Delaunay Triangulation with Colored Triangles", fontsize=18, weight='bold')
plt.xlabel("X Coordinate", fontsize=14)
plt.ylabel("Y Coordinate", fontsize=14)
plt.grid(True, linestyle='--', alpha=0.5)
plt.gca().set_aspect('equal', adjustable='box')
plt.tight_layout()

plt.show()
