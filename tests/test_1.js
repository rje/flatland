
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
  window.setSize(640, 480);
  window.setViewportSize(20, 15);
  window.setResizable(false);
  window.setClearColor(0.2, 0.2, 0.2, 0);
  for(var i = 0; i < 10; i++) {
      createSprite(1 + i * 2, 1+ i * 2);
  }
}

main();
