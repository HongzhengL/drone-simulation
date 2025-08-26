import * as THREE from "three";

let scene = new THREE.Scene();

scene.background = new THREE.Color("skyblue");

scene.add(new THREE.AmbientLight("white", 2));
scene.add(new THREE.DirectionalLight("white", 2));

export { scene };
