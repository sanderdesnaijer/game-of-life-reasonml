open Types;

let component = ReasonReact.statelessComponent("Field");

let toClassName = (field: field) =>
  switch (field) {
  | Alive => "field alive"
  | Dead => "field dead"
  };

let make = (~value: field, ~row: int, ~col: int, ~onToggle, _children) => {
  ...component,
  render: __children =>
    <div
      className=(toClassName(value))
      onClick=(_evt => onToggle(row, col))
    />,
};