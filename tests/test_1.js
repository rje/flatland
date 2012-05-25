
function createSprite() {
  var e = new Entity("spritename");
  var m = new Mesh.createRect(0.5, 0.5);
  var mr = new MeshRenderer();
  mr.setColor(1, 1, 1, 1);
  e.addComponent(m);
  e.addComponent(mr);
  return e;
}

function main() {
  window.setSize(800, 600);
  window.setClearColor(0, 0, 0, 0);
  var sprite = createSprite();
}

main();
