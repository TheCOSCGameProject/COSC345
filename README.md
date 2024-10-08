![Codacy Badge](https://app.codacy.com/project/badge/Grade/416142ee7b9049e3b421bc0592f98b00)

###

![Coverage Badge](https://app.codacy.com/project/badge/Coverage/416142ee7b9049e3b421bc0592f98b00)

# Valeris - A Text-Based Dungeon Crawler

Welcome to **Valeris**, a modern remake of classic text-based dungeon crawler games, inspired by "choose your adventure" books and set in an immersive sci-fi world. This project is being developed by the team **Wang and Co.** at the University of Otago.

## Table of Contents

- [Valeris - A Text-Based Dungeon Crawler](#valeris---a-text-based-dungeon-crawler)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Clone the Repository and Run the Project](#clone-the-repository-and-run-the-project)
        - [Run Project](#run-project)
        - [Run Tests](#run-tests)
  - [Usage](#usage)
  - [Development Workflow](#development-workflow)
  - [Documentation](#documentation)
  - [Tutorial Videos](#tutorial-videos)
  - [Report Bugs](#report-bugs)
  - [Contributing](#contributing)
  - [The User Testing and the Feedback Collection](#the-user-testing-and-the-feedback-collection)

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

Codecov - https://app.codecov.io/gh/TheCOSCGameProject/COSC345/tree/main/helper
Codacy - https://app.codacy.com/gh/TheCOSCGameProject/COSC345/dashboard


## Documentation

The codedocs.xyz has been used to generate Doxygen documentation. The documentation for this project can be found in the below webpage/website:
https://codedocs.xyz/TheCOSCGameProject/COSC345/

## Tutorial Videos

Tutorial on interacting with rooms with locked safes inside on them.
[![Valeris Game Tutorial #1](https://img.youtube.com/vi/NFQdjaoEKqc/0.jpg)](https://www.youtube.com/watch?v=NFQdjaoEKqc)

A tutorial on how to interact with the gambling rooms and play the games.
[![Valeris Game Tutorial #2](https://img.youtube.com/vi/cv9LjFNY92s/0.jpg)](https://www.youtube.com/watch?v=cv9LjFNY92s)

A Tutorial on how to fight enemies in rooms and how to view inventory.
[![Valeris Game Tutorial #3](https://img.youtube.com/vi/U_HqfbN5TFg/0.jpg)](https://www.youtube.com/watch?v=U_HqfbN5TFg)

## Report Bugs
If you encounter any bugs or issues while using the project, please feel free to report them:

1. **Submit an Issue**: You can report bugs by opening an issue on our [Issue Tracker](https://github.com/TheCOSCGameProject/COSC345/issues). Please provide detailed information about the bug, including:
   - Steps to reproduce the bug.
   - Expected and actual behavior.
   - Any relevant screenshots or logs.

2. **Send an Email**: Alternatively, you can send an email to [bug-report@gmail.com](mailto:cjmt97@gmail.com) with the same information.

We appreciate your feedback and will do our best to address the issues as soon as possible!


## Contributing

You are welcome to contribute to the project, by simply making Git push requests. We may review the push requests and make changes accordingly.


## The User Testing and the Feedback Collection

The Google Form has been created to collect feedback regarding the game/project. The Google Form can be found below:

https://forms.gle/UhVaeFyPmQwcN7Gx8

