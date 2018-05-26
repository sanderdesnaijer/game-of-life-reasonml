/* This is the basic component. */
open Types;

type action =
  | ClickField(int, int);

let component = ReasonReact.reducerComponent("Game");

let initialState = {
  grid: [
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead, Dead],
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

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action: action, state: state) =>
    ReasonReact.Update(initialState),
  render: ({state}) =>
    <div className="game"> <Grid grid=state.grid /> </div>,
};