# Link to my github repository

https://github.com/Goncalo-Alexandre-Viveiros-Guilherme/Prog4-Exam-MsPacMan


# Component-Based Architecture

The engine uses a component-based architecture, allowing game objects to be composed of reusable and modular components. This approach improves code maintainability and flexibility, making it easy to add or modify behaviors without altering core object logic.

# Time Management

A dedicated Time class manages delta time, total elapsed time, and fixed time steps. This ensures consistent game logic updates and smooth rendering, regardless of frame rate fluctuations.

# Modern C++ Standards

The codebase is written using C++20 features, leveraging modern language constructs for improved safety, performance, and expressiveness.

# Resource Management
A centralized resource manager handles loading and caching of assets such as textures and sounds. This reduces redundant loading and improves performance by reusing resources across the engine.

# Scene and State Management
Scenes and game states are managed through dedicated managers, enabling clean transitions and separation of concerns between different parts of the game (e.g., menus, gameplay, pause screens).

# Third-Party Integrations
The engine integrates with third-party libraries such as Steamworks and Dear ImGui, providing features like Steam integration and in-game debugging tools.