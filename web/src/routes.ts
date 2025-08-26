import * as THREE from "three";
import $ from "jquery";
import { addMesh } from "./model";

const showRoutesCheckbox = $("#show-routes")[0];

let routes: THREE.Group[] = [];
let showRoutes = false;

async function addRoute(details: any) {
  let route = await addMesh(details);
  route.visible = showRoutes;
  routes.push(route);
}

showRoutesCheckbox.onclick = () => {
  showRoutes = !showRoutes;
  routes.forEach((route) => {
    route.visible = showRoutes;
  });
};

export { addRoute };
