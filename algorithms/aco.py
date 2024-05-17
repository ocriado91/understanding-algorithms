#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import os

import imageio

def plot_pheromone_matrix(pheromone_matrix: np.array,
                          filename: str,
                          title="Pheromone Matrix") -> None:
    '''
    Plot the pheromone matrix
    '''

    fig, ax = plt.subplots()
    plt.imshow(pheromone_matrix,
               cmap="GnBu")

    # Create text annotations with 1 decimals
    round_matrix = np.around(pheromone_matrix, decimals=1)
    for idx, row in enumerate(round_matrix):
        for idy, item in enumerate(row):
            ax.text(idy, idx, item,
                    ha="center", va="center")

    # Add title
    ax.set_title(title)
    plt.savefig(filename)

def plot_path(path: list,
              points: list,
              filename=str,
              title="Path") -> None:
    '''
    Plot the entire path
    '''

    fig, ax = plt.subplots()

    for point in points:
        ax.scatter(x=point[0], y=point[1], color="red")


    for idx in range(len(path)-1):
        current_point = points[path[idx]]
        next_point = points[path[idx+1]]
        print(f"Plotting journey between {current_point} and {next_point}")
        ax.plot([current_point[0], next_point[0]],
                [current_point[1], next_point[1]],
                color="green")

    ax.set_title(title)
    plt.savefig(filename)


def animate_plot(folder: str,
                 filename: str):
    '''
    Create an animated GIF in based of inputs found
    into folder.

    Parameters
        - folder: Folder to search plots to generate the GIF.
        - filename: GIF file name.
    '''

    images = []
    files = os.listdir(folder)
    files.sort()
    for file in files:
        # Open file with imageio imread to generate the animation
        file = os.path.join(folder, file)
        print(f"Adding frame {file}")
        images.append(imageio.imread(file))

    # Create GIF file
    imageio.mimsave(filename, images, duration=0.05)



def distance(point1, point2):
    '''
    Compute the distance between two points
    '''
    return np.sqrt(np.sum((point1 - point2)**2))


def ant_colony_optimization(points: np.array,
                            ants: int,
                            alpha: np.array,
                            iterations: int = 5):
    '''
    Implementation of ant colony optimization
    '''
    print(f"Starting points:\n {points}")
    pheromone = np.ones((len(points), len(points)))
    best_path_length = np.inf
    best_path = []

    for iteration in range(iterations):
        print(f"Starting iteration {iteration}")
        print(f"Current pheromones:\n {pheromone}")

        # Store all paths and lengths into lists
        path_lengths = []
        paths = []

        # Each ant becomes its journey
        for ant in range(ants):
            # Initialize the visited point list by current ant
            visited = [False] * len(points)

            # # Determine randomly the first point
            # current_point = np.random.randint(len(points))
            # Fix first point to 0
            current_point = 0

            # And add first point to list of visited points
            visited[current_point] = True

            # Initialize path length
            path_length = 0

            # Initialize a list to store the point traveled by current ant
            path = [current_point]

            print(f"ANT {ant} starting its journey in {current_point}...")

            # Each ant try to visit all points
            while False in visited:
                # Extract the current unvisited points by ant
                unvisited = [idx for idx, x in enumerate(visited) if not x]

                # Compute the probability of go to another unvisited point from current
                # point based into their distance
                probabilities = [0] * len(unvisited)

                for idx, unvisited_point in enumerate(unvisited):

                    # Compute distance betweeen current point and unvisited point
                    _distance = distance(points[current_point],
                                         points[unvisited_point])

                    # Compute probability as inverse of distance
                    probability = pheromone[current_point, unvisited_point] /_distance

                    # Apply alpha factor to probability
                    probability *= alpha[idx]

                    # Assign probability to probability list
                    probabilities[idx] = probability

                # Normalize probability
                probabilities /= np.sum(probabilities)
                # Select next point based on probabilities
                next_point = np.random.choice(unvisited,
                                            p=probabilities)

                # Add next point to path list
                path.append(next_point)

                # Increment path length between current point and next point
                # and append it to list of path lengths
                path_length += distance(points[current_point],
                                        points[next_point])

                # Add the next point to list of visited points
                visited[next_point] = True

                # Move to the next point
                current_point = next_point

            # Add current path and its length to lists
            paths.append(path)
            path_lengths.append(path_length)

            if path_length < best_path_length:
                best_path_length = path_length
                best_path = path

            print(f"Path traveled by ant {ant} of length {path_length}: {path}")

        # Update pheromone matrix with the information recollected by ants
        # into the current iteration
        for path, path_length in zip(paths, path_lengths):
            for idx in range(len(path)-1):
                pheromone[path[idx], path[idx+1]] += 1/path_length

        iteration_str = str(iteration).zfill(4)

        # Plot iteration best path
        plot_name = f"path_{iteration_str}"
        title = f"Best path ({best_path_length}) at iteration = {iteration}"
        plot_path(best_path,
                  points,
                  filename=f"plots/paths/{plot_name}.png",
                  title=title)

        # Plot pheromone matrix
        print(f"Pheromone matrix:\n {pheromone}")
        plot_name = f"pm_{iteration_str}"
        title = f"Pheromone Matrix at iteration = {iteration}"
        plot_pheromone_matrix(pheromone_matrix=pheromone,
                              filename=f"plots/pheromone/{plot_name}.png",
                              title=title)
    # Report final results
    print(f"Best path = {best_path} with length = {best_path_length}")
    animate_plot("plots/pheromone",
                 filename="pheromone.gif")
    animate_plot("plots/paths/",
                 filename="paths.gif")



def main():
    '''
    Main function
    '''
    N_ANTS = 10
    N_ITERATIONS = 100

    points =  [
        [0.62005352, 0.7051838 ],
        [0.38730963, 0.22982921],
        [0.72145019, 0.34813559],
        [0.69624767, 0.74909976],
        [0.21898804, 0.1450391 ],
        [0.91504129, 0.91483308],
        [0.43181647, 0.09180593],
        [0.94606053, 0.5478663 ],
        [0.27562911, 0.68909373],
        [0.10469777, 0.49994994],
 ]
    points = np.array(points)
    alpha = np.array([1]*len(points))
    ant_colony_optimization(points=points,
                            ants=N_ANTS,
                            iterations=N_ITERATIONS,
                            alpha=alpha)

if __name__ == '__main__':
    main()
