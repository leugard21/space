# Space

**Disk Usage Visual Analyzer**

`space` is a lightweight command-line tool written in C++ for analyzing and visualizing disk usage. It provides a quick breakdown of directory sizes with ASCII bar visualizations and tree views.

## Features

- **Visual Breakdown**: See disk usage with ASCII bars and percentage.
- **Tree View**: Explore directory structure with depth control.
- **Colorized Output**: Highlighting directories and large files for better visibility.
- **Sorting**: Support for sorting entries by size or name.
- **Filtering**: Filter by minimum size or top N entries.
- **JSON Output**: Export data for further processing.
- **Fast**: Built with modern C++ and `std::filesystem`.

## Installation

### Arch Linux (AUR)

You can install `space` from the AUR using your favorite helper:

```bash
yay -S space
```

### From Source

```bash
mkdir build && cd build
cmake ..
make
sudo make install
```

## Usage

```bash
space [path] [options]
```

### Options

- `[path]`: Directory to analyze (default: current directory).
- `--top N`: Show only the top N largest entries.
- `--min-size <size>`: Filter entries smaller than `<size>` (e.g., `100M`, `1G`).
- `--tree`: Display a tree view of the directory structure.
- `--max-depth N`: Limit traversal depth.
- `--sort <type>`: Sort entries by `size` or `name` (default: `size`).
- `--no-color`: Disable colorized output.
- `--json`: Output result in JSON format.
- `--version`: Show version information.
- `--help`: Show help (WIP).

## License

This project is licensed under the [MIT License](LICENSE).
