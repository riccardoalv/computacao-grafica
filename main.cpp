#include <GL/glut.h>
#include <cmath>
#include <vector>

// Variáveis de controle
float angle = 0.0;
float step = 0.05;
float posZ = -1.0;
float posY = 0.0;
float rotateX = 0.0;
float rotateY = 0.0;
float zoom = 5.0;             // Inicialização do zoom
bool morphing = false;        // Estado de morphing
bool toCircle = true;         // Direção do morphing
float morphingProgress = 0.0; // Progresso da animação de morphing
float morphingSpeed = 0.1;    // Velocidade do morphing

struct Tree {
  float x, z;
};

std::vector<Tree> trees;

// Função de inicialização
void init() {
  glClearColor(0.5, 0.8, 1.0, 1.0); // Cor azul claro para o céu
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  // Adiciona árvores à cena
  trees = {{2.0f, 2.0f},
           {-3.0f, -2.0f},
           {1.0f, -5.0f},
           {-4.0f, 3.0f},
           {3.5f, -3.5f}};
}

// Função para desenhar um cubo
void drawCube(float size) { glutSolidCube(size); }

// Função para desenhar o chão
void drawGround() {
  glColor3f(0.0, 1.0, 0.0); // Cor verde para grama
  glBegin(GL_QUADS);
  glVertex3f(-10.0, 0.0, -10.0);
  glVertex3f(-10.0, 0.0, 10.0);
  glVertex3f(10.0, 0.0, 10.0);
  glVertex3f(10.0, 0.0, -10.0);
  glEnd();
}

// Função para desenhar uma árvore
void drawTree(float x, float z) {
  glColor3f(0.55, 0.27, 0.07); // Cor marrom para o tronco
  glPushMatrix();
  glTranslatef(x, 0.5, z);
  glScalef(0.2, 1.0, 0.2);
  drawCube(1.0);
  glPopMatrix();

  glColor3f(0.0, 1.0, 0.0); // Cor verde para a folhagem
  glPushMatrix();
  glTranslatef(x, 1.5, z);
  glutSolidSphere(0.5, 20, 20);
  glPopMatrix();
}

// Função para desenhar uma figura de palito
void drawStickFigure(float progress) {
  glColor3f(1.0, 1.0, 1.0); // Cor branca para o boneco palito

  // Cabeça
  glPushMatrix();
  glTranslatef(0.0, posY + 1.5, posZ); // Ajustar para acima do chão
  float headSize = 0.1 + 0.4 * progress;
  glutSolidSphere(headSize, 10 + 40 * progress, 10 + 40 * progress);
  glPopMatrix();

  // Corpo
  glPushMatrix();
  glTranslatef(0.0, posY + 1.0 * (1.0 - progress),
               posZ); // Ajustar para acima do chão
  glScalef(0.6 * (1.0 - progress), 1.0 * (1.0 - progress),
           0.2 * (1.0 - progress));
  if (progress < 1.0) {
    drawCube(0.5);
  }
  glPopMatrix();

  // Braços
  for (int i = 0; i < 2; ++i) {
    float sign = (i == 0) ? 1.0f : -1.0f;
    glPushMatrix();
    glTranslatef(0.0, posY + 1.25 * (1.0 - progress),
                 posZ); // Ajustar para acima do chão
    glRotatef(sign * sin(angle) * 45 * (1.0 - progress), 1, 0, 0);
    glTranslatef(sign * 0.2 * (1.0 - progress), -0.24 * (1.0 - progress), 0.0);
    glScalef(0.2 * (1.0 - progress), 1.0 * (1.0 - progress),
             0.2 * (1.0 - progress));
    if (progress < 1.0) {
      drawCube(0.5);
    } else {
      drawCube(0.5 * progress); // Ajustar tamanho do braço para morphing
    }
    glPopMatrix();
  }

  // Pernas
  for (int i = 0; i < 2; ++i) {
    float sign = (i == 0) ? 1.0f : -1.0f;
    glPushMatrix();
    glTranslatef(0.0, posY + 0.6 * (1.0 - progress),
                 posZ); // Ajustar para acima do chão
    glRotatef(sign * sin(angle) * 45 * (1.0 - progress), 1, 0, 0);
    glTranslatef(sign * 0.1 * (1.0 - progress), -0.1 * (1.0 - progress), 0.0);
    glScalef(0.2 * (1.0 - progress), 1.1 * (1.0 - progress),
             0.2 * (1.0 - progress));
    if (progress < 1.0) {
      drawCube(0.5);
    } else {
      drawCube(0.5 * progress); // Ajustar tamanho do braço para morphing
    }
    glPopMatrix();
  }
}

// Função de exibição
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0.0, 1.0, zoom, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0);

  glRotatef(rotateX, 1.0, 0.0, 0.0);
  glRotatef(rotateY, 0.0, 1.0, 0.0);

  drawGround();

  // Desenhar árvores
  for (const auto &tree : trees) {
    drawTree(tree.x, tree.z);
  }

  drawStickFigure(morphingProgress);
  glutSwapBuffers();
}

// Função para checar colisão
bool checkCollision(float newZ) {
  for (const auto &tree : trees) {
    float dx = 0.0f - tree.x;
    float dz = newZ - tree.z;
    float distance = sqrt(dx * dx + dz * dz);
    if (distance < 0.5) {
      return true; // Colisão detectada
    }
  }
  return false; // Sem colisão
}

// Função de atualização
void update(int value) {
  angle += 0.1;
  if (angle > 2 * M_PI) {
    angle -= 2 * M_PI;
  }

  if (morphing) {
    if (toCircle) {
      morphingProgress += morphingSpeed;
      if (morphingProgress > 1.0) {
        morphingProgress = 1.0;
        morphing = false;
      }
    } else {
      morphingProgress -= morphingSpeed;
      if (morphingProgress < 0.0) {
        morphingProgress = 0.0;
        morphing = false;
      }
    }
  }

  float newPosZ = posZ + step;
  if (!checkCollision(newPosZ)) {
    posZ = newPosZ;
  }

  if (posZ > 10.0) { // Limite ajustado para o chão
    posZ = -10.0;
  }

  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}

// Função de gerenciamento de teclas
void handleKeys(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    posY += step;
    break;
  case 's':
    posY -= step;
    break;
  case 'a':
    posZ -= step;
    break;
  case 'd':
    posZ += step;
    break;
  case '+':
    zoom -= 0.5; // Zoom in
    if (zoom < 2.0) {
      zoom = 2.0; // Limite mínimo do zoom
    }
    break;
  case '-':
    zoom += 0.5; // Zoom out
    if (zoom > 15.0) {
      zoom = 15.0; // Limite máximo do zoom
    }
    break;
  case 'v':
    if (!morphing) {
      morphing = true;
      toCircle = !toCircle;
    }
    break;
  case 27: // Tecla ESC
    exit(0);
  }
  glutPostRedisplay();
}

// Função de gerenciamento de teclas especiais
void handleSpecialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    rotateX -= 5.0;
    break;
  case GLUT_KEY_DOWN:
    rotateX += 5.0;
    break;
  case GLUT_KEY_LEFT:
    rotateY -= 5.0;
    break;
  case GLUT_KEY_RIGHT:
    rotateY += 5.0;
    break;
  }
  glutPostRedisplay();
}

// Função principal
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Uirapuru - Animação 3D de uma Pessoa Andando");

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(handleKeys);
  glutSpecialFunc(handleSpecialKeys);
  glutTimerFunc(25, update, 0);

  glutMainLoop();
  return 0;
}

