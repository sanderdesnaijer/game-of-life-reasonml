/* This is the basic component. */
open Types;
open Utils;

type action =
  | ToggleField(int, int)
  | NextFrame;

let initialState = {
  grid: [
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Alive, Alive, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Alive, Alive, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Alive, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
  ],
  gameState: Paused,
};

let toggleField = (rowI: int, colI: int, grid: grid) : grid =>
  grid
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, value: field) =>
            colI === colIndex && rowI === rowIndex ? {
              switch (value) {
                | Dead => Alive
                | Alive => Dead
            }
            } : value
          )
     );

let component = ReasonReact.reducerComponent("Game");

let make = _ => {
  ...component,
  initialState: () => initialState,
  didMount: (_) => (),
  reducer: (action: action, state: state) =>
    switch (action) {
    | ToggleField((row: int), (col: int)) =>
      let grid = toggleField(row, col, state.grid);
      ReasonReact.Update({grid, gameState: state.gameState});
    | NextFrame => 
        ReasonReact.Update({grid: calcNextState(state.grid), gameState: state.gameState});
    },
  render: ({state, send}) =>
    <div className="game">
      <Grid
        onToggle=((row, col) => send(ToggleField(row, col)))
        grid=state.grid
      />
      <button onClick=(_ => send(NextFrame))>(toString("knop"))</button>

    </div>,
};