# safe-stack

A dynamic stack in C with built-in memory corruption detection and Unit-tests

## How protection works

Each stack instance is protected by two mechanisms:

**Canaries** are random values placed at the boundaries of the stack structure and data array. If anything writes outside its bounds, the canary changes and the corruption is detected. Randomized at runtime so the value can't be found by inspecting the binary.

**Hash** detects corruption of the stack contents. Updated in O(1) on every push and pop. The hash base is randomized per instance, so the value can't be found.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run tests

```bash
cd build
./test-stack
```

## Build doxygen docs

```bash
mkdir build && cd build
cmake ..
make docs
```

## API

| Function | Description |
|---|---|
| `init(capacity)` | Allocate a new stack. Returns NULL on failure. |
| `push(stack, value)` | Push a value. Resizes automatically. |
| `pop(stack)` | Remove the top element. |
| `top(stack, &value)` | Read the top element without removing it. |
| `size(stack, &size)` | Get the number of elements. |
| `empty(stack)` | Returns 1 if empty, 0 if not, -1 if error. |
| `clear(stack)` | Free all memory. |
| `check_canaries(stack, &out)` | O(1) canaries integrity check. |
| `check_hash(stack, &out)` | O(n) full hash integrity check. |
| `print_dump(stack)` | Print full stack info in stderr. |

The element type is `typedef int type` in `stack.h`.