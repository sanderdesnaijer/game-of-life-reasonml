open Types;

let component = ReasonReact.statelessComponent("Row");

let make = (~index, ~row, ~onToggle, _children) => {
  ...component,
  render: __children =>
    <div className="row">
      (
        row
        |> List.mapi((col: int, value: field) =>
             <Field
               key=((index |> string_of_int) ++ (col |> string_of_int))
               value
               row=index
               col
               onToggle
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};