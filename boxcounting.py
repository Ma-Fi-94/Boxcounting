# Lib imports
import numpy as np
import pandas as pd

# Load numerical solution of the system
res = pd.read_csv("result_t1000_dt1e-5.csv", header=None)
res.columns = ["t", "x", "y", "z"]

# Reference point for uniquely identifying every grid box
xmin = -50
ymin = -50
zmin = -50


# The different grid sizes we try
epsilons = [1, 0.999, 0.99, 0.9, 0.8, 0.7, 0.6, 0.5,
            0.1, 0.05, 0.01, 0.005, 0.001, 0.0005, 0.0001, 5e-05]

# Store results in here
nb_hits = []


for epsilon in epsilons:
    
    # For every point, find the coordinates of the grid box it falls in.
    res["i_x"] = (res.x - xmin) // epsilon
    res["i_y"] = (res.y - ymin) // epsilon
    res["i_z"] = (res.z - zmin) // epsilon
    
    # Store all "touched" boxes in a set, so that every touched box
    # is saved only once.
    hits = set()
    
    # Add all "touched" boxes as coordinate-touples to the set.
    # We need to do this manually in a for loop, because
    # generating a column of coordinate-touples first
    # required too much memory.
    for i_x,i_y,i_z in zip(res.i_x, res.i_y, res.i_z):
        hits.add((i_x, i_y, i_z))
    
    # Progress meter for the impatient ;)
    print(epsilon, len(hits))
    
    # Save count of current grid size
    nb_hits.append(len(hits))


# Print the final list of counts. 
print(nb_hits)

