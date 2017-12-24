function animate() {
    app.timeNow = new Date().getTime();
    app.elapsed = app.timeNow - app.lastTime;
    if (app.lastTime != 0) {
      // animate stuff
      if( !app.camera.disable ){
        cameraMove();
      }
      if( app.camera.shake ){
        cameraShake();
      }
    }
    app.lastTime = app.timeNow;
  }
  
  function tick() {
    requestAnimFrame(tick);
    app.drawScene();
    animate();
  }
  
  function webGLStart( meshes ) {
    app.meshes = meshes;
    canvas = document.getElementById("mycanvas");
    initGL(canvas);
    initShaders();
    initBuffers();
    initTunnel();
    initPointerLock();
    initTextures();
  
    document.onkeydown = cameraKeyDownHandler;
    document.onkeyup = cameraKeyUpHandler;
  
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
  
    tick();
  }
