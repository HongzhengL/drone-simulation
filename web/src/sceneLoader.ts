import $ from "jquery";
import { loadModel, addMesh } from "./model";
import { addRoute } from "./routes";
import { sendCommand } from "./websocket_api";

function loadScene(file: string) {
  $.getJSON(file, (data) => {
    data.forEach((command: any) => {
      switch (command.command) {
        case "SetScene":
          loadModel(command.params);
          break;
        case "AddMesh":
          if (command.params.type == "route") {
            addRoute(command.params);
          } else {
            addMesh(command.params);
          }
          break;
        default:
          sendCommand(command.command, command.params);
          break;
      }
    });
  });
}

export { loadScene };
