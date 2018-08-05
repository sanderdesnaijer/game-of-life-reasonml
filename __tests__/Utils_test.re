open Jest;

open Types;

let testGrid = [
  [Dead, Dead, Dead, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Alive, Dead, Dead],
  [Dead, Dead, Dead, Dead, Dead],
];

describe("toString", () => {
  open Expect;
  let testValue = "testing-109";
  test("in bounds", () =>
    expect(testValue |> Utils.toString) |> toBe(Utils.toString(testValue))
  );
});

describe("isAlive", () => {
  open Expect;
  test("Alive", () =>
    expect(Utils.isAlive(0, Alive)) |> toBe(Dead)
  );
  test("Alive", () =>
    expect(Utils.isAlive(1, Alive)) |> toBe(Dead)
  );
  test("Alive", () =>
    expect(Utils.isAlive(2, Alive)) |> toBe(Alive)
  );
  test("Alive", () =>
    expect(Utils.isAlive(3, Alive)) |> toBe(Alive)
  );
  test("Alive", () =>
    expect(Utils.isAlive(4, Alive)) |> toBe(Dead)
  );
  test("Dead", () =>
    expect(Utils.isAlive(2, Dead)) |> toBe(Dead)
  );
  test("Dead", () =>
    expect(Utils.isAlive(3, Dead)) |> toBe(Alive)
  );
  test("Dead", () =>
    expect(Utils.isAlive(4, Dead)) |> toBe(Dead)
  );
});

describe("getNextCell", () => {
  open Expect;
  test("in bounds", () =>
    expect(Utils.getNextCell(0, 10)) |> toBe(0)
  );
  test("out of bounds negative", () =>
    expect(Utils.getNextCell(-1, 10)) |> toBe(9)
  );
  test("out of bounds positive", () =>
    expect(Utils.getNextCell(10, 10)) |> toBe(0)
  );
});

describe("getNeighbourValue", () => {
  open Expect;
  test("row 1 col 1", () =>
    expect(Utils.getNeighbourValue(1, 0, testGrid)) |> toBe(0)
  );
  test("row 1 col 2", () =>
    expect(Utils.getNeighbourValue(1, 2, testGrid)) |> toBe(1)
  );
  test("row 1 col 3", () =>
    expect(Utils.getNeighbourValue(1, 3, testGrid)) |> toBe(0)
  );
});

describe("calcNextState with oscilator pattern", () => {
  open Expect;
  let predictedResult = [
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Alive, Alive, Alive, Dead],
    [Dead, Dead, Dead, Dead, Dead],
    [Dead, Dead, Dead, Dead, Dead],
  ];
  test("nextState", () =>
    expect(Utils.calcNextState(testGrid)) |> toEqual(predictedResult)
  );
  test("nextState", () =>
    expect(Utils.calcNextState(predictedResult)) |> toEqual(testGrid)
  );
});