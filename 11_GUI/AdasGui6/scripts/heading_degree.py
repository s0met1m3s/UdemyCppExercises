import numpy as np


def main() -> int:
    v_long = (0.5) * 3.0
    v_lat = (np.sqrt(3) / 2) * 3.0
    print(f"v_long: {v_long}")
    print(f"v_lat: {v_lat}")

    a2 = np.arctan2(v_long, v_lat)
    print(f"arctan2: {a2}")
    deg = (a2 / np.pi) * 360.0
    print(f"deg: {deg}")
    return 0


if __name__ == "__main__":
    main()
