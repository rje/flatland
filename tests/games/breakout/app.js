function createBox(w, h, name, r, g, b) {
    var e = new Entity(name);
    e.addComponent(Mesh.createRect(w, h));
    var mr = e.addComponent(new MeshRenderer());
    mr.setColor(r, g, b, 1);

    return e;
}

function createBoard(cols, rows) {
    var blockSize = {w: 3, h: 1.5};
    var blockSpace = {w: 0.25, h: 0.25};
    var rowWidth = cols * blockSize.w + (cols - 1) * blockSpace.w;
    var colHeight = rows * blockSize.h + (rows - 1) * blockSpace.h;
    var xOffset = (32 - rowWidth) / 2 + blockSize.w / 2;
    var yOffset = 24 - colHeight - xOffset + blockSize.w;
    for(var x = 0; x < cols; x++) {
        for(var y = 0; y < rows; y++) {
            var block = createBox(blockSize.w, blockSize.h, "block", 0.8, 0.8, 0.8);
            var t = block.getComponent("Transform");
            t.setPosition(xOffset + x * (blockSize.w + blockSpace.w),
                          yOffset + y * (blockSize.h + blockSpace.h));
            var bc = block.addComponent(new BoxCollider(1.5, 0.75));
            bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});
            bc.onCollision = function(contact, otherCollider) {
                this.getParent().destroy();
            };
        }
    }
}

function createPaddle() {
    var paddle = createBox(4, 0.5, "paddle", 0.8, 0.8, 0.8);
    var t = paddle.getComponent("Transform");
    t.setPosition(14, 1);
    var s = new Scriptable("Controls");
    s.onUpdate = function(delta) {
        var pos = t.getPosition();
        if(keyboard.isKeyDown(keyboard.codes.left)) {
            pos.x -= 16.0 * delta;
        }
        if(keyboard.isKeyDown(keyboard.codes.right)) {
            pos.x += 16.0 * delta;
        }
        t.setPosition(pos.x, pos.y, pos.z);
    };
    paddle.addComponent(s);
    var bc = paddle.addComponent(new BoxCollider(2, 0.25));
    bc.setPhysicsProperties({type: Collider.kinematic, restitution: 1, friction: 0, density: 10});
    return paddle;
}

function createBall() {
    var ball = new Entity("ball");
    ball.addComponent(Mesh.createCircle(0.5, 32));
    ball.addComponent(new MeshRenderer()).setColor(0.8, 0.8, 0.8, 1);
    ball.getComponent("Transform").setPosition(16, 8);
    var cc = ball.addComponent(new CircleCollider(0.5));
    cc.setPhysicsProperties({type: Collider.dynamic, restitution: 1, friction: 0, density: 1});
    cc.setLinearVelocity(3, 5);
}

function createWalls() {
    var e = new Entity();
    e.getComponent("Transform").setPosition(0, 12);
    var bc = e.addComponent(new BoxCollider(0.1, 20));
    bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});

    e = new Entity();
    e.getComponent("Transform").setPosition(32, 12);
    bc = e.addComponent(new BoxCollider(0.1, 20));
    bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});

    e = new Entity();
    e.getComponent("Transform").setPosition(16, 24);
    bc = e.addComponent(new BoxCollider(25, 0.1));
    bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});
    bc.onCollision = function(contact, otherCollider) {
        var ball = otherCollider.getParent();
        if(!ball.hasDoubled) {
            var vel = otherCollider.getLinearVelocity();
            vel.x *= 2;
            vel.y *= 2;
            otherCollider.setLinearVelocity(vel.x, vel.y);
            ball.hasDoubled = true;
        }
    }
}

function main() {
    window.setSize(1024, 768);
    window.setViewportSize(32, 24);
    window.setResizable(false);
    window.setClearColor(0.33, 0.33, 0.33, 0);
    createBoard(8, 6);
    createWalls();
    createPaddle();
    createBall();
}

main();