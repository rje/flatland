
function createSprite() {
  var e = new Entity("spritename");
  e.addComponent(Mesh.createRect(64, 64));
  e.addComponent(new MeshRenderer());
  return e;
}

function main() {
  window.setSize(800, 600);
  window.setClearColor(0, 0, 0, 0);
  var sprite = createSprite();
}

main();
