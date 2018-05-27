type field =
  | Dead
  | Alive;

type row = list(field);

type grid = list(row);

type gameState =
  | Playing
  | Paused;

type state = {
  grid,
  gameState,
  intervalId: ref(option(Js.Global.intervalId)),
};