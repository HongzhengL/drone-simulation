import $ from "jquery";
import * as THREE from "three";
import { scene } from "./scene";
import { camera } from "./camera";
import { ground } from "./model";
import { sendCommand } from "./websocket_api";

const container = $("#scene-container")[0];
const scheduleButton = $("#schedule-button")[0];
const scheduleForm = $("#schedule-input")[0];
const scheduleName = $("#schedule-name")[0] as HTMLInputElement;
const scheduleStrategy = $("#search-strategy")[0] as HTMLSelectElement;
const scheduleSubmit = $("#schedule-submit")[0];
const scheduleError = $("#schedule-error")[0];
const scheduleCancelButton = $("#schedule-cancel")[0];

let raycaster = new THREE.Raycaster();
let beamGeometry = new THREE.CylinderGeometry(0.2, 0.2, 3000, 16, 1);
let beamSelector1 = new THREE.Mesh(
  beamGeometry,
  new THREE.MeshBasicMaterial({
    color: 0xffff00,
    transparent: true,
    opacity: 0.5,
  })
);
let beamSelector2 = new THREE.Mesh(
  beamGeometry,
  new THREE.MeshBasicMaterial({
    color: 0x00ff00,
    transparent: true,
    opacity: 0.5,
  })
);
let beamState = 0;

function initScheduler() {
  beamSelector1.visible = false;
  beamSelector2.visible = false;
  scene.add(beamSelector1, beamSelector2);

  scheduleButton.onclick = () => {
    beamState = 1;
    scheduleButton.hidden = true;
    scheduleForm.hidden = false;
  };

  scheduleCancelButton.onclick = () => {
    beamState = 0;
    beamSelector1.visible = false;
    beamSelector2.visible = false;
    scheduleButton.hidden = false;
    scheduleForm.hidden = true;
  };

  container.onmousedown = (click) => {
    if (beamState > 0) {
      click.preventDefault();
      let normalized_coords = new THREE.Vector2(
        (click.clientX / container.clientWidth) * 2 - 1,
        -(click.clientY / container.clientHeight) * 2 + 1
      );
      raycaster.setFromCamera(normalized_coords, camera);
      if (ground) {
        let intersects = raycaster.intersectObject(ground, true);
        intersects.forEach((i) => {
          switch (beamState) {
            case 1:
              beamSelector1.position.copy(i.point);
              beamSelector1.visible = true;
              beamState = 2;
              break;
            default:
              beamSelector2.position.copy(i.point);
              beamSelector2.visible = true;
              beamState = 3;
              break;
          }
        });
      }
    }
  };

  scheduleSubmit.onclick = () => {
    let name = scheduleName.value;
    let searchStrat = scheduleStrategy.value;
    scheduleError.innerHTML = "";
    if (name == "")
      scheduleError.innerHTML +=
        '<p style="color: red">[!] Error, missing name...</p>';
    if (beamState != 3)
      scheduleError.innerHTML +=
        '<p style="color: red">[!] Error, missing pickup and drop off location ...</p>';
    if (name != "" && beamState == 3) {
      sendCommand("CreateEntity", {
        type: "package",
        name: name + "_package",
        mesh: "assets/model/package1.glb",
        position: [
          beamSelector1.position.x * 14.2,
          254.665,
          beamSelector1.position.z * 14.2,
        ],
        scale: [0.75, 0.75, 0.75],
        direction: [1, 0, 0],
        speed: 30.0,
        radius: 1.0,
        rotation: [0, 0, 0, 0],
      });
      sendCommand("CreateEntity", {
        type: "robot",
        name: name,
        mesh: "assets/model/robot.glb",
        position: [
          beamSelector2.position.x * 14.2,
          254.665,
          beamSelector2.position.z * 14.2,
        ],
        scale: [0.25, 0.25, 0.25],
        direction: [1, 0, 0],
        speed: 30.0,
        radius: 1.0,
        rotation: [0, 0, 0, 0],
      });
      sendCommand("ScheduleTrip", {
        name: name,
        start: [
          beamSelector1.position.x * 14.2,
          beamSelector1.position.z * 14.2,
        ],
        end: [
          beamSelector2.position.x * 14.2,
          254.665,
          beamSelector2.position.z * 14.2,
        ],
        search: searchStrat,
      });
      beamState = 0;
      beamSelector1.visible = false;
      beamSelector2.visible = false;
      scheduleButton.hidden = false;
      scheduleForm.hidden = true;
    }
  };

  window.addEventListener("keydown", (ev) => {
    switch (ev.key) {
      case " ":
        if (beamState == 0) {
          scheduleButton.click();
          scheduleName.focus();
          scheduleName.value = "";
          ev.preventDefault();
        }
        break;
      case "Enter":
        if (beamState > 0) {
          ev.preventDefault();
          scheduleSubmit.click();
        }
        break;
      case "Escape":
        if (beamState > 0) {
          ev.preventDefault();
          scheduleCancelButton.click();
        }
        break;
      case "ArrowUp":
        if (beamState > 0) {
          ev.preventDefault();
          (
            scheduleStrategy[
              (scheduleStrategy.selectedIndex + scheduleStrategy.length - 1) %
                scheduleStrategy.length
            ] as HTMLOptionElement
          ).selected = true;
        }
        break;
      case "ArrowDown":
        if (beamState > 0) {
          ev.preventDefault();
          (
            scheduleStrategy[
              (scheduleStrategy.selectedIndex + 1) % scheduleStrategy.length
            ] as HTMLOptionElement
          ).selected = true;
        }
        break;
    }
  });
}

export { initScheduler };
