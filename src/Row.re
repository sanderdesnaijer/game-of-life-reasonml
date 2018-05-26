open Types;

open Utils;

let component = ReasonReact.statelessComponent("Row");

let make = (~index, ~row, _children) => {
  ...component,
  render: __children =>
    <div className="row">
      (
        row
        |> List.mapi((col: int, value: field) => {
             let key = string_of_int(index) ++ string_of_int(col);
             <Field
               key
               value
               row=index
               col
               onClick=(
                 (a, v) =>
                   Js.log(string_of_int(a) ++ " " ++ string_of_int(v))
               )
             />;
           })
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
    </div>,
};