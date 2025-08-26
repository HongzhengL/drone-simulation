import $ from "jquery";
import * as THREE from "three";
import { GLTFLoader } from "three/examples/jsm/Addons.js";
import { OBJLoader } from "three/examples/jsm/Addons.js";
import { scene } from "./scene";
import { currentView, resetCurrentView } from "./camera";

let gltfLoader = new GLTFLoader();
let objLoader = new OBJLoader();

let entities: Record<number, THREE.Object3D> = {};
let mixers: {
  id: number;
  mixer: THREE.AnimationMixer;
  start?: number;
  duration?: number;
}[] = [];
let ground: THREE.Group | undefined = undefined;

function addEntity(id: number, details: any) {
  return new Promise<THREE.Group>((resolve, reject) => {
    gltfLoader.load(details.mesh, (gltf) => {
      $("#entity-select").append(
        $(`<option value="${id}">${details.name}</option>`)
      );

      let group = new THREE.Group();
      gltf.scene.children.forEach((model) => {
        group.add(model);
      });

      group.traverse((object) => {
        if (object instanceof THREE.Mesh) {
          object.userData.defaultColor = object.material.color.clone();
          if (details.color) {
            object.material.color.multiply(new THREE.Color(details.color));
          }
        }
      });

      let animation = gltf.animations[0];
      if (animation) {
        let mixer = new THREE.AnimationMixer(group.children[0]);
        mixers.push({
          id: id,
          mixer: mixer,
          start: details.start,
          duration: details.duration,
        });
        let action = mixer.clipAction(animation);
        action.play();
      }

      group.scale.copy(new THREE.Vector3(...details.scale));

      if (details.offset)
        group.userData.offset = new THREE.Vector3(...details.offset);
      else group.userData.offset = new THREE.Vector3();

      scene.add(group);
      entities[id] = group;
      resolve(group);
    });
  });
}

function updateEntity(id: number, details: any) {
  let model = entities[id];
  if (!model) return;

  model.position.copy(new THREE.Vector3(...details.pos));
  model.position.x /= 14.2;
  model.position.y /= 20;
  model.position.y -= 13;
  model.position.z /= 14.2;
  model.position.add(model.userData.offset);

  let dir = new THREE.Vector3(...details.dir);
  dir = model.localToWorld(new THREE.Vector3()).add(dir);
  model.lookAt(dir);

  model.traverse((node) => {
    if (node instanceof THREE.Mesh) {
      if (details.color) {
        let color = node.userData.defaultColor.clone();
        color.multiply(new THREE.Color(details.color));
        node.material.color.set(color);
      } else {
        node.material.color.set(node.userData.defaultColor);
      }
    }
  });
}

function removeEntity(id: number) {
  scene.remove(entities[id]);
  $(`#entity-select option[value="${id}"]`).remove();
  delete entities[id];
  if (currentView == id) {
    resetCurrentView();
  }
}

// adds mesh with simple purple lines around it
function addMesh(details: any) {
  return new Promise<THREE.Group>((resolve, reject) => {
    objLoader.load(details.mesh, (obj) => {
      obj.position.copy(new THREE.Vector3(...details.position));
      obj.scale.copy(new THREE.Vector3(...details.scale));

      obj.traverse((node) => {
        if (node instanceof THREE.LineSegments) {
          node.material = new THREE.LineBasicMaterial({
            color: details.color,
            linewidth: 1,
            linecap: "round",
            linejoin: "round",
          });
        } else if (node instanceof THREE.Mesh) {
          node.material = new THREE.MeshBasicMaterial({
            color: details.color,
          });
        }
      });

      scene.add(obj);
      resolve(obj);
    });
  });
}

// loads the main building model
function loadModel(details: any) {
  return new Promise<THREE.Group>((resolve, reject) => {
    objLoader.load(details.mesh, (obj) => {
      obj.position.copy(new THREE.Vector3(...details.position));
      obj.scale.copy(new THREE.Vector3(...details.scale));

      let textureLoader = new THREE.TextureLoader();

      let roofTexture = textureLoader.load(details.texture);
      let groundTexture = textureLoader.load(details.groundTexture);

      let roofMaterial = new THREE.MeshStandardMaterial({
        color: details.color,
        map: roofTexture,
      });
      let groundMaterial = new THREE.MeshStandardMaterial({
        map: groundTexture,
      });

      obj.traverse((node) => {
        if (node.name == "EXPORT_GOOGLE_SAT_WM") {
          (node as THREE.Mesh).material = groundMaterial;
        } else if (node.name == "Areas:building") {
          (node as THREE.Mesh).material = roofMaterial;
        } else if (!(node instanceof THREE.Group)) {
          node.visible = false;
        }
      });

      ground = obj;
      scene.add(obj);
      resolve(obj);
    });
  });
}

function updateAnimations(delta: number) {
  mixers.forEach((mixer) => {
    if (mixer.start && mixer.duration) {
      if (
        mixer.mixer.time < mixer.start ||
        mixer.mixer.time > mixer.start + mixer.duration
      ) {
        mixer.mixer.setTime(mixer.start);
      }
    }
    mixer.mixer.update(delta);
  });
}

export {
  entities,
  addEntity,
  removeEntity,
  updateAnimations,
  updateEntity,
  addMesh,
  loadModel,
  ground,
};
