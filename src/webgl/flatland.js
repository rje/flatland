
var b2Vec2 = Box2D.Common.Math.b2Vec2;
var b2BodyDef = Box2D.Dynamics.b2BodyDef;
var b2Body = Box2D.Dynamics.b2Body;
var b2FixtureDef = Box2D.Dynamics.b2FixtureDef;
var b2Fixture = Box2D.Dynamics.b2Fixture;
var b2PolygonShape = Box2D.Collision.Shapes.b2PolygonShape;
var b2World = Box2D.Dynamics.b2World;
var b2Transform = Box2D.Common.Math.b2Transform;
var b2CircleShape = Box2D.Collision.Shapes.b2CircleShape;
var b2ContactListener = Box2D.Dynamics.b2ContactListener;
var b2Contact = Box2D.Dynamics.Contacts.b2Contact;

flwindow = undefined;
PhysicsSystem = undefined;
keyboard = undefined;

window.requestAnimFrame = (function(){
          return  window.requestAnimationFrame       ||
                  window.webkitRequestAnimationFrame ||
                  window.mozRequestAnimationFrame    ||
                  window.oRequestAnimationFrame      ||
                  window.msRequestAnimationFrame     ||
                  function(/* function */ callback, /* DOMElement */ element){
                    window.setTimeout(callback, 1000 / 60);
                  };
    })();

function __extends(baseClass, subClass) {
    function inheritance() {}
    inheritance.prototype = baseClass.prototype;
    subClass.prototype = new inheritance();
    subClass.prototype.constructor = subClass;
    subClass.baseConstructor = baseClass;
    subClass.superClass = baseClass.prototype;
}

function flatland_init(canvas_id) {
    flwindow = new Window();
    flwindow.initialize(canvas_id);
    flwindow.setSize(1024, 768);
    main();
    window.requestAnimFrame(_flatland_tick, 1000/60);
}

function _flatland_tick() {
    var delta = 1.0 / 60.0;
    var time = (new Date()).getTime();
    if(this._lastUpdate != undefined) {
        delta = (time - this._lastUpdate) / 1000.0;
    }
    PhysicsSystem.doStep(delta);
    EntityRegistry.destroyMarked();
    EntityRegistry.callUpdates(delta);
    var renderer = flwindow.getRenderer();
    renderer.prepare();
    renderer.draw();
    PhysicsSystem.drawDebugData();
    renderer.flush();
    window.requestAnimFrame(_flatland_tick, 1000/60);
}

function Renderer() {
    var gl = flwindow.getGLContext();
    gl.enable(gl.BLEND);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
}

Renderer.prototype.prepare = function() {
    var gl = flwindow.getGLContext();
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
};

Renderer.prototype.draw = function() {
    var entityList = EntityRegistry.getEntityList();
    var cameraList = EntityRegistry.getCameraList();
    for(var cIdx = 0; cIdx < cameraList.length; cIdx++) {
        var camera = cameraList[cIdx];
        if(!camera.isEnabled) {
            continue;
        }
        // Setup shader vars
        for(var i = 0; i < entityList.length; i++) {
            var mr = entityList[i].getComponent("MeshRenderer");
            if(mr) {
                mr.render(camera);
            }
        }
    }
};

Renderer.prototype.flush = function() {

};

function Window() {
}

Window.prototype.getRenderer = function() {
    return this._renderer;
};

Window.prototype.getGLContext = function() {
    return this._gl;
};

Window.prototype.initialize = function(canvas_id) {
    this._canvas = document.getElementById(canvas_id);
    this._gl = this._canvas.getContext("experimental-webgl");
    this._width = this._canvas.width;
    this._height = this._canvas.height;
    this._gl.viewportWidth = this._canvas.width;
    this._gl.viewportHeight = this._canvas.height;
    this._gl.clearColor(0, 0, 0, 1);
    this._gl.viewport(0, 0, this._gl.viewportWidth, this._gl.viewportHeight);
    this._gl.enable(this._gl.DEPTH_TEST);
    this._gl.clear(this._gl.COLOR_BUFFER_BIT | this._gl.DEPTH_BUFFER_BIT);
    this._renderer = new Renderer();
    this._createDefaultShader();
    PhysicsSystem = new PhysicsSystemImpl();
    keyboard = new KeyboardHandler();
    keyboard.register();
};

