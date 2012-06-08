
function createSprite(x, y) {
  var e = new Entity("spritename");
  var mr = new MeshRenderer();
  mr.setColor(1, 0, 0, 1);
  e.addComponent(Mesh.createRect(2, 2));
  e.addComponent(mr);
  e.getComponent("Transform").setPosition(x, y);
  var s = new Scriptable("moving");
  s.onUpdate = function (delta) {
    if(this.transform == undefined) {
       this.transform = e.getComponent("Transform");
    }
    var pos = this.transform.getPosition();
    var newX = pos.x + 0.01;
    if(newX > 20) {
      newX -= 20;
    }
    this.transform.setPosition(newX, pos.y, pos.z);
  }
  e.addComponent(s);
  return e;
}

function main() {
  window.setSize(640, 480);
    window.setViewportSize(20, 15);
    window.setResizable(false);
  window.setClearColor(1, 1, 1, 1);
  for(var i = 0; i < 8; i++) {
      createSprite(1 + i * 2, 1 + i * 2);
  }
}

main();
