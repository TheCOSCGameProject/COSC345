![Codacy Badge](https://app.codacy.com/project/badge/Grade/416142ee7b9049e3b421bc0592f98b00)

###

![Coverage Badge](https://app.codacy.com/project/badge/Coverage/416142ee7b9049e3b421bc0592f98b00)

# Valeris - A Text-Based Dungeon Crawler

Welcome to **Valeris**, a modern remake of classic text-based dungeon crawler games, inspired by "choose your adventure" books and set in an immersive sci-fi world. This project is being developed by the team **Wang and Co.** at the University of Otago.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Development Workflow](#development-workflow)
- [Documentation](#documentation)
- [Contributing](#contributing)

## Introduction

Valeris is a text-based dungeon crawler that offers players a unique experience with dynamic characters, procedurally generated dungeons, and engaging mini-games. The game is built with a modular design, allowing for continuous integration and testing throughout the development process.

## Features

- **Dynamic Characters:** Interact with characters that can aid or hinder your progress.
- **Mini-Games:** Complete time-based challenges to earn rewards or face unique bosses.
- **Procedural Generation:** Each playthrough offers a new dungeon layout, characters, and challenges.
- **Immersive Story:** Uncover the secrets of your past through an engaging narrative.
- **Replayability:** With varying paths, characters, and challenges, no two runs are the same.

## Installation

### Prerequisites

- C++ Compiler (e.g., GCC, Clang)
- .yml for the Build
- Doxygen (for generating documentation)

### Clone the Repository and Run the Project

git clone https://github.com/TheCOSCGameProject/COSC345.git

##### Run Project

cd src && g++ -std=c++17 ../helper/*.cpp valeris.cpp -o valeris && ./valeris && cd ..

##### Run Tests

cd tests && g++ -std=c++17 -o run_tests minigames_test.cpp ../helper/*.cpp && ./run_tests && cd ..












## Usage
Once the game is started, you can navigate through the dungeons, interact with characters, and engage in mini-games using the keyboard. Each choice you make will affect the outcome of your journey. Once the game is run, the player will be represented with a main menu and the in-game actions can be utlised to play the game. The specific instructions to play the game, has been provided in the game play.








## Development Workflow

We follow an agile development process with tasks managed via Trello and real-time communication through Discord. Continuous integration (CI) is set up to ensure that every component integrates smoothly with the rest of the system. There are two .yml files located in the git Workflows folder that assist with the project build.


## Documentation

The codedocs.xyz has been used to generate Doxygen documentation. The documentation for this project can be found in the below webpage/website:
https://codedocs.xyz/TheCOSCGameProject/COSC345/

## Contributing

You are welcome to contribute to the project, by simply making Git push requests. We may review the push requests and make changes accordingly.


## The User Testing and the Feedback Collection

The Google Form has been created to collect feedback regarding the game/project. The Google Form can be found below:

https://forms.gle/UhVaeFyPmQwcN7Gx8

