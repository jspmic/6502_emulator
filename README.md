# 🧠 6502 Emulator

A minimal yet robust emulator for the legendary 6502 microprocessor, written in C with a decentralized structure for clarity, testability, and modularity.

>     Built for hackers, low-level enthusiasts, and those who admire the elegance of the silicon heart behind the NES, Commodore 64, and Apple II.

# ✨ Features

- ✅ Accurate emulation of 6502 instructions, including addressing modes

- 🧩 Modular design with decentralized source layout

- 🧪 Per-instruction-mode tests (e.g., LDA_IM, STA_ZP)

- ⚙️ Compatible with GCC and Clang (see below for details)

# 📦 Project Structure

This project follows a clean separation of responsibilities to ease development and testing:

```
6502-emulator/
├── src/
│   ├── addr.c         # All addressing mode implementations (e.g., IM, ZP, ABS)
│   ├── proc.c         # Custom procedures (utilities, helpers, etc.)
│   ├── header.h       # Enums for opcodes and cycles, references to procedures from other files
│   └── instructions.c # Each instruction with its addressing mode (e.g., LDA_IM)
├── tests/             # Unit tests for each instruction + addressing mode combo
└── main.c             # Entry point (if applicable)
```

Each instruction is defined in conjunction with its addressing mode. This modular approach allows precise testing and easy extension of the emulator.
This project structure will change and all the header files will be in the `include/` directory. But this works for now!

# 🧪 Testing Philosophy

Each instruction and its addressing mode are tested individually — for example:

    LDA_IM — Load accumulator using Immediate addressing

    STA_ZP — Store accumulator using Zero Page addressing

    And so on for each valid opcode variant

This fine-grained approach ensures correctness and easier debugging.

# 🛠 Compiler Compatibility

The emulator relies on compiler-specific behavior to run initialization code automatically:

```C 
__attribute__((constructor)) void init(void) {
    // Initialization
}
```

✅ Supported:
- gcc
- clang

⚠️ Not supported by some compilers that don’t recognize `__attribute__((constructor))`. If you're not using GCC or Clang, this feature may not work as intended.

# 🚀 Getting Started
## Build
```bash
make
```
## Run
```bash
./build/main
```
## Run Tests
Assuming you have the `check` test framework:
```bash
make vtest
```
# 📚 Contributing
Contributions are welcome! Whether it's implementing new instructions, improving test coverage, or refactoring code — feel free to open a pull request.
# 📜 License
MIT — do whatever you want, but please don’t emulate poorly 😉
