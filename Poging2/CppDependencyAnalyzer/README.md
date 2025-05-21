# C++ Dependency Analyzer

This tool analyzes C++ source code using Clang's LibTooling and generates a `.dsi` XML file of software dependencies.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./CppDependencyAnalyzer path/to/source/*.cpp --output output.dsi
```

Output is a DSM-compatible `.dsi` file using absolute paths.