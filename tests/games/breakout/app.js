
function createWhiteBox(w, h, name) {
    var e = new Entity(name);
    e.addComponent(Mesh.createRect(w, h));
    var mr = new MeshRenderer();
    mr.setColor(1, 1, 1, 1);
    e.addComponent(mr);
    return e;
}

function createBoard(cols, rows) {
    var blockSize = {w: 64, h: 32};
    var blockSpace = {w: 6, h: 6};
    var screenSize = window.getSize();
    var rowWidth = cols * blockSize.w + (cols - 1) * blockSpace.w;
    var colHeight = rows * blockSize.h + (rows - 1) * blockSpace.h;
    var xOffset = (screenSize.width - rowWidth) / 2;
    var yOffset = screenSize.height - colHeight - xOffset;
    for(var x = 0; x < cols; x++) {
        for(var y = 0; y < rows; y++) {
            var block = createWhiteBox(blockSize.w, blockSize.h, "block");
            var t = block.getComponent("Transform");
            t.setPosition(xOffset + x * (blockSize.w + blockSpace.w),
                yOffset + y * (blockSize.h + blockSpace.h));
        }
    }
}

function createPaddle() {
    var screenSize = window.getSize();
    var paddle = createWhiteBox(128, 16, "paddle");
    var t = paddle.getComponent("Transform");
    t.setPosition(screenSize.width / 2 - 64, 32);
    return paddle;
}

function createBall() {
    var screenSize = window.getSize();
    var ball = createWhiteBox(16, 16, "ball");
    var t = ball.getComponent("Transform");
    t.setPosition(screenSize.width / 2 - 8, 200);
}

function main() {
    window.setSize(800, 600);
    window.setResizable(false);
    createBoard(10, 6);
    createPaddle();
    createBall();
}

main();