open Types;

open Utils;

let component = ReasonReact.statelessComponent("Page");

let make = (~grid, _children) => {
  ...component,
  didMount: (_) => Js.log(grid),
  render: __children =>
    <div className="grid">
      (
        grid
        |> List.mapi((index: int, row: row) =>
             <Row key=("row-" ++ string_of_int(index)) index row />
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>,
};