Window.prototype._createDefaultShader = function() {
    if(Shader.defaultShader) {
        return;
    }

    var defaultNoTextureVertShader = "attribute vec4 position;" +
                                     "uniform mat4 u_pMatrix;" +
                                     "uniform mat4 u_mvMatrix;" +
                                     "" +
                                     "void main() {" +
                                     "    gl_Position = u_pMatrix * u_mvMatrix * position;" +
                                     "}";
    var defaultNoTextureFragShader = "precision lowp float;" +
                                     "uniform vec4 u_color;" +
                                     "" +
                                     "void main() {" +
                                     "    gl_FragColor = u_color;" +
                                     "}";

    var defaultVertShader = "attribute vec4 position;" +
                            "attribute vec2 uv;" +
                            "uniform mat4 u_pMatrix;" +
                            "uniform mat4 u_mvMatrix;" +
                            "varying vec2 v_texCoords;" +
                            "" +
                            "void main() {" +
                            "    v_texCoords = uv;" +
                            "    gl_Position = u_pMatrix * u_mvMatrix * position;" +
                            "}";

    var defaultFragShader = "precision lowp float;" +
                            "uniform vec4 u_color;" +
                            "uniform sampler2D u_tex;" +
                            "varying vec2 v_texCoords;" +
                            "" +
                            "void main() {" +
                            "    gl_FragColor = texture2D(u_tex, v_texCoords) * u_color;" +
                            "}";


    var shader = new Shader();
    var fs = new FragmentShader();
    fs.setSource(defaultFragShader);
    fs.compile();
    shader.addFragmentShader(fs);

    var vs = new VertexShader();
    vs.setSource(defaultVertShader);
    vs.compile();
    shader.addVertexShader(vs);

    shader.linkShader();
    Shader.defaultShader = shader;

    shader = new Shader();
    fs = new FragmentShader();
    fs.setSource(defaultNoTextureFragShader);
    fs.compile();
    shader.addFragmentShader(fs);

    vs = new VertexShader();
    vs.setSource(defaultNoTextureVertShader);
    vs.compile();
    shader.addVertexShader(vs);

    shader.linkShader();
    Shader.defaultNoTextureShader = shader;
};

Window.prototype.setSize = function(w, h) {
    this._width = w;
    this._height = h;
    this._canvas.width = w;
    this._canvas.height = h;
    this._gl.viewportWidth = w;
    this._gl.viewportHeight = h;
    this._gl.viewport(0, 0, w, h);
    this._gl.clear(this._gl.COLOR_BUFFER_BIT | this._gl.DEPTH_BUFFER_BIT);
};

Window.prototype.getSize = function() {
    return {width: this._width, height: this._height};
};

Window.prototype.setClearColor = function(r, g, b, a) {
    this._gl.clearColor(r, g, b, a);
};

Window.prototype.setResizable = function(shouldResize) {

};

Window.prototype.centerOnScreen = function() {

};

var EntityRegistry = {
    _entities: [],

    _cameras: [],

    register: function(entity) {
        if(this._entities.indexOf(entity) == -1) {
            this._entities.push(entity);
        }
    },

    unregister: function(entity) {
        var idx = this._entities.indexOf(entity);
        if(idx != -1) {
            this._entities.splice(idx, 1);
        }
    },

    destroyMarked: function() {
        for(var i = this._entities.length - 1; i >= 0; i--) {
            this._entities[i].destroyIfMarked();
        }
    },

    addCamera: function(toAdd) {
        this._cameras.push(toAdd);
    },

    removeCamera: function(toRemove) {

    },

    callUpdates: function(delta) {
        for(var i = 0; i < this._entities.length; i++) {
            this._entities[i].update(delta);
        }
    },

    getEntityList: function() {
        return this._entities;
    },

    getCameraList: function() {
        return this._cameras;
    }
};

