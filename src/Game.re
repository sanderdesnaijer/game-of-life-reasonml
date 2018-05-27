open Types;
open Utils;

type action =
  | ToggleField(int, int)
  | NextFrame
  | TogglePlay

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

let speed:int = 200;

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
  didMount: ({state, send}) => {
      switch(state.gameState) {
        | Playing => 
            state.intervalId := Some(Js.Global.setInterval(() => send(NextFrame), speed))
        | Paused => ()
      }
  },
  reducer: (action: action, state: state,) =>
    switch (action) {
        | ToggleField((row: int), (col: int)) =>
        ReasonReact.Update({...state, grid: toggleField(row, col, state.grid)});
        | NextFrame => 
            ReasonReact.Update({...state, grid: calcNextState(state.grid)});
        | TogglePlay => {
            switch(state.gameState){
            | Playing => {            
                switch (state.intervalId^) {
                    | Some(id) => {
                        Js.Global.clearInterval(id);                
                        ReasonReact.Update({...state, gameState: Paused});
                    };
                    | None => ReasonReact.Update(initialState);
                }            
            }
            | Paused => ReasonReact.UpdateWithSideEffects({...state, gameState: Playing } , {
                (self => {                    
                    state.intervalId := Some(Js.Global.setInterval(() => self.send(NextFrame), speed));
                })
            });
            }
        }    
    },
  render: ({state, send}) =>
    <div className="game">
      <Grid
        onToggle=((row, col) => send(ToggleField(row, col)))
        grid=state.grid
      />
      <button onClick=(_ => send(TogglePlay))>
        ((state.gameState === Playing ? "Pause" : "Play") |> toString)
    </button>        
    </div>,
};