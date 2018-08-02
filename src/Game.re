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
      ReasonReact.Update({...state, grid: toggleField(row, col, state.grid)})
    | NextFrame =>
      ReasonReact.Update({...state, grid: Utils.calcNextState(state.grid)})
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
        ((state.gameState === Playing ? "Pause" : "Play") |> Utils.toString)
      </button>
      <button onClick=((_) => send(Clear))>
        (Utils.toString("Reset"))
      </button>
    </div>,
};