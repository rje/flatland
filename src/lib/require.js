function require(file) {
  //console.log('requiring: ' + file);
  if(this._cache === undefined) {
    //console.log('  ->> creating require cache');
    this._cache = {};
  }
  if(this._cache[file]) {
    //console.log('  ->> found existing module, short circuiting');
    return this._cache[file];
  }
  else {
    //console.log('  ->> calling load for: ' + file);
    this._cache[file] = {};
    var results = _loadfile(file);
    //console.log('  ->> to copy over for file: ' + file);
    //console.log(util.inspect(results));
    for(var name in results) {
      this._cache[file][name] = results[name];
    }
    //console.log('  ->> results for file: ' + file);
    //console.log(util.inspect(this._cache[file]));
  }
  return this._cache[file];
}
