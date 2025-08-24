import matplotlib.pyplot as plt
import pandas as pd

df =  pd.read_csv("coordinates.csv")
df['x'], df['y'] = df['y'], df['x']
num_samples = int(input("Enter the number of points to sample for plotting: "))

df_sampled = df.sample(n=num_samples)
df_sampled.to_csv('sampled_points.csv', index=False)
plt.scatter(df_sampled['x'], df_sampled['y'], s=1)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Scatter plot of coordinates')
plt.grid(True)
plt.show()
