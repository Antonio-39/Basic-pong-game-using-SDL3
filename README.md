# Basic Pong Game using SDL3

A classic **Pong** game built from scratch with the [SDL3](https://www.libsdl.org/) library. Play solo against a computer-controlled bot in a horizontal-paddle version of the arcade original. The project is a compact, easy-to-read example of a 2D game: paddle mechanics, ball collision physics, score tracking, and a fundamental game loop.

![Language](https://img.shields.io/badge/language-C%2FC%2B%2B-blue)
![SDL](https://img.shields.io/badge/SDL-3-orange)
![Platform](https://img.shields.io/badge/IDE-Visual%20Studio-purple)

<!-- Add a screenshot or GIF of the game here -->
<!-- ![Gameplay screenshot](docs/screenshot.png) -->

## Features

- **Single-player** mode: you versus a bot
- **Horizontal paddles**: move left and right with `A` and `D`
- Ball physics with collision detection (paddles and walls)
- Score tracking for you and the bot
- A basic game loop (input, update, render)
- 2D rendering with SDL3
- Quit or stop the game at any time with `Esc`

## Project Structure

```
Basic-pong-game-using-SDL3/
├── data/               # Game assets and resources
├── sdl_project/        # Source code and project files
└── sdl_solution.slnx   # Visual Studio solution
```

## Requirements

- [Visual Studio](https://visualstudio.microsoft.com/) 2022 or newer, with the **Desktop development with C++** workload (the `.slnx` solution format requires a recent version)
- [SDL3](https://github.com/libsdl-org/SDL/releases) development libraries
- Windows (the project is set up as a Visual Studio solution)

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Antonio-39/Basic-pong-game-using-SDL3.git
cd Basic-pong-game-using-SDL3
```

### 2. Set up SDL3

If SDL3 is not already configured in the project, download the Visual C++ development package from the [SDL releases page](https://github.com/libsdl-org/SDL/releases), extract it, and make sure the project points to it:

1. Open the project's **Properties**.
2. Under **C/C++ → General → Additional Include Directories**, add the SDL3 `include` folder.
3. Under **Linker → General → Additional Library Directories**, add the SDL3 `lib` folder (match your x64/x86 platform).
4. Under **Linker → Input → Additional Dependencies**, add `SDL3.lib`.
5. Copy `SDL3.dll` next to the built executable.

### 3. Build and run

1. Open `sdl_solution.slnx` in Visual Studio.
2. Select a configuration (`Debug` or `Release`) and platform (`x64`).
3. Press **F5** (or **Ctrl+F5**) to build and run.

## How to Play

You control the paddle at the bottom of the screen and play against a bot that controls the opposing paddle at the top. Because the paddles are horizontal, you move them **left and right** to keep the ball in play. Bounce the ball past the bot's paddle to score, and don't let it get past yours.

### Controls

| Action              | Key   |
| ------------------- | ----- |
| Move paddle left    | `A`   |
| Move paddle right   | `D`   |
| Stop / quit the game | `Esc` |

## How It Works

The game runs on a standard loop:

1. **Handle input**: poll SDL events and read the keyboard state (`A`, `D`, `Esc`).
2. **Update**: move your paddle, the bot's paddle, and the ball; detect collisions; and update the score when the ball passes a paddle.
3. **Render**: clear the screen, draw the paddles, ball, and score, then present the frame.

The opponent is a computer-controlled bot that moves its paddle automatically to track the ball.

## Possible Improvements

- Adjustable bot difficulty
- Two-player local mode
- Sound effects and background music
- Ball speed increase over time
- Pause menu and game-over screen
- Cross-platform build with CMake

## Contributing

Contributions, issues, and suggestions are welcome. Feel free to fork the repository and open a pull request.


## Acknowledgments

- [SDL3](https://www.libsdl.org/) for the cross-platform multimedia library
- The original *Pong* by Atari (1972) for the inspiration