function Entity(name) {
    this._name = name;
    this._components = [];
    this.transform = new Transform();
    this.addComponent(this.transform);
    EntityRegistry.register(this);
}

Entity.prototype.destroy = function() {
    this._shouldDestroy = true;
};

Entity.prototype.destroyIfMarked = function() {
    if(this._shouldDestroy) {
        EntityRegistry.unregister(this);
        for(var i = 0; i < this._components.length; i++) {
            this._components[i].destroy();
        }
    }
};

Entity.prototype.addComponent = function(toAdd) {
    if(this._components.indexOf(toAdd) == -1) {
        this._components.push(toAdd);
        toAdd.setParent(this);
        if(toAdd.register) {
            toAdd.register();
        }
    }
    return toAdd;
};

Entity.prototype.removeComponent = function(toRemove) {
    var idx = this._components.indexOf(toRemove);
    if(idx != -1) {
        this._components[i].setParent(undefined);
        this._components.slice(idx, 1);
    }
};

Entity.prototype.getComponent = function(type) {
    for(var i = 0; i < this._components.length; i++) {
        if(this._components[i]._type === type) {
            return this._components[i];
        }
    }

    return undefined;
};

Entity.prototype.update = function(delta) {
    for(var i = 0; i < this._components.length; i++) {
        if(this._components[i].update) {
            this._components[i].update(delta);
        }
    }
};

Entity.prototype.getCollider = function() {
    for(var i = 0; i < this._components.length; i++) {
        if(this._components[i]._type.indexOf("Collider") != -1) {
            return this._components[i];
        }
    }
    return undefined;
};

function Transform() {
    this._type = "Transform";
    this._position = {x: 0, y: 0, z: 0};
}
__extends(Component, Transform);

Transform.prototype.getPosition = function() {
    return this._position;
};

Transform.prototype.setPosition = function(x, y, z) {
    this._position.x = x;
    this._position.y = y;
    if(z) {
        this._position.z = z;
    }
    var collider = this.getParent().getCollider();
    if(collider) {
        collider.updateWithTransform(this, true, false);
    }
};

Transform.prototype.getMatrix = function() {
    return mat4.translate(mat4.identity(), vec3.createFrom(this._position.x, this._position.y, this._position.z));
};

function Mesh() {
    this._type = "Mesh";
    this._vertBuffer = undefined;
    this._uvBuffer = undefined;
    this._indexBuffer = undefined;
}
__extends(Component, Mesh);

Mesh.prototype.destroy = function() {
    var gl = flwindow.getGLContext();
    gl.deleteBuffer(this._vertBuffer);
    gl.deleteBuffer(this._uvBuffer);
    gl.deleteBuffer(this._indexBuffer);
};

Mesh.prototype.createBuffers = function() {
    var gl = flwindow.getGLContext();
    this._vertBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, this._vertBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this._verts), gl.STATIC_DRAW);

    this._uvBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, this._uvBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this._uvs), gl.STATIC_DRAW);

    this._indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(this._indices), gl.STATIC_DRAW);
};

Mesh.prototype.bindBuffers = function() {
    var gl = flwindow.getGLContext();
    gl.enableVertexAttribArray(0);
    gl.enableVertexAttribArray(1);
    gl.bindBuffer(gl.ARRAY_BUFFER, this._vertBuffer);
    gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, this._uvBuffer);
    gl.vertexAttribPointer(1, 2, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this._indexBuffer);
};

