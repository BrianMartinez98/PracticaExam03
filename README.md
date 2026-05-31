# 42 Exam Rank 03 — Practice Solutions

Practice repository for **42 Exam Rank 03**. The repo is organized by level and by exercise, keeping the original subject text next to each solution.

## Included exercises

| Level | Exercise | Expected deliverable |
|---|---|---|
| lvl1 | `broken_gnl` | `get_next_line.c`, `get_next_line.h` |
| lvl1 | `filter` | `filter.c` |
| lvl1 | `ft_scanf` | `ft_scanf.c` |
| lvl2 | `n_queens` | `n_queens.c` |
| lvl2 | `permutation` | `permutation.c` |
| lvl2 | `powerset` | `powerset.c` |
| lvl2 | `rip` | `rip.c` |

## Compile check

```bash
./scripts/check.sh
```

The script compiles all C files with:

```bash
gcc -Wall -Wextra -Werror -std=c99 -D BUFFER_SIZE=42
```

## Notes

- `broken_gnl` has been cleaned to expose the expected `get_next_line.c` / `get_next_line.h` files only.
- Standalone exercises with `main` can be compiled and tested directly from their folders.
