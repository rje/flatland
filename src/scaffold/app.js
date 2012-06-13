
function configureWindow() {
  flwindow.setSize(1280, 720);
  var camera = new Entity("camera");
  camera.addComponent(new Camera()).setOrtho(0, 40, 0, 22.5, -1, 100);
  flwindow.setResizable(false);
  flwindow.centerOnScreen();
}

function main() {
  configureWindow();
}