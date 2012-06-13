
function createSprite(x, y) {
  var e = new Entity("spritename");
  var mr = e.addComponent(new MeshRenderer());
  mr.setColor(1, 0, 0, 1);
  mr.setShader(Shader.getDefaultNoTextureShader());
  e.addComponent(Mesh.createRect(2, 2));
  e.transform.setPosition(x, y);
  var s = new Scriptable("moving");
  s.onUpdate = function (delta) {
    if(this.transform == undefined) {
       this.transform = e.transform;
    }
    var pos = this.transform.getPosition();
    var newX = pos.x + 10 * delta;
    if(newX > 20) {
      newX -= 20;
    }
    this.transform.setPosition(newX, pos.y, pos.z);
  };
  e.addComponent(s);
  return e;
}

function main() {
  flwindow.setSize(640, 480);
  var camera = new Entity("camera");
  camera.addComponent(new Camera()).setOrtho(0, 20, 0, 15, -1, 100);
  flwindow.setResizable(false);
  flwindow.setClearColor(1, 1, 1, 1);
  for(var i = 0; i < 8; i++) {
      createSprite(1 + i * 2, 1 + i * 2);
  }
}
