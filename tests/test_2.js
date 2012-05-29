
function createSprite(x, y) {
  var e = new Entity("spritename");
  var mr = new MeshRenderer();
  mr.setColor(1, 0, 0, 1);
  e.addComponent(Mesh.createRect(64, 64));
  e.addComponent(mr);
  e.getComponent("Transform").setPosition(x, y);
  var s = new Scriptable();
  s.onUpdate = function (delta) {
    if(this.transform == undefined) {
       this.transform = e.getComponent("Transform");
    }
    var pos = this.transform.getPosition();
    var newX = pos.x + 1;
    if(newX > window.getSize().width) {
      newX -= window.getSize().width;
    }
    this.transform.setPosition(newX, pos.y, pos.z);
  }
  e.addComponent(s);
  return e;
}

function main() {
  window.setSize(800, 600);
  window.setClearColor(1, 1, 1, 1);
  for(var i = 0; i < 10; i++) {
      createSprite(i * 64, i * 64);
  }
}

main();
