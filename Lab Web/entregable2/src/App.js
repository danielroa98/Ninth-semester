//librerias ó components
import "./App.css";
import "./index.css";
import React, { useState, useEffect } from "react";

import NewInput from "./components/NewInput";

function App() {
  
  const [date, setDate] = useState(new Date())
  const [users, setUsers] = useState([{ id: 0, name: "Daniel"}]);

  const onClick = () => {
    setUsers([...users, { id: users.length, name: "Bigus Dickus"}])
  };  

  var dataComponent = {
    type:'button',
    value:'Update',
    hidden:false
  }

  useEffect(() => {
    var timerID = setInterval(() => tick(), 1000)
    
    return function cleanup(params) {
      clearInterval(timerID);
    }

  });

  function tick() {
    setDate(new Date())
  }

  return (
    <div>
      {/* <NewInput onClick={onClick} {...dataComponent} />
      <div>
        {users.map((e) => (
          <div>
            {e.id} - {e.name}
          </div>
        ))}
      </div> */}
      <h1>{date.toLocaleTimeString()}</h1>
    </div>
  );
}

export default App;
