# 🐍 Snake Game - Modern Console Edition

Welcome to the **Snake Game**! This is a modern twist on the classic game we all know and love, designed to be played in your console. With dynamic gameplay, smooth controls, and a touch of nostalgia, it's time to relive your childhood in code!

## 🎮 How to Play

- **Move the Snake**: Use the arrow keys (`←`, `↑`, `→`, `↓`) to navigate your snake.
- **Eat the Fruit**: Munch on the delicious fruits (`🍎` emoji coming soon!) to grow your tail and rack up points.
- **Avoid Collisions**: Don't run into your own tail or the walls, or it's game over!
- **Pause/Resume**: Thinking of adding this feature 😉.

## 🧠 Features

- **Dynamic Gameplay**: Your snake grows with each fruit, making the game more challenging and fun.
- **Threaded Input**: Smooth, responsive controls ensure you never miss a beat.
- **Wrap-Around Mode**: The snake can wrap around the edges of the screen (Wall ON/OFF feature coming soon).
- **Score Tracking**: Keep an eye on your score and aim for the high score (SQL database integration planned).
- **Hidden Caret**: We’ve hidden the cursor to give you a more immersive experience.
- **Multithreading Magic**: Input and game logic run on separate threads for maximum performance.

## 🚀 Getting Started

### Prerequisites

- A Windows machine with a C++ compiler like **MinGW** or **Microsoft Visual C++ Compiler**.
- Basic knowledge of how to compile and run C++ code.

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/umaryaksambi/TheSnakeGame.git
   ```
2. **Navigate to the directory**:
   ```bash
   cd TheSnakeGame
   ```
3. **Compile the code**:
   ```bash
   g++ -o TheSnakeGame TheSnakeGame.cpp -lpthread
   ```
4. **Run the game**:
   ```bash
   ./TheSnakeGame
   ```

## 🌟 What's Next?

- **Emoji Integration**: Replace the boring `F` with a juicy `🍎` emoji.
- **Big Fruit**: Occasionally, a bigger fruit that gives more points will spawn.
- **Walls Mode**: Option to toggle walls ON/OFF for added difficulty.
- **High Score Database**: Connect to a SQL database to save and retrieve high scores.
- **Speed Adjustment**: Increase the game speed as your score increases.

## 🛠️ Built With

- **C++** - The powerful programming language that runs this game.
- **Windows API** - Used to manipulate the console window for a smooth gaming experience.

## 🤝 Contributing

Contributions are welcome! If you have ideas to make this game more fun, feel free to fork the repository and submit a pull request.

## 🐛 Bug Reports & Feature Requests

If you encounter any bugs or have cool ideas for new features, please open an issue in the [Issues section](https://github.com/yourusername/snake-game/issues).

## 💻 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Let's get nostalgic and code on! 🚀
