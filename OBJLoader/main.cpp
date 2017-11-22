#include "vector.h"
#include "mesh.h"
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

using namespace std;

// Some global variables:
int windowW = 1366;
int windowH = 768;
float focale = 65.0f;
float near = 0.1f;
float far = 100.0f;
float zoom = 1.0f;
// Mesh creation
Mesh mesh;


// callback functions
GLvoid affichage() { mesh.affichage(); }
GLvoid redimensionner(int w, int h);
GLvoid clavier(unsigned char touche, int x, int y);
void specialKeys( int key, int x, int y );



int main(int argc, char *argv[]) {
   mesh.readOBJ("TieFighter.obj");
   // Initialisation de GLUT
   glutInit(&argc, argv);
   // Choix du mode d'affichage (ici RVB)
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   // Position initiale de la fenetre GLUT
   glutInitWindowPosition(200, 200);
   // Taille initiale de la fenetre GLUT
   glutInitWindowSize(windowW, windowH);
   // Creation de la fenetre GLUT
   glutCreateWindow("Load OBJ");
   
   // With help from NeHe tutorial
   // Enable Texture Mapping
   glEnable(GL_TEXTURE_2D);
   glClearDepth(1.0f);
   // Depth Buffer Setup
   glEnable(GL_DEPTH_TEST);
   // Enable Z-buffer depth test
   glEnable(GL_DEPTH_TEST);
   // The Type Of Depth Testing To Do
   glDepthFunc(GL_LEQUAL);
   // Really Nice Perspective
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

   // Définition de la couleur d'effacement du framebuffer
   glClearColor(0.0f,0.0f,0.0f,0.0f);


   // Définition des fonctions de callbacks
   glutDisplayFunc(affichage);
   glutKeyboardFunc(clavier);
   glutReshapeFunc(redimensionner);
   glutSpecialFunc(specialKeys);

   // Lancement de la boucle infinie GLUT
   glutMainLoop();

   return 0;
}

// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {
   // Garde les valeurs
   windowW = w;
   windowH = h;
   // eviter une division par 0
   if(windowH==0)
      windowH = 1;
   
   float ratio = (float)windowW / (float)windowH;
   std::cout << "Ratio : " << ratio << std::endl;
   
   // Projection
   glMatrixMode(GL_PROJECTION);
   
   // Resetting matrix
   glLoadIdentity();
   
   // Viewport
   // // TODO Essayez de modifier l'appel à glViewport
   // en changeant les parametre d'appel a la fonction mais
   // tout en obtenant le meme resultat
   glViewport(0, 0, windowW, windowH);
   
   // Mise en place de la perspective
   // TODO : peut-on changerle ratio ici pour un meilleur resultat ?
   gluPerspective(focale, 4/3.0, near, far);
   
   // Placement de la caméra
   gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
   
   // Retourne a la pile modelview
   glMatrixMode(GL_MODELVIEW);
}

GLvoid clavier(unsigned char touche, int x, int y) {
   switch(touche) {
      case '+' : // zoom in
         mesh.setZoom(mesh.getZoom()+0.1);
         glutPostRedisplay();
         break;
      case '-' : // zoom in
         mesh.setZoom(mesh.getZoom()-0.1);
         glutPostRedisplay();
         break;
      case 'q' : // quit
      case 27 :
         exit(0);
         break;
   }
   glutPostRedisplay();
}

void specialKeys( int key, int x, int y ) {
   //  Right arrow - increase rotation by 5 degree
   if (key == GLUT_KEY_RIGHT) {
      mesh.setAngleY(mesh.getAngleY()+5);
   }
    
   //  Left arrow - decrease rotation by 5 degree
   else if (key == GLUT_KEY_LEFT) {
      mesh.setAngleY(mesh.getAngleY()-5);
   }
    
   else if (key == GLUT_KEY_UP) {
      mesh.setAngleX(mesh.getAngleX()+5);
   }
    
   else if (key == GLUT_KEY_DOWN) {
      mesh.setAngleX(mesh.getAngleX()-5);
   }
    
   //  Request display update
   glutPostRedisplay();
}