Mesh.createRect = function(width, height) {
    var m = new Mesh();
    m._verts = [];
    m._uvs = [];
    m._indices = [];
    var wd2 = width / 2.0;
    var hd2 = height / 2.0;
    for(var i = 0; i < 4; i++) {
        var base = i * 3;
        m._verts[base + 0] = (i % 2 == 0) ? -wd2 : wd2;
        m._verts[base + 1] = (i < 2) ? -hd2 : hd2;
        m._verts[base + 2] = 0;

        base = i * 2;
        m._uvs[base + 0] = (i % 2 == 0) ? 0 : 1;
        m._uvs[base + 1] = (i < 2) ? 1 : 0;
    }
    m._indices[0] = 0;
    m._indices[1] = 1;
    m._indices[2] = 2;
    m._indices[3] = 1;
    m._indices[4] = 2;
    m._indices[5] = 3;
    m._indexCount = 6;
    m._meshType = flwindow.getGLContext().TRIANGLES;

    m.createBuffers();

    return m;
};

Mesh.createCircle = function(radius, numPoints) {
    var m = new Mesh();
    m._verts = [];
    m._uvs = [];
    m._indices = [];
    for(var i = 0; i < numPoints; i++) {
        var base = i * 3;
        var cx = Math.cos(2 * Math.PI * i / numPoints);
        var sy = Math.sin(2 * Math.PI * i / numPoints);
        m._verts[base + 0] = radius * cx;
        m._verts[base + 1] = radius * sy;
        m._verts[base + 2] = 0;

        base = i * 2;
        m._uvs[base + 0] = 0.5 + cx / 2;
        m._uvs[base + 1] = 0.5 + sy / 2;

        m._indices[i] = i;
    }
    m._indexCount = numPoints;
    m._meshType = flwindow.getGLContext().TRIANGLE_FAN;

    return m;
};

function Component() {

}

Component.prototype.destroy = function() {

};

Component.prototype.getParent = function() {
    return this._parent;
};

Component.prototype.setParent = function(parent) {
    this._parent = parent;
};

function MeshRenderer() {
    this._type = "MeshRenderer";
    this._color = {r: 1.0, g: 1.0, b: 1.0, a: 1.0};
    this._texture = undefined;
    this._shader = undefined;
}
__extends(Component, MeshRenderer);

MeshRenderer.prototype.setColor = function(r, g, b, a) {
    this._color.r = r;
    this._color.g = g;
    this._color.b = b;
    if(a) {
        this._color.a = a;
    }

    return this;
};

MeshRenderer.prototype.getColor = function() {
    return this._color;
};

MeshRenderer.prototype.setTexture = function(texture) {
    this._texture = texture;

    return this;
};

MeshRenderer.prototype.getTexture = function() {
    return this._texture;
};

MeshRenderer.prototype.setShader = function(shader) {
    this._shader = shader;

    return this;
};

MeshRenderer.prototype.getShader = function() {
    return this._shader;
};

MeshRenderer.prototype.render = function(camera) {
    if(this._shader) {
        this._shader.useShader();
    }
    var gl = flwindow.getGLContext();
    var m = this.getParent().getComponent("Mesh");
    m.bindBuffers();
    gl.uniform4f(gl.getUniformLocation(this._shader._program, "u_color"), this._color.r, this._color.g, this._color.b, this._color.a);
    if(this._texture) {
        this._texture.bind();
        gl.uniform1i(gl.getUniformLocation(this._shader._program, "u_tex"), this._texture.getTextureID());
    }
    gl.uniformMatrix4fv(gl.getUniformLocation(this._shader._program, "u_pMatrix"), false, camera.getMatrix());
    var trans = this.getParent().transform.getMatrix();
    gl.uniformMatrix4fv(gl.getUniformLocation(this._shader._program, "u_mvMatrix"), false, trans);
    gl.drawElements(m._meshType, m._indexCount, gl.UNSIGNED_BYTE, 0);
};

function Camera() {
    this._enabled = true;
    this._matrix = mat4.identity();
    this._type = "Camera";
}
__extends(Component, Camera);

Camera.prototype.register = function() {
    EntityRegistry.addCamera(this);
};

