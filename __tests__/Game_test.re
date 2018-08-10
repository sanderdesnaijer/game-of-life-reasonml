open Jest;

open Expect;

open Game;

open Types;

let testGrid = [
  [Dead, Dead, Dead, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Dead, Dead, Dead],
];

describe("toggleField", () => {
  let grid = ref(testGrid);

  test("toggle Alive", () => {
    grid := toggleField(0, 1, grid^);
    expect(List.nth(List.nth(grid^, 0), 1)) |> toEqual(Alive)
  });
  
  test("toggle Dead", () => {
    grid := toggleField(0, 1, grid^);
    expect(List.nth(List.nth(grid^, 0), 1)) |> toEqual(Dead)
  });
});

describe("clearGrid", () => {
  test("clear", () => {
    let grid = testGrid |> clearGrid;
    let totalAlive = grid |> Array.of_list |> Js.Array.reduce((total, row) => {      
      let aliveInRow = row |> Array.of_list |> Js.Array.filter(p => p === Alive) |> Array.length;      
      total + aliveInRow;
    }, 0);
    
    expect(totalAlive) |> toBe(0)
  });
});

describe("isAlive", () => {
  test("Alive", () =>
    expect(isAlive(0, Alive)) |> toBe(Dead)
  );
  test("Alive", () =>
    expect(isAlive(1, Alive)) |> toBe(Dead)
  );
  test("Alive", () =>
    expect(isAlive(2, Alive)) |> toBe(Alive)
  );
  test("Alive", () =>
    expect(isAlive(3, Alive)) |> toBe(Alive)
  );
  test("Alive", () =>
    expect(isAlive(4, Alive)) |> toBe(Dead)
  );
  test("Dead", () =>
    expect(isAlive(2, Dead)) |> toBe(Dead)
  );
  test("Dead", () =>
    expect(isAlive(3, Dead)) |> toBe(Alive)
  );
  test("Dead", () =>
    expect(isAlive(4, Dead)) |> toBe(Dead)
  );
});

describe("getNextCell", () => {
  test("in bounds", () =>
    expect(getNextCell(0, 10)) |> toBe(0)
  );
  test("out of bounds negative", () =>
    expect(getNextCell(-1, 10)) |> toBe(9)
  );
  test("out of bounds positive", () =>
    expect(getNextCell(10, 10)) |> toBe(0)
  );
});

describe("getNeighbourValue", () => {
  test("row 1 col 1", () =>
    expect(getNeighbourValue(1, 0, testGrid)) |> toBe(0)
  );
  test("row 1 col 2", () =>
    expect(getNeighbourValue(1, 2, testGrid)) |> toBe(1)
  );
  test("row 1 col 3", () =>
    expect(getNeighbourValue(1, 3, testGrid)) |> toBe(0)
  );
});

describe("calcNextState with oscilator pattern", () => {
  let predictedResult = [
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Alive, Alive, Alive, Dead],
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead],
  ];
  test("nextState", () =>
    expect(calcNextState(testGrid)) |> toEqual(predictedResult)
  );
  test("nextState", () =>
    expect(calcNextState(predictedResult)) |> toEqual(testGrid)
  );
});