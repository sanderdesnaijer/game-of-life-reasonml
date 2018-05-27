open Types;

let toString = ReasonReact.string;

/*
  Rules of Game of Life:
 Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
 Any live cell with more than three live neighbours dies, as if by overpopulation.
 Any live cell with two or three live neighbours lives on to the next generation.
 Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction */
let isAlive = (totalNeighbours: int, field: field) : field =>
  switch (field) {
  | Alive => totalNeighbours === 2 || totalNeighbours === 3 ? Alive : Dead
  | Dead => totalNeighbours === 3 ? Alive : Dead
  };

/* check future index, and handle if out of bounds   */
let getNextCell = (index: int, totalFields: int) : int => {
  let min = index == (-1);
  let max = index > totalFields - 1;
  if (min || max) {
    if (min) {
      totalFields - 1;
    } else {
      index - totalFields;
    };
  } else {
    index;
  };
};

let calcNeighbour = (row, col, totalRows, totalCols, grid: grid) : int => {
  let nextRow = getNextCell(row, totalRows);
  let nextCol = getNextCell(col, totalCols);
  List.nth(List.nth(grid, nextRow), nextCol) === Dead ? 0 : 1;
};

let calcNextState = (grid: grid) =>
  grid
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, value: field) => {
            let totalRows = List.length(grid);
            let totalCols = List.length(row);
            /* neighbours */
            let topLeft =
              calcNeighbour(
                rowIndex - 1,
                colIndex - 1,
                totalRows,
                totalCols,
                grid,
              );
            let topCenter =
              calcNeighbour(
                rowIndex - 1,
                colIndex,
                totalRows,
                totalCols,
                grid,
              );
            let topRight =
              calcNeighbour(
                rowIndex - 1,
                colIndex + 1,
                totalRows,
                totalCols,
                grid,
              );
            let centerLeft =
              calcNeighbour(
                rowIndex,
                colIndex - 1,
                totalRows,
                totalCols,
                grid,
              );
            let centerRight =
              calcNeighbour(
                rowIndex,
                colIndex + 1,
                totalRows,
                totalCols,
                grid,
              );
            let bottomLeft =
              calcNeighbour(
                rowIndex + 1,
                colIndex - 1,
                totalRows,
                totalCols,
                grid,
              );
            let bottomCenter =
              calcNeighbour(
                rowIndex + 1,
                colIndex,
                totalRows,
                totalCols,
                grid,
              );
            let bottomRight =
              calcNeighbour(
                rowIndex + 1,
                colIndex + 1,
                totalRows,
                totalCols,
                grid,
              );
            let totalNeighbours =
              topLeft
              + topCenter
              + topRight
              + centerLeft
              + centerRight
              + bottomLeft
              + bottomCenter
              + bottomRight;
            isAlive(totalNeighbours, value);
          })
     );