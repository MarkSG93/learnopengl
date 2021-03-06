# LearnOpenGL

This is a repo I use to log all of the exercises / tutorials I follow on https://learnopengl.com.

I may make different tags to show the history of the repo as I follow the tutorials, or I might make separate folders. Not entirely sure yet, but if you're looking for examples you'll be able to tell in the `tags` of the repo or by the folder structure.

**N.B** This is my own source code, so it will be a different layout and structure. I found at the end of the shaders section the code was rather messy so I tidied up the `Shader` class. All of the loading code was directly in the constructor 😱 

## OpenGL Version
In `main.cpp` it's hard coded to 4.1, so you'll probably want to change that based on your system/requirements.

## Running the project
This project was setup on Mac OS X with the CLion IDE. I've included the glfw-3.3.2 and glad dependencies in the repo so it should hopefully build with CMake straight away.

## Getting Help
I am a complete n00b when it comes to OpenGL. I'm doing this because 
1. I'm interested in graphics programming
2. I've got a lot of time in lockdown

That being said, if you want help feel free to reach out, I just can't guarantee I can help.

## Tutorial Progress
- [ ] Getting Started
    - [x] Creating a window
    - [x] Hello window
    - [x] Hello Triangle
    - [x] Shaders
    - [x] Textures
    - [x] Transformations
    - [x] Coordinate Systems
    - [ ] Camera
    - [ ] Review 
- [ ] Lighting
- [ ] Model Loading
- [ ] Advanced OpenGL 😱
- [ ] Advanced Lighting
- [ ] PBR 

## Pro Tip
Don't forget to increase your stride when you add more vertex attributes to your vertices array! Spent an hour debugging this 😬
