/* This is the basic component. */
let component = ReasonReact.statelessComponent("Page");

let make = _children => {...component, render: self => <div> <Game /> </div>};