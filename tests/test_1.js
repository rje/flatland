
function createSprite() {
  var e = new Entity("spritename");
  var m = Mesh.createRect(64, 64);
  e.addComponent(m);

  return e;
}

function main() {
  window.setSize(800, 600);
  var sprite = createSprite();
}

main();
