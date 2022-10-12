# Tooling

## Compiler

Any GCC, Clang or MSVC compiler

## IDE: Visual Studio Code

- [Visual Studio Code](https://code.visualstudio.com/)

### VSCode Extensions

- Coding Tools Extension Pack (franneck94)
- C/C++ Extension Pack (franneck94)

## Steps from the video

0. Install all tools from the main course (including C/C++ Runner)
1. F1 (Command Palette) > Generate C++ Config Files (Minimal)
2. Copy settings below
3. Paste the copied settings into the **settings.json** file
4. Select folder in the blue status bar down below

### Extra settings (for local .vscode/settings.json file)

```json
  "C_Cpp_Runner.warnings": [
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wshadow",
    "-Wconversion",
    "-Woverflow",
    "-Wformat=2",
    "-Wsign-conversion"
  ],
  "C_Cpp_Runner.compilerArgs": [],
  "C_Cpp_Runner.includePaths": [],
  "C_Cpp_Runner.linkerArgs": [
      "-lm"
  ],
  "C_Cpp_Runner.cStandard": "c99",
  "C_Cpp_Runner.cppStandard": "c++17",
  "C_Cpp_Runner.excludeSearch": [
      "**/scripts/"
  ],
  "C_Cpp_Runner.enableWarnings": true,
  "C_Cpp_Runner.warningsAsError": false,
  "Workspace_Formatter.includePattern": [
    "*.h",
    "*.c",
    "**/*.h",
    "**/*.c"
  ]
```