Camera.prototype.destroy = function() {
    EntityRegistry.removeCamera(this);
};

Camera.prototype.setOrtho = function(left, right, bottom, top, near, far) {
    this._matrix = mat4.ortho(left, right, bottom, top, near, far);
};

Camera.prototype.setPerspective = function(fovy, aspect, near, far) {
    this._matrix = mat4.perspective(fovy, aspect, near, far);
};

Camera.prototype.getMatrix = function() {
    return this._matrix;
};

Camera.prototype.isEnabled = function() {
    return this._enabled;
};

function Shader() {
    this._fragShaders = [];
    this._vertShaders = [];
    this._program = undefined;
}

Shader.getDefaultShader = function() {
    return Shader.defaultShader;
};

Shader.getDefaultNoTextureShader = function() {
    return Shader.defaultNoTextureShader;
}

Shader.prototype.addVertexShader = function(toAdd) {
    this._vertShaders.push(toAdd);
};

Shader.prototype.addFragmentShader = function(toAdd) {
    this._fragShaders.push(toAdd);
};

Shader.prototype.linkShader = function() {
    var gl = flwindow.getGLContext();
    this._program = gl.createProgram();
    var i;
    for(i = 0; i < this._vertShaders.length; i++) {
        gl.attachShader(this._program, this._vertShaders[i].getShaderID());
    }
    for(i = 0; i < this._fragShaders.length; i++) {
        gl.attachShader(this._program, this._fragShaders[i].getShaderID());
    }
    gl.bindAttribLocation(this._program, 0, "position");
    gl.linkProgram(this._program);

    if (!gl.getProgramParameter(this._program, gl.LINK_STATUS)) {
        var err = gl.getProgramInfoLog(this._program);
        gl.deleteProgram(this._program);
        this._program = undefined;
        throw new Error(err);
    }
};

Shader.prototype.useShader = function() {
    if(this._program) {
        var gl = flwindow.getGLContext();
        gl.useProgram(this._program);
    }
};

function FragmentShader() {
    this._shaderID = undefined;
}

FragmentShader.prototype.getShaderID = function() {
    return this._shaderID;
};

FragmentShader.prototype.setSource = function(src) {
    this._src = src;
};

FragmentShader.prototype.compile = function() {
    var gl = flwindow.getGLContext();
    this._shaderID = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(this._shaderID, this._src);
    gl.compileShader(this._shaderID);
    if (!gl.getShaderParameter(this._shaderID, gl.COMPILE_STATUS)) {
        var err = gl.getShaderInfoLog(this._shaderID);
        gl.deleteShader(this._shaderID);
        throw new Error(err);
    }
};

function VertexShader() {
    this._shaderID = undefined;
}

VertexShader.prototype.getShaderID = function() {
    return this._shaderID;
};

VertexShader.prototype.setSource = function(src) {
    this._src = src;
};

VertexShader.prototype.compile = function() {
    var gl = flwindow.getGLContext();
    this._shaderID = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(this._shaderID, this._src);
    gl.compileShader(this._shaderID);
    if (!gl.getShaderParameter(this._shaderID, gl.COMPILE_STATUS)) {
        var err = gl.getShaderInfoLog(this._shaderID);
        gl.deleteShader(this._shaderID);
        throw new Error(err);
    }
};

Collider = function() {
    this._type = "Collider";
    this._friction = 1.0;
    this._restitution = 0.0;
    this._density = 1.0;
    this._bodyType = Collider.static;
    this._body = undefined;
    this._shape = undefined;
};
__extends(Component, Collider);

Collider.prototype.destroy = function() {
    PhysicsSystem.destroyCollider(this);
};

Collider.static = b2Body.b2_staticBody;
Collider.kinematic = b2Body.b2_kinematicBody;
Collider.dynamic = b2Body.b2_dynamicBody;

Collider.prototype.getBody = function() {
    return this._body;
};

