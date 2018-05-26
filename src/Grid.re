open Types;

open Utils;

let component = ReasonReact.statelessComponent("Page");

let make = (~grid, ~onToggle, _children) => {
  ...component,
  render: __children =>
    <div className="grid">
      (
        grid
        |> List.mapi((index: int, row: row) => {
             let key = "row-" ++ string_of_int(index);
             <Row onToggle key index row />;
           })
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>,
};