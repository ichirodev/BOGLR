 #version 120

 attribute vec3 position;
 attribute vec2 textCoord;

 varying vec2 textCoord0;

 void main()
 {
     gl_Position = vec4(position, 1.0);
     textCoord0 = textCoord;
 }