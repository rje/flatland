
util = {
inspect: function(toShow) {
    return this._genInspectString(toShow, 0);
},
    
_tabs: function(cnt) {
    var toRet = "";
    for(var i = 0; i < cnt; i++) {
        toRet += "  ";
    }
    return toRet;
},
    
_genInspectString: function(toShow, tabdepth) {
    var str = "";
    if(tabdepth === undefined) {
        tabdepth = 0;
    }
    
    switch(typeof(toShow)) {
        case "number":
        case "undefined":
        case "boolean":
            str += toShow;
            break;
        case "string":
            str += "\"" + toShow + "\"";
            break;
        case "function":
            str = "function()";
            break;
        case "object":
            str += "{\n";
            for(var key in toShow) {
                if(typeof(toShow[key]) === "function") {
                    str += this._tabs(tabdepth + 1) + key + ": function(),\n";
                    continue;
                }
                str += this._tabs(tabdepth + 1) + key + ": " + this._genInspectString(toShow[key], tabdepth + 1) + ",\n";
            }
            str += this._tabs(tabdepth) + "}";
            break;
    }
    return str;
}
};