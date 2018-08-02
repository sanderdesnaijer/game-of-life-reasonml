open Types;

let toString = ReasonReact.string;

/*
  Rules of Game of Life:
  Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
  Any live cell with more than three live neighbours dies, as if by overpopulation.
  Any live cell with two or three live neighbours lives on to the next generation.
  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
 */
let isAlive = (totalNeighbours: int, field: field) : field =>
  switch (field) {
  | Alive => totalNeighbours === 2 || totalNeighbours === 3 ? Alive : Dead
  | Dead => totalNeighbours === 3 ? Alive : Dead
  };

/* check future index, and handle if out of bounds   */
let getNextCell = (index: int, totalFields: int) : int => {
  let min = index === (-1);
  let max = index > totalFields - 1;
  if (min) {
    totalFields - 1;
  } else if (max) {
    index - totalFields;
  } else {
    index;
  };
};

let getNeighbour = (row: int, col: int, grid: grid) : int => {
  let nextRow = getNextCell(row, List.length(grid));
  let nextCol = getNextCell(col, List.length(List.nth(grid, 0)));
  let neighbour = List.nth(List.nth(grid, nextRow), nextCol);
  /* convert field value to integer to count it */
  switch (neighbour) {
  | Dead => 0
  | _ => 1
  };
};

let calcNextState = (grid: grid) =>
  grid
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, value: field) => {
            let neighbours = [|
              /* topLeft */
              [|rowIndex - 1, colIndex - 1|],
              /* topCenter */
              [|rowIndex - 1, colIndex|],
              /* topRight */
              [|rowIndex - 1, colIndex + 1|],
              /* centerLeft */
              [|rowIndex, colIndex - 1|],
              /* centerRight */
              [|rowIndex, colIndex + 1|],
              /* bottomLeft */
              [|rowIndex + 1, colIndex - 1|],
              /* bottomCenter */
              [|rowIndex + 1, colIndex|],
              /* bottomRight */
              [|rowIndex + 1, colIndex + 1|],
            |];
            let totalNeighbours =
              neighbours
              |> Js.Array.reduce(
                   (total, list) =>
                     total + getNeighbour(list[0], list[1], grid),
                   0,
                 );
            isAlive(totalNeighbours, value);
          })
     );