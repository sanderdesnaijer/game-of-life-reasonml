open Types;

let component = ReasonReact.statelessComponent("Page");

let make = (~grid, ~onToggle, _children) => {
  ...component,
  render: __children =>
    <div className="grid">
      (
        grid
        |> List.mapi((index: int, row: row) =>
             <Row onToggle key=("col" ++ (index |> string_of_int)) index row />
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};