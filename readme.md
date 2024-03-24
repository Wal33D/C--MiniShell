# C--MiniShell 🐚

C--MiniShell is a minimal shell implementation in C, designed by Waleed Gudah 🧑‍💻. It mimics some of the basic functionalities of a traditional Unix shell, including command execution, environment variable expansion, and basic I/O redirection.

## Features ✨

- Execute system commands 💻
- I/O redirection (>, >>, <) 📂
- Background process execution (&) 🚀
- Environment variable support 🌎
- Internal commands:
  - `cd`: Change the current working directory 📁
  - `echo`: Print text to the standard output 📢
  - `exit`: Exit the shell 🚪

## Getting Started 🚶‍♂️

### Prerequisites 📋

Ensure you have GCC (GNU Compiler Collection) installed on your system to compile the source code. You can check if GCC is installed by running:

```bash
gcc --version
```

### Installation 🔧

1. Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/C--MiniShell.git
```

2. Navigate to the cloned directory:

```bash
cd C--MiniShell
```

3. Compile the `shell.c` file:

```bash
gcc shell.c -o minishell
```

4. Run the shell:

```bash
./minishell
```

## Usage 📖

After launching `C--MiniShell`, you will be greeted with a prompt `Waleed's Shell:`. You can start typing commands just like you would in any other shell. Here are some examples:

- Running a system command:

```bash
ls -l
```

- Changing directories:

```bash
cd /path/to/directory
```

- Using I/O redirection:

```bash
echo "Hello, World!" > hello.txt
```

- Running a command in the background:

```bash
sleep 10 &
```

## Contributing 🤝

Contributions are welcome! If you have suggestions for improving C--MiniShell, please open an issue or submit a pull request.

## License 📄

This project is licensed under the MIT License - see the LICENSE file for details.