Collider.prototype.getBodyShape = function() {
    return this._shape;
};

Collider.prototype.getBodyType = function() {
    return this._bodyType;
};

Collider.prototype.setBodyType = function(bodyType) {
    this._bodyType = bodyType;
    if(this._body) {
        this._body.SetType(bodyType);
    }
};

Collider.prototype.getRestitution = function() {
    return this._restitution;
};

Collider.prototype.setRestitution = function(rest) {
    this._restitution = rest;
    if(this._body) {
        this._body.GetFixtureList().SetRestitution(rest);
    }
};

Collider.prototype.getFriction = function() {
    return this._friction;
};

Collider.prototype.setFriction = function(friction) {
    this._friction = friction;
    if(this._body) {
        this._body.GetFixtureList().SetFriction(friction);
    }
};

Collider.prototype.getDensity = function() {
    return this._density;
};

Collider.prototype.setDensity = function(density) {
    this._density = density;
    if(this._body) {
        this._body.GetFixtureList().SetDensity(density);
    }
};

Collider.prototype.setPhysicsProperties = function(props) {
    if(props.hasOwnProperty("type")) {
        this.setBodyType(props['type']);
    }
    if(props.hasOwnProperty("restitution")) {
        this.setRestitution(props['restitution']);
    }
    if(props.hasOwnProperty("friction")) {
        this.setFriction(props['friction']);
    }
    if(props.hasOwnProperty("density")) {
        this.setDensity(props['density']);
    }
};

Collider.prototype.setLinearVelocity = function(x, y) {
    this._body.SetLinearVelocity(new b2Vec2(x, y));
};

Collider.prototype.getLinearVelocity = function() {
    var vec = this._body.GetLinearVelocity();
    return {x: vec.x, y: vec.y};
};

Collider.prototype.update = function(delta) {
    var trans = this.getParent().transform;
    var vec = this._body.GetPosition();
    trans.setPosition(vec.x, vec.y);
    //TODO: Set Angle
};

Collider.prototype.register = function() {
    this._body = PhysicsSystem.registerCollider(this);
    var xform = this.getParent().transform;
    if(xform) {
        this.updateWithTransform(xform, true, true);
    }
};

Collider.prototype.updateWithTransform = function(xform, shouldUpdatePos, shouldUpdateAngle) {
    if(shouldUpdatePos) {
        var pos = xform.getPosition();
        this._body.SetPosition(new b2Vec2(pos.x, pos.y));
    }
    if(shouldUpdateAngle) {

    }
};

Collider.prototype.handleCollision = function(contact, otherCollider) {
    if(this.onCollision) {
        return this.onCollision(contact, otherCollider);
    }
    return false;
};

function BoxCollider(halfWidth, halfHeight) {
    BoxCollider.baseConstructor.call(this, undefined);
    this._type = "BoxCollider";
    this._halfWidth = halfWidth;
    this._halfHeight = halfHeight;
    this._shape = new b2PolygonShape();
    this._shape.SetAsBox(halfWidth, halfHeight);
}
__extends(Collider, BoxCollider);

BoxCollider.prototype.getSize = function() {
    return {halfWidth: this._halfWidth, halfHeight: this._halfHeight};
};

BoxCollider.prototype.setSize = function(hw, hh) {
    this._halfWidth = hw;
    this._halfHeight = hh;
    this._shape.SetAsBox(hw, hh);
};

function CircleCollider(radius) {
    CircleCollider.baseConstructor.call(this, undefined);
    this._type = "CircleCollider";
    this._radius = radius;
    this._shape = new b2CircleShape();
    this._shape.SetRadius(radius);
}
__extends(Collider, CircleCollider);

CircleCollider.prototype.getSize = function() {
    return this._radius;
};

CircleCollider.prototype.setSize = function(radius) {
    this._radius = radius;
    this._shape.SetRadius(radius);
};

var b2DebugDraw = Box2D.Dynamics.b2DebugDraw;

