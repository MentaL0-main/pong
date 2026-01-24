# Pong  
*Simple C++/SDL3 implementation of classic Pong with an unbeatable bot. *

> ! [Screenshot](screenshots/screenshot.png)

---

## Overview

- Written in **C++** using **SDL3** and **SDL3_ttf**.  
- Mode: the player versus the perfect bot (his racket always follows the ball).

## Features

-Classic Pong: ball, two rackets, score.
- "Dishonest" bot: the bat racket is always at ball level on the Y-axis.  
- Text rendering via SDL3_ttf.

## Controls

| Key | Action |
|---------|------------|
| **W**   | Left racket up |
| **S**   | Left down |
| **O**   | Right paddle up (if Two Players mode |
| **L**   | Right Down Racquet (if Two Players mode |
---------------------------------------------------------

## Building

**Requirements:**
- C++17+
- SDL3, SDL3_ttf
- clang/g++
- CMake
- Make
- git

`bash
git clone https://github.com/mental0-main/pong.git
cd pong
mkdir build && cd build
cmake .. && make -j3
cp .. /assets/fonts/monojet.ttf .
./pong
`

