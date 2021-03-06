var windowSize = {w: 1024, h: 768};
var viewSize = {w: 32, h: 24};
var blockSize = {w: 3, h: 1.5};
var blockSpace = {w: 0.25, h: 0.25};
var ballRadius = 0.5;
var numBlocks = {cols: 7, rows: 5};

function createBox(w, h, name, r, g, b) {
    var e = new Entity(name);
    e.addComponent(Mesh.createRect(w, h));
    var mr = e.addComponent(new MeshRenderer());
    mr.setColor(r, g, b);
    mr.setShader(Shader.getDefaultShader());
    return e;
}

function createBoard(cols, rows) {
    var rowWidth = cols * blockSize.w + (cols - 1) * blockSpace.w;
    var colHeight = rows * blockSize.h + (rows - 1) * blockSpace.h;
    var xOffset = (viewSize.w - rowWidth) / 2 + blockSize.w / 2;
    var yOffset = viewSize.h - colHeight - xOffset + blockSize.w;
    for(var x = 0; x < cols; x++) {
        for(var y = 0; y < rows; y++) {
            var block = createBox(blockSize.w, blockSize.h, "block", 0.8, 0.8, 0.8);
            block.getComponent("MeshRenderer").setTexture(TextureCache.getTexture("textures/brick.png"));
            block.transform.setPosition(xOffset + x * (blockSize.w + blockSpace.w),
                                        yOffset + y * (blockSize.h + blockSpace.h));
            var bc = block.addComponent(new BoxCollider(1.5, 0.75));
            bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});
            bc.onCollision = function(contact, otherCollider) {
                this.getParent().destroy();
                return true;
            };
        }
    }
}

function createPaddle() {
    var paddle = createBox(4, 0.5, "paddle", 0.8, 0.8, 0.8);
    paddle.transform.setPosition(viewSize.w / 2, 1);
    paddle.getComponent("MeshRenderer").setTexture(TextureCache.getTexture("textures/paddle.png"));
    var s = new Scriptable("Controls");
    s.onUpdate = function(delta) {
        var pos = paddle.transform.getPosition();
        if(keyboard.isKeyDown(keyboard.codes.left)) {
            pos.x -= (viewSize.w / 2.0) * delta;
        }
        if(keyboard.isKeyDown(keyboard.codes.right)) {
            pos.x += (viewSize.w / 2.0) * delta;
        }
        paddle.transform.setPosition(pos.x, pos.y, pos.z);
    };
    paddle.addComponent(s);
    var bc = paddle.addComponent(new BoxCollider(2, 0.25));
    bc.setPhysicsProperties({type: Collider.kinematic, restitution: 1, friction: 0, density: 10});
    return paddle;
}

function createBall() {
    var ball = new Entity("ball");
    ball.addComponent(Mesh.createRect(ballRadius * 2, ballRadius * 2));
    ball.addComponent(new MeshRenderer()).setColor(0.8, 0.8, 0.8).setShader(Shader.getDefaultShader());
    ball.transform.setPosition(viewSize.w / 2, viewSize.h / 3);

    ball.getComponent("MeshRenderer").setTexture(TextureCache.getTexture("textures/ball.png"));
    var cc = ball.addComponent(new CircleCollider(ballRadius));
    cc.setPhysicsProperties({type: Collider.dynamic, restitution: 1, friction: 0, density: 1});
    cc.setLinearVelocity(3, 5);
}

function createCamera() {
    var cameraObj = new Entity("Camera");
    var cam = cameraObj.addComponent(new Camera());
    cam.setOrtho(0, viewSize.w, 0, viewSize.h, -1, 100);
}

function createWalls() {
    var e = new Entity('left-wall');
    e.transform.setPosition(0, viewSize.h / 2);
    var bc = e.addComponent(new BoxCollider(0.1, viewSize.h));
    bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});

    e = new Entity('right-wall');
    e.transform.setPosition(viewSize.w, viewSize.h / 2);
    bc = e.addComponent(new BoxCollider(0.1, viewSize.h));
    bc.setPhysicsProperties({type: Collider.static, restitution: 1, friction: 0});

    e = new Entity('top-wall');
    e.transform.setPosition(viewSize.w / 2, viewSize.h);
    bc = e.addComponent(new BoxCollider(viewSize.w, 0.1));
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
        return true;
    }
}

function main() {
    flwindow.setSize(windowSize.w, windowSize.h);
    flwindow.setClearColor(0.2, 0.2, 0.2, 1);
    //flwindow.centerOnScreen();
    flwindow.setResizable(false);
    createCamera();

    createBoard(numBlocks.cols, numBlocks.rows);
    createWalls();
    createPaddle();
    createBall();
}
