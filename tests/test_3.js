function createTestEntity(x, y) {
  var e = new Entity();
  e.getComponent("Transform").setPosition(x, y);
  e.addComponent(Mesh.createRect(32, 32));
  var mr = new MeshRenderer();
  mr.setColor(0.5, 0.5, 1.0, 1.0);
  e.addComponent(mr);
  var s = new Scriptable("simple update");
  s.onUpdate = function(delta) {
    var t = this.getParent().getComponent("Transform");
    var pos = t.getPosition();
    var newX = pos.x + 20.0 * delta;
    t.setPosition(newX, pos.y);
  };
  e.addComponent(s);

  return e;
}

function main() {
  window.setSize(1280, 720);
  var e = createTestEntity(200, 200);
}

main();
