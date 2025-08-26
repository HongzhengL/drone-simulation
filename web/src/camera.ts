import * as THREE from "three";
import $ from "jquery";
import { OrbitControls } from "three/examples/jsm/Addons.js";
import { entities } from "./model";

const container = $("#scene-container")[0];
const entitySelect = $("#entity-select");

let camera = new THREE.PerspectiveCamera(
  35,
  container.clientWidth / container.clientHeight,
  0.1,
  1000
);
let controls = new OrbitControls(camera, container);

let currentView = -1;

camera.position.set(-10, 10, 10);

entitySelect[0].onchange = () => {
  currentView = entitySelect.val() as number;
  updateControls();
};

function updateControls() {
  if (currentView >= 0) {
    controls.target.copy(entities[currentView].position);
    controls.update();
  }
}

function resetCurrentView() {
  currentView = -1;
}

export { camera, updateControls, currentView, resetCurrentView };
