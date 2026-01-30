# A-Star

A* pathfinding algorithm with SDL2 visualization.

## Overview

An interactive implementation of the A* pathfinding algorithm with real-time visualization using SDL2. Based on OneLoneCoder's tutorial, this project lets you create obstacles and watch the algorithm find optimal paths.

## Features

- Interactive node grid with clickable obstacles
- Adjustable start and end positions (Shift+click / Ctrl+click)
- Visual feedback showing searched nodes and final path
- Handles unreachable destinations gracefully

## Prerequisites

- macOS (tested on Catalina 10.15.4+)
- SDL2 (`brew install sdl2`)
- CMake 3.17+
- C++17 compiler

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./build/a-star/a-star
```

### Controls

| Action | Control |
|--------|---------|
| Add obstacle | Click on node |
| Move start | Shift + Click |
| Move end | Ctrl + Click |

## Tests

Tests are not yet implemented.

## License

CC0 1.0 Universal - see [LICENSE](LICENSE)

## Author

**Rich Nistuk** - [rnistuk](https://github.com/rnistuk)

## Acknowledgments

- [javidx9 OneLoneCoder](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA) - A* tutorial video
- [A* on Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)
