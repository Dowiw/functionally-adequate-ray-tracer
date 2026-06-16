# functionally-adequate-ray-tracer
F.A.R.T modelled after miniRT

## Getting Started

### Building the Project
To compile the project, run:
```bash
make
```

### Running Tests
To build and run the unit tests:
```bash
make test
```

### Cleaning Up
- To remove compiled object files:
  ```bash
  make clean
  ```
- To remove all compiled object files, libraries, and binaries:
  ```bash
  make fclean
  ```
- To perform a clean build:
  ```bash
  make re
  ```

### Running under Valgrind
To compile and check for memory leaks:
```bash
make valgrind
```

---

## Clangd tracking (Compile Commands)

To update the `compile_commands.json` database for `clangd` (LSP tracking), you should run `bear` with a clean build. Since `bear` intercepts compilation commands as they run, any files that are already compiled will not be tracked.

Run the following command to generate/update the compilation database:
```bash
make clean && bear -- make
# Or simply:
bear -- make re -o .configs/compile_commands.json
```
