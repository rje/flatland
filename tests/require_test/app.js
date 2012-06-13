var o = require('./lib/other.js');
var o2 = require('./lib/other2.js');

function main() {
    var result = o.c(o2.a, o2.b);
    console.log("3 = " + result);
}
