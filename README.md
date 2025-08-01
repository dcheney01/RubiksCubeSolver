# Rubik's Cube Solving Robot

A high-performance Rubik's Cube solving robot combining advanced algorithms, computer vision, and precision mechanical control to achieve competitive solving times.

## Performance Achievements
- **Record Time**: 7.82 second solve on hardware
- **Consistent Performance**: Reliable sub-10 second solves
- **[Watch Demo Video](https://youtu.be/ljCj2J3jsT0)**

### Hardware Components
- **Dual Arduino Control**: Two synchronized Arduino boards for 6-face manipulation
  - `DLF_RubikSolver_Arduino/` - Controls Down, Left, Front faces
  - `URB_RubikSolver_Arduino/` - Controls Up, Right, Back faces
- **Stepper Motors**: Precise 50-step movements for 90° rotations
- **Mechanical Framework**: Custom-designed cube gripping and rotation mechanism
- **Computer Vision**: Camera system for cube state detection

### Software Components
- **Cube State Recognition**: Computer vision algorithms for face detection and color identification
- **Solving Algorithm**: Implementation of efficient cube solving methods (likely CFOP or Kociemba)
- **Motion Planning**: Optimized move sequences and timing coordination
- **Arduino Communication**: Serial communication protocol for move execution

### Control Interface
- Real-time move execution via serial commands
- Standardized cube notation (F, B, L, R, U, D with modifiers)
- Error handling and position verification
- Synchronized dual-controller operation

## Project Structure

- `DLF_RubikSolver_Arduino/` - Arduino code for Down/Left/Front face control
- `URB_RubikSolver_Arduino/` - Arduino code for Up/Right/Back face control  
- `RubiksCubeGUIVideo/` - Demonstration videos and GUI components

This project showcases the intersection of algorithms, robotics, and engineering to solve one of the world's most famous puzzles at competitive speeds.
