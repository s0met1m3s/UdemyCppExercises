import copy
import os
import json
from typing import TypedDict

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


DATA_FILENAME = "lane_data.json"
GIF_FILENAME = "example.gif"

DATA_PATH = os.path.join(os.path.dirname(os.path.dirname(__file__)), "data")
DATA_FILEPATH = os.path.join(DATA_PATH, DATA_FILENAME)
GIF_FILEPATH = os.path.join(DATA_PATH, GIF_FILENAME)


class Poly2nd(TypedDict):
    x2: float
    x1: float
    x0: float


POLY = Poly2nd(x2=100.0, x1=50.0, x0=0.0)

fig, ax = plt.subplots()
p2 = POLY


def poly_2nd_values(x: np.ndarray, poly: Poly2nd) -> np.ndarray:
    y = (poly['x2']*x)**2 + (poly['x1']*x)**1 + poly['x0']
    return y


def pertubation_x2(p2: Poly2nd):
    if p2['x2'] > 40.0 and p2['x2'] < 60.0:
        eps = np.random.uniform(low=-20.0, high=20.0)
    elif p2['x2'] > 100.0:
        eps = np.random.uniform(low=-15.0, high=2.0)
    elif p2['x2'] < 0.0:
        eps = np.random.uniform(low=-2.0, high=15.0)
    else:
        eps = np.random.uniform(low=-10.0, high=10.0)
    return eps


def update(frame: int):
    x = np.linspace(start=0.0, stop=100.0, num=1000)
    ax.clear()
    plt.xlim(-100.0, 100.0)
    plt.ylim(-5.0, 5.0)
    plt.yticks([-4.5, -1.5, 0.0, 1.5, 4.5])
    plt.hlines(y=-4.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=-1.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=1.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=4.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.gca().invert_yaxis()
    p2['x2'] += pertubation_x2(p2)
    y = poly_2nd_values(x, p2)
    x2 = round(p2['x2'])
    x1 = round(p2['x1'])
    x0 = round(p2['x0'])
    title_str = (
        f'It: {frame} - p(x) = {x2}$x^2$ + {x1}$x^1$ + {x0}'
    )
    plt.title(title_str)
    plt.plot(y, x - 4.5, color="black")
    plt.plot(y, x - 1.5, color="black")
    plt.plot(y, x + 1.5, color="black")
    plt.plot(y, x + 4.5, color="black")
    return ax


def generate_data(num_frames: int):
    lane_data = {i: Poly2nd() for i in range(num_frames)}
    p2 = POLY
    for i in range(num_frames):
        p2['x2'] += pertubation_x2(p2)
        p2['x2'] = round(p2['x2'], 4)
        p2['x1'] = round(p2['x1'], 4)
        p2['x0'] = round(p2['x0'], 4)
        lane_data[i] = copy.deepcopy(p2)
    return lane_data


def animation():
    animation = FuncAnimation(fig, update, frames=200)
    animation.save(GIF_FILEPATH)


def main() -> int:
    animation()
    # lane_data = generate_data(num_frames=1000)
    # with open(DATA_FILEPATH, "w") as file_object:
    #     json.dump(lane_data, file_object)

    return 0


if __name__ == "__main__":
    main()
