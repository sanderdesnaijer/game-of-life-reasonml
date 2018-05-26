/* This is the basic component. */
let component = ReasonReact.statelessComponent("Main");

let make = _children => {
  ...component,
  render: _self => <div> <Game /> </div>,
};