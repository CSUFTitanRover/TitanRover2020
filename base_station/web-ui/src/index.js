import React from "react";
import ReactDOM from "react-dom";
import { Route, Link, Switch, BrowserRouter as Router } from "react-router-dom";
import "./index.css";
import App from "./App";
import Science from "./Science";
import Extreme from "./Extreme";
import Autonomous from "./Autonomous";
import * as serviceWorker from "./serviceWorker";

const routing = (
  <Router>
    <Switch>
      <Route exact path="/">
        <App />
      </Route>
      <Route path="/science">
        <Science />
      </Route>
      <Route path="/extreme">
        <Extreme />
      </Route>
      <Route path="/autonomous">
        <Autonomous />
      </Route>
    </Switch>
  </Router>
);

ReactDOM.render(routing, document.getElementById("root"));

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister();
