
function createSprite(x, y) {
  var e = new Entity("spritename");
  var mr = new MeshRenderer();
  mr.setColor(1, 1, 1, 1);
  mr.setShader(Shader.getDefaultNoTextureShader());
  e.addComponent(Mesh.createRect(2, 2));
  e.addComponent(mr);
  e.getComponent("Transform").setPosition(x, y);
  return e;
}

function main() {
  flwindow.setSize(640, 480);
  var camera = new Entity("camera");
  camera.addComponent(new Camera()).setOrtho(0, 20, 0, 15, -1, 100);
  flwindow.setResizable(false);
  flwindow.setClearColor(0.2, 0.2, 0.2, 1);
  for(var i = 0; i < 10; i++) {
      createSprite(1 + i * 2, 1+ i * 2);
  }
}