function PhysicsSystemImpl() {
    this._world = new b2World(new b2Vec2(0.0, 0.0));

    var debugDraw = new FlatlandDebugDraw();
    this._world.SetDebugDraw(debugDraw);
    this._colliders = [];
    this._contactListener = new b2ContactListener();
    this._contactListener.BeginContact = function(contact) {
        var a = contact.GetFixtureA().GetBody();
        var b = contact.GetFixtureB().GetBody();
        var ac = a.GetUserData();
        var bc = b.GetUserData();
        if(!ac.handleCollision(contact, bc)) {
            bc.handleCollision(contact, ac);
        }
    };
    this._world.SetContactListener(this._contactListener);
}

PhysicsSystemImpl.prototype.getGravity = function() {
    var g = this._world.GetGravity();
    var toReturn = {};
    toReturn.x = g.x;
    toReturn.y = g.y;
    return toReturn;
};

PhysicsSystemImpl.prototype.setGravity = function(x, y) {
    this._world.SetGravity(new b2Vec2(x, y));
};

PhysicsSystemImpl.prototype.doStep = function(delta) {
    this._world.Step(delta, 8, 3);
};

PhysicsSystemImpl.prototype.registerCollider = function(collider) {
    if(this._colliders.indexOf(collider) == -1) {
        var bodyDef = new b2BodyDef();
        bodyDef.userData = collider;
        bodyDef.type = collider.getBodyType();
        var toReturn = this._world.CreateBody(bodyDef);
        var shape = collider.getBodyShape();
        var fix = toReturn.CreateFixture2(shape, collider.getDensity());
        fix.SetFriction(collider.getFriction());
        fix.SetRestitution(collider.setRestitution());
        this._colliders.push(collider);
        return toReturn;
    }
};

PhysicsSystemImpl.prototype.destroyCollider = function(collider) {
    this._world.DestroyBody(collider.getBody());
};

PhysicsSystemImpl.prototype.drawDebugData = function() {
    this._world.DrawDebugData();
};

function FlatlandDebugDraw() {
    //this.m_drawFlags = b2DebugDraw.e_shapeBit | b2DebugDraw.e_aabbBit;
}

FlatlandDebugDraw.prototype.DrawPolygon = function (vertices, vertexCount, color) {
    var shader = Shader.defaultNoTextureShader;
    shader.useShader();
    var gl = flwindow.getGLContext();
    var vertBuffer = gl.createBuffer();
    var verts = [];
    var indices = [];
    for(var i = 0; i < vertexCount; i++) {
        verts[i * 3 + 0] = vertices[i].x;
        verts[i * 3 + 1] = vertices[i].y;
        verts[i * 3 + 2] = 0;
        indices[i] = i;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, vertBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);

    var indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(indices), gl.STATIC_DRAW);

    gl.enableVertexAttribArray(0);
    gl.disableVertexAttribArray(1);
    gl.bindBuffer(gl.ARRAY_BUFFER, vertBuffer);
    gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

    var camera = EntityRegistry.getCameraList()[0];
    var mat = mat4.identity();

    gl.uniform4f(gl.getUniformLocation(shader._program, "u_color"), color.r, color.g, color.b, 0.4);
    gl.uniformMatrix4fv(gl.getUniformLocation(shader._program, "u_pMatrix"), false, camera.getMatrix());
    gl.uniformMatrix4fv(gl.getUniformLocation(shader._program, "u_mvMatrix"), false, mat);
    gl.drawElements(gl.LINE_LOOP, vertexCount, gl.UNSIGNED_BYTE, 0);

};

