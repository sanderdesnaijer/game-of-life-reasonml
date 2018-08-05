open Jest;

open Enzyme;

open Types;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

describe("toClassname", () => {
  open Expect;
  test("Alive", () =>
    expect(Field.toClassName(Alive)) |> toBe("field alive")
  );
  test("Dead", () =>
    expect(Field.toClassName(Dead)) |> toBe("field dead")
  );
});

describe("Field", () =>
  Expect.(
    test("value", () => {
      let setup = (~value=Alive, ~row=0, ~col=0, ~onToggle=(0, 0) => (), ()) =>
        Enzyme.shallow(<Field value row col onToggle />);
      let value = Dead;
      let wrapper = setup(~value, ());
      expect(wrapper |> find(".field.dead") |> length) |> toBe(1);
    })
  )
);