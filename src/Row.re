open Types;

let component = ReasonReact.statelessComponent("Row");

let make = (~index, ~row, ~onToggle, _children) => {
  ...component,
  render: __children =>
    <div className="row">
      (
        row
        |> List.mapi((col: int, value: field) => {
             let key = string_of_int(index) ++ string_of_int(col);
             <Field key value row=index col onToggle />;
           })
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};