FlatlandDebugDraw.prototype.DrawSolidPolygon = function (vertices, vertexCount, color) {
    var shader = Shader.defaultNoTextureShader;
    shader.useShader();
    var gl = flwindow.getGLContext();
    var vertBuffer = gl.createBuffer();
    var verts = [];
    var indices = [];
    for(var i = 0; i < vertexCount; i++) {
        verts[i * 3 + 0] = vertices[i].x;
        verts[i * 3 + 1] = vertices[i].y;
        verts[i * 3 + 2] = 0;
        indices[i] = i;
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, vertBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);

    var indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(indices), gl.STATIC_DRAW);

    gl.enableVertexAttribArray(0);
    gl.disableVertexAttribArray(1);
    gl.bindBuffer(gl.ARRAY_BUFFER, vertBuffer);
    gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);

    var camera = EntityRegistry.getCameraList()[0];
    var mat = mat4.identity();

    gl.uniform4f(gl.getUniformLocation(shader._program, "u_color"), color.r, color.g, color.b, 0.4);
    gl.uniformMatrix4fv(gl.getUniformLocation(shader._program, "u_pMatrix"), false, camera.getMatrix());
    gl.uniformMatrix4fv(gl.getUniformLocation(shader._program, "u_mvMatrix"), false, mat);
    gl.drawElements(gl.TRIANGLE_FAN, vertexCount, gl.UNSIGNED_BYTE, 0);

    gl.deleteBuffer(vertBuffer);
    gl.deleteBuffer(indexBuffer);
};

FlatlandDebugDraw.prototype.DrawCircle = function (center, radius, color) {

};

FlatlandDebugDraw.prototype.DrawSolidCircle = function (center, radius, axis, color) {

};

FlatlandDebugDraw.prototype.DrawSegment = function (p1, p2, color) {

};

FlatlandDebugDraw.prototype.DrawTransform = function (xf) {

};

FlatlandDebugDraw.prototype.SetFlags = function (flags) {
    if (flags === undefined) flags = 0;
    this.m_drawFlags = flags;
};

FlatlandDebugDraw.prototype.GetFlags = function () {
    return this.m_drawFlags;
};

FlatlandDebugDraw.prototype.AppendFlags = function (flags) {
    if (flags === undefined) flags = 0;
    this.m_drawFlags |= flags;
};

FlatlandDebugDraw.prototype.ClearFlags = function (flags) {
    if (flags === undefined) flags = 0;
    this.m_drawFlags &= ~flags;
};

function KeyboardHandler() {
    this._keyData = {};
    this.codes = {
        left: 37,
        right: 39,
        up: 38,
        down: 40
    };
}

KeyboardHandler.prototype.register = function() {
    var $this = this;
    document.onkeydown = function(event) {
        $this._keyData[event.keyCode] = true;
    };
    document.onkeyup = function(event) {
        $this._keyData[event.keyCode] = false;
    }
};

KeyboardHandler.prototype.isKeyDown = function(code) {
    return this._keyData[code];
};

function Scriptable(name) {
    this._type = "Scriptable";
    this._name = name;
}
__extends(Component, Scriptable);

Scriptable.prototype.update = function(delta) {
    if(this.onUpdate) {
        this.onUpdate(delta);
    }
};

TextureCache = {
    _cache: {},

    getTexture: function(name) {
        if(!this._cache[name]) {
            this._cache[name] = this._loadTexture(name);
        }
        return this._cache[name];
    },

    _loadTexture: function(name) {
        var tex = new Texture();
        tex.loadImage(name);
        return tex;
    }
};

function Texture() {

}

Texture.prototype.loadImage = function(src) {
    var gl = flwindow.getGLContext();
    this._texID = gl.createTexture();
    var img = new Image();
    var $this = this;
    img.onload = function() {
        console.log(src + " loaded");
        gl.bindTexture(gl.TEXTURE_2D, $this._texID);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
        gl.generateMipmap(gl.TEXTURE_2D);
        gl.bindTexture(gl.TEXTURE_2D, null);
    };
    img.src = src;
};

Texture.prototype.bind = function() {
    var gl = flwindow.getGLContext();
    gl.bindTexture(gl.TEXTURE_2D, this._texID);
};

Texture.prototype.getTextureID = function() {
    return this._texID;
};