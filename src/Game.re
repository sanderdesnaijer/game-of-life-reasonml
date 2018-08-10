open Types;

type action =
  | ToggleField(int, int)
  | NextFrame
  | TogglePlay
  | Clear;

let initialState = {
  grid: [
    [Dead, Dead, Dead, Alive, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Alive, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Alive, Alive, Alive, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Alive, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Alive, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Alive, Alive, Alive, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
  ],
  gameState: Playing,
  intervalId: ref(None),
};

let speed: int = 200;

let toggleField = (rowI: int, colI: int, grid: grid) : grid =>
  grid
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, value: field) =>
            colI === colIndex && rowI === rowIndex ?
              switch (value) {
              | Dead => Alive
              | Alive => Dead
              } :
              value
          )
     );

let clearGrid = (grid: grid) : grid =>
  grid
  |> List.map((row: row) =>
       row
       |> List.map((value: field) =>
            switch (value) {
            | Dead => Dead
            | Alive => Dead
            }
          )
     );


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

/* get value of neighbour cell */
let getNeighbourValue = (row: int, col: int, grid: grid) : int => {
  let nextRow = getNextCell(row, List.length(grid));
  let nextCol = getNextCell(col, List.length(List.nth(grid, 0)));
  let neighbour = List.nth(List.nth(grid, nextRow), nextCol);
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
                     total + getNeighbourValue(list[0], list[1], grid),
                   0,
                 );
            isAlive(totalNeighbours, value);
          })
     );     

let component = ReasonReact.reducerComponent("Game");

let make = (_) => {
  ...component,
  initialState: () => initialState,
  didMount: ({state, send}) =>
    switch (state.gameState) {
    | Playing =>
      state.intervalId :=
        Some(Js.Global.setInterval(() => send(NextFrame), speed))
    | Paused => ()
    },
  reducer: (action: action, state: state) =>
    switch (action) {
    | ToggleField((row: int), (col: int)) =>
      switch (state.intervalId^) {
      | Some(id) =>
        ReasonReact.UpdateWithSideEffects(
          {
            ...state,
            gameState: Paused,
            grid: toggleField(row, col, state.grid),
          },
          ((_) => Js.Global.clearInterval(id)),
        )
      | None =>
        ReasonReact.Update({
          ...state,
          grid: toggleField(row, col, state.grid),
        })
      }
    | NextFrame =>
      ReasonReact.Update({...state, grid: calcNextState(state.grid)})
    | TogglePlay =>
      switch (state.gameState) {
      | Playing =>
        switch (state.intervalId^) {
        | Some(id) =>
          ReasonReact.UpdateWithSideEffects(
            {...state, gameState: Paused},
            ((_) => Js.Global.clearInterval(id)),
          )
        | None => ReasonReact.Update(initialState)
        }
      | Paused =>
        ReasonReact.UpdateWithSideEffects(
          {...state, gameState: Playing},
          (
            self =>
              state.intervalId :=
                Some(
                  Js.Global.setInterval(() => self.send(NextFrame), speed),
                )
          ),
        )
      }
    | Clear => ReasonReact.Update({...state, grid: clearGrid(state.grid)})
    },
  render: ({state, send}) =>
    <div className="game">
      <Grid
        onToggle=((row, col) => send(ToggleField(row, col)))
        grid=state.grid
      />
      <button onClick=((_) => send(TogglePlay))>
        ((state.gameState === Playing ? "Pause" : "Play") |> ReasonReact.string)
      </button>
      (
        switch (state.gameState) {
        | Playing => ReasonReact.null
        | _ =>
          <button onClick=((_) => send(NextFrame))>
            ("Next" |> ReasonReact.string)
          </button>
        }
      )
      <button onClick=((_) => send(Clear))>
        ("Reset" |> ReasonReact.string)
      </button>
    </div>,
};