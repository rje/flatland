
function createBox(w, h, name, r, g, b, a) {
    r = (r == undefined) ? 1 : r;
    g = (g == undefined) ? 1 : g;
    b = (b == undefined) ? 1 : b;
    a = (a == undefined) ? 1 : a;
    var e = new Entity(name);
    e.addComponent(Mesh.createRect(w, h));
    var mr = new MeshRenderer();
    mr.setColor(r, g, b, a);
    e.addComponent(mr);
    return e;
}

function createBoard(cols, rows) {
    var blockSize = {w: 64, h: 32};
    var blockSpace = {w: 16, h: 16};
    var screenSize = window.getSize();
    var rowWidth = cols * blockSize.w + (cols - 1) * blockSpace.w;
    var colHeight = rows * blockSize.h + (rows - 1) * blockSpace.h;
    var xOffset = (screenSize.width - rowWidth) / 2 + blockSize.w / 2;
    var yOffset = screenSize.height - colHeight - xOffset + blockSize.w;
    for(var x = 0; x < cols; x++) {
        for(var y = 0; y < rows; y++) {
            var block = createBox(blockSize.w, blockSize.h, "block", 0.8, 0.8, 0.8);
            var t = block.getComponent("Transform");
            t.setPosition(xOffset + x * (blockSize.w + blockSpace.w),
                          yOffset + y * (blockSize.h + blockSpace.h));
            var bc = new BoxCollider();
            bc.setSize(1, 0.5);
            block.addComponent(bc);
            bc.setRestitution(1);
            bc.onCollision = function(other) {
                this.getParent().destroy();
            };
        }
    }
}

function createPaddle() {
    var screenSize = window.getSize();
    var paddle = createBox(128, 16, "paddle", 0.8, 0.8, 0.8);
    var t = paddle.getComponent("Transform");
    t.setPosition(screenSize.width / 2 - 64, 32);
    var s = new Scriptable("Controls");
    s.onUpdate = function(delta) {
        var pos = t.getPosition();
        if(keyboard.isKeyDown(keyboard.codes.left)) {
            pos.x -= 400.0 * delta;
        }
        if(keyboard.isKeyDown(keyboard.codes.right)) {
            pos.x += 400.0 * delta;
        }
        t.setPosition(pos.x, pos.y, pos.z);
    };
    paddle.addComponent(s);
    var bc = new BoxCollider();
    bc.setSize(2, 0.25);
    paddle.addComponent(bc);
    bc.setRestitution(1);
    return paddle;
}

function createBall() {
    var screenSize = window.getSize();
    var ball = createBox(16, 16, "ball", 0.8, 0.8, 0.8);
    var t = ball.getComponent("Transform");
    t.setPosition(screenSize.width / 2 - 8, 200);
    var cc = new CircleCollider();
    cc.setSize(0.2);
    ball.addComponent(cc);
    cc.setType(Collider.dynamic);
    cc.setLinearVelocity(3, -5);
}

function main() {
    window.setClearColor(0.33, 0.33, 0.33, 0);
    window.setSize(800, 600);
    window.setResizable(false);
    createBoard(9, 6);
    createPaddle();
    createBall();
}

main();