Mesh = function (objectData) {

  var verts = [], vertNormals = [], textures = [], colors = [], unpacked = {};
  // unpacking stuff
  unpacked.verts = [];
  unpacked.norms = [];
  unpacked.textures = [];
  unpacked.colors = [];
  unpacked.hashindices = {};
  unpacked.indices = [];
  unpacked.index = 0;
  // array of lines separated by the newline
  var lines = objectData.split('\n');
  
  var VERTEX_RE = /^v\s/;
  var NORMAL_RE = /^vn\s/;
  var TEXTURE_RE = /^vt\s/;
  var FACE_RE = /^f\s/;
  var WHITESPACE_RE = /\s+/;
  for (var i = 0; i < lines.length; i++) {
    var line = lines[i].trim();
    var elements = line.split(WHITESPACE_RE);
    //console.log(elements)
    elements.shift();
    if (VERTEX_RE.test(line)) {
      // if this is a vertex
      verts.push.apply(verts, elements);
    } else if (NORMAL_RE.test(line)) {
      // if this is a vertex normal
      vertNormals.push.apply(vertNormals, elements);
    } else if (TEXTURE_RE.test(line)) {
      // if this is a texture
      textures.push.apply(textures, elements);
    } else if (FACE_RE.test(line)) {
      // if this is a face
      /*
      split this face into an array of vertex groups
      for example:
        f 16/92/11 14/101/22 1/69/1
      becomes:
        ['16/92/11', '14/101/22', '1/69/1'];
      */
      var quad = false;
      for (var j = 0, eleLen = elements.length; j < eleLen; j++){
          if( elements.length==3){
            if(elements[j] in unpacked.hashindices){
              unpacked.indices.push(unpacked.hashindices[elements[j]]);
            }else{
              var vertex = elements[ j ].split( '/' );
              // vertex position
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 0]);
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 1]);
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 2]);
              // vertex textures
              if (textures.length) {
                unpacked.textures.push(+textures[(vertex[1] - 1) * 2 + 0]);
                unpacked.textures.push(+textures[(vertex[1] - 1) * 2 + 1]);
              }else{
                unpacked.textures.push(+1);
                unpacked.textures.push(+1);
              }
              // vertex normals
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 0]);
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 1]);
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 2]);
              // add the newly created vertex to the list of indices
              unpacked.colors.push(0.4);
              unpacked.colors.push(0.6);
              unpacked.colors.push(0.8);
              unpacked.colors.push(1);
              unpacked.hashindices[elements[j]] = unpacked.index;
              unpacked.indices.push(unpacked.index);
              // increment the counter
              unpacked.index += 1;
            }
          } else {
          // Triangulating quads
          // quad: 'f v0/t0/vn0 v1/t1/vn1 v2/t2/vn2 v3/t3/vn3/'
          // corresponding triangles:
          //      'f v0/t0/vn0 v1/t1/vn1 v2/t2/vn2'
          //      'f v2/t2/vn2 v3/t3/vn3 v0/t0/vn0'
          if(j === 3 && !quad) {
              // add v2/t2/vn2 in again before continuing to 3
              j = 2;
              quad = true;
          }
          if(elements[j] in unpacked.hashindices){
              unpacked.indices.push(unpacked.hashindices[elements[j]]);
          }
          else{
              var vertex = elements[ j ].split( '/' );
              // vertex position
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 0]);
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 1]);
              unpacked.verts.push(+verts[(vertex[0] - 1) * 3 + 2]);
              // vertex textures
              if (vertex[1].length) {
                unpacked.textures.push(+textures[(vertex[1] - 1) * 2 + 0]);
                unpacked.textures.push(+textures[(vertex[1] - 1) * 2 + 1]);
              }else{
                unpacked.textures.push(+1);
                unpacked.textures.push(+1);
              }
              // vertex normals
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 0]);
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 1]);
              unpacked.norms.push(+vertNormals[(vertex[2] - 1) * 3 + 2]);

              unpacked.colors.push(0.4);
              unpacked.colors.push(0.6);
              unpacked.colors.push(0.8);
              unpacked.colors.push(1);
              // add the newly created vertex to the list of indices
              unpacked.hashindices[elements[j]] = unpacked.index;
              unpacked.indices.push(unpacked.index);
              // increment the counter
              unpacked.index += 1;
          }
          if(j === 3 && quad) {
              // add v0/t0/vn0 onto the second triangle
              unpacked.indices.push( unpacked.hashindices[elements[0]]);
          }
        }
      }
    }
  }
  this.vertices = new Float32Array(unpacked.verts);
  this.vertexNormals = new Float32Array(unpacked.norms);
  this.textures = new Float32Array(unpacked.textures);
  this.colors = new Float32Array(unpacked.colors);
  this.indices = new Float32Array(unpacked.indices);
}