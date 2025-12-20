## Compilation

Compile via CMake or CLion's built-in CMake. The project uses **CXX_STANDARD 20**.

## Usage

The project uses ANSII codes. Make sure your terminal emulator has them enabled on Windows!

### Running:
```
./VoltageCalculator <path-to-input-file>
```

### Input file formatting


Every new line is a new instruction. There are two types of instructions: (S)ource and (R)esistor.

**Source**
```
S <node-index> <amount-of-current>
```
Where:
- node index is an int >= 1
- amount of current can be either an int or double with dot notation

**Resistor**
```
R <node-A-index> <node-B-index> <amount-of-resistance>
```
Where:
- node indexes are an ints >= 1
- amount of resistance can be either an int or double with dot notation
- this is a resistor between node A and node B

Do note that f the circuit doesn't make sense the results won't make sense either.
