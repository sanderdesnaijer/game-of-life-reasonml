open Types;

open Utils;

let component = ReasonReact.statelessComponent("Field");

/* let toValue = (field:field) =>
       switch(field) {
       | Alive => "alive"
       | Dead => "dead"
   }; */

let toClassName = (field:field) => {
    switch field {
    | Alive => "field alive"
    | Dead => "field dead"
    };
}

let make = (~value: field, ~row: int, ~col: int, ~onClick, _children) => {
  ...component,
  didMount: (_) => Js.log("mount"),
  render: __children =>
    <div className=toClassName(value) onClick=(_evt => onClick(row, col))>
    </div>,
};