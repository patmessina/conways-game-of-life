# Conways Game of Life

Rules [1]:

     1. Any live cell with fewer than two live neighbours dies, as if
        by underpopulation.
     2. Any live cell with two or three live neighbours lives on to
        the next generation.
     3. Any live cell with more than three live neighbours dies, as if
        by overpopulation.
     4. Any dead cell with exactly three live neighbours becomes a
        live cell, as if by reproduction.

Which can be condensed down to:
    
    1. Any live cell with two or three live neighbors survives.
    2. Any dead cell with three live neighbors becomes a live cell.
    3. All other live cells die in the next generation. Similarly, all
       other dead cells stay dead.

[1]: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
