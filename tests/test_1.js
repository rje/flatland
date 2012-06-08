
function createSprite(x, y) {
  var e = new Entity("spritename");
  var mr = new MeshRenderer();
  mr.setColor(1, 1, 1, 1);
  e.addComponent(Mesh.createRect(2, 2));
  e.addComponent(mr);
  e.getComponent("Transform").setPosition(x, y);
  return e;
}

function main() {
  window.setSize(800, 600);
    window.setViewportSize(32, 24);
    window.setResizable(false);
  window.setClearColor(1, 0, 0, 1);
  for(var i = 0; i < 10; i++) {
      createSprite(i * 64, i * 64);
  }
}

main();
