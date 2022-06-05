// originally written by lmarchesoti https://github.com/lmarchesoti/rubik_cube/blob/master/src/main.cpp     



#include<GL/gl.h>
#include<GL/glut.h>
#include<vector>

using namespace std;


struct cube_info{
	GLdouble angle, x, y, z;
};

GLdouble dist, cube_size, gap;
GLint change;

int r[3], q[3][2];

//要素追加のために可変長配列
vector<cube_info> cubes[2][2][2];



//パーツ回転
//引数のangleは、90 or -90
void parts_rotate(GLdouble angle)
{
  	vector<cube_info> face[2][2];	
        //cube_info rotation;	

  	// 回転前の面の情報をfaceにコピー
  	// 面を回転
  	for(int i = 0; i < 2; i++){
    	  for(int j = 0; j < 2; j++) {

	     if(angle == 90){
      		if(q[0][0] == q[0][1]){
        	  //rotation = {angle, 1.0, 0.0, 0.0};
		  face[1-j][i] = cubes[q[0][1]][i][j];
      		}

      		if(q[1][0] == q[1][1]){
        	  rotation = {angle, 0.0, 1.0, 0.0};
        	  face[1-j][i] = cubes[j][q[1][1]][i];
		}

      		if(q[2][0] == q[2][1]){
        	  rotation = {angle, 0.0, 0.0, 1.0};
        	  face[1-j][i] = cubes[i][j][q[2][1]];
		}

      		//face[1-j][i].emplace_back(rotation);     //push_backでもOK
	  
	     }
	    
	     if(angle == -90){
	    	if(q[0][0] == q[0][1]){
                  rotation = {angle, 1.0, 0.0, 0.0};
                  face[1-j][i] = cubes[q[0][1]][i][j];
                }

                if(q[1][0] == q[1][1]){
                  rotation = {angle, 0.0, 1.0, 0.0};
                  face[1-j][i] = cubes[j][q[1][1]][i];
                }

                if(q[2][0] == q[2][1]){
                  rotation = {angle, 0.0, 0.0, 1.0};
                  face[1-j][i] = cubes[i][j][q[2][1]];
                }	    
	     }
	  }
	}


  	//コピーしておいた面の情報を適用
  	for(int i = 0; i < 2; i++){
    	  for(int j = 0; j < 2; j++) {

      	  	if(q[0][0] == q[0][1])
        	  cubes[q[0][1]][i][j] = face[i][j];

      		if(q[1][0] == q[1][1])
        	  cubes[j][q[1][1]][i] = face[i][j];

      		if(q[2][0] == q[2][1])
          	  cubes[j][i][q[2][1]] = face[i][j];
	  }
	}

}



//初期化関数
void init(void)
{
  	cube_size = 30.0;
  	r[0]=15;
  	r[1]=-40;  //はじめ等角投影
  	change = 5; //視点変動分
  	gap = 1.0;//小キューブ間の溝
  
  	glEnable(GL_DEPTH_TEST);  //隠面消去

  	dist = 45;
}




//１つの小キューブを描画する関数
//x1,y1,z1には0,1が入る
void a_cube(int x1, int y1, int z1)
{
  	  vector<cube_info> lrot = cubes[x1][y1][z1];
          
  	  glPushMatrix();

  	  // 各キューブの位置へ平行移動
  	  glTranslated((x1-0.5)*(cube_size + gap) , (y1-0.5)*(cube_size + gap) , (z1-0.5)*(cube_size + gap));

  	  // 各キューブの位置への回転移動
  	  for(int i = 0; i < lrot.size() ; i++) {
	  	glRotated(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);
	  }
	  

	  double s = cube_size/2;

	  //前面描画
	  glColor3d(1.0, 0.5, 0.0);
          glBegin(GL_QUADS);
            glNormal3d(0.0, 0.0, 1.0);  // 面の法線
            glVertex3d(s, s, s);
            glVertex3d(-s, s, s);
            glVertex3d(-s, -s, s);
            glVertex3d(s, -s, s);
          glEnd();

          //後面描画
          glColor3d(1.0, 0.0, 0.0);
          glBegin(GL_QUADS);  
            glNormal3d(0.0, 0.0, -1.0);  // 面の法線
            glVertex3d(s, s, -s);
            glVertex3d(s, -s, -s);
            glVertex3d(-s, -s, -s);
            glVertex3d(-s, s, -s);
          glEnd();
          
	  //左面描画
          glColor3d(0.0, 0.0, 1.0);
          glBegin(GL_QUADS);  
            glNormal3d(-1.0, 0.0, 0.0);  // 面の法線
            glVertex3d(-s, s, s);
            glVertex3d(-s, s, -s);
            glVertex3d(-s, -s, -s);
            glVertex3d(-s, -s, s);
          glEnd();

          //右面描画
          glColor3d(0.0, 1.0, 0.0);
          glBegin(GL_QUADS);  
            glNormal3d(1.0, 0.0, 0.0);  // 面の法線
            glVertex3d(s, s, s);
            glVertex3d(s, -s, s);
            glVertex3d(s, -s, -s);
            glVertex3d(s, s, -s);
          glEnd();

          //上面描画
          glColor3d(1.0, 1.0, 1.0);
          glBegin(GL_QUADS);  
            glNormal3d(0.0, 1.0, 0.0);  // 面の法線
            glVertex3d(-s, s, -s);
            glVertex3d(-s, s, s);
            glVertex3d(s, s, s);
            glVertex3d(s, s, -s);
          glEnd();

          //下面描画
          glColor3d(1.0, 1.0, 0.0);
          glBegin(GL_QUADS);  
            glNormal3d(0.0, -1.0, 0.0);  // 面の法線
            glVertex3d(-s, -s, -s);
            glVertex3d(-s, -s, s);
            glVertex3d(s, -s, s);
            glVertex3d(s, -s, -s);
          glEnd();

	  glPopMatrix();

}




//描画関数
void display(void)
{
  	int x = -cube_size, y = -cube_size,z = -cube_size;
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glLoadIdentity();  //変換行列初期化
  	gluLookAt(10,60,250,0,0,0,0,1,0);  //カメラ位置セット
  	glScaled(1.5, 1.5, 1.5);
  	glRotated((double)r[0], 1.0, 0.0, 0.0);  //x軸回り回転
  	glRotated((double)r[1], 0.0, 1.0, 0.0);  //y軸回り回転
  	glRotated((double)r[2], 0.0, 0.0, 1.0);  //z軸回り回転

  	//2x2x2のキューブを描画
  	for(int i = 0; i < 2; ++i){ // x方向に２個
    		for(int j = 0; j < 2; ++j){ //  y方向に２個
      			for(int k = 0; k < 2; ++k) { // z方向に２個
	      			a_cube(i, j, k);
      			}
    		}
  	}
  	glutSwapBuffers();  //ダブルバッファリング時、２画面を入れ替え
}


//再描画
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  	gluPerspective(dist,(double)w/(double)h,0.4, 500);
  	glMatrixMode(GL_MODELVIEW);
}




// キーボード操作
void keyboard(unsigned char key, int x, int y)
{
  	switch(key) {
    	     //面を選択
    
    		// x軸
    		case 'q':	  
		  q[0][0] = 0;
		  q[0][1] = 0;
		  q[1][0] = 0;
		  q[1][1] = 2;
		  q[2][0] = 0;
		  q[2][1] = 2;
		  break;

    		case 'w':		  
		  q[0][0] = 1;
                  q[0][1] = 1;
                  q[1][0] = 0;
                  q[1][1] = 2;
                  q[2][0] = 0;
                  q[2][1] = 2;
      		  break;


   		// y軸
    		case 'a':
		  q[0][0] = 0;
                  q[0][1] = 2;
                  q[1][0] = 0;
                  q[1][1] = 0;
                  q[2][0] = 0;
                  q[2][1] = 2;
		  break;

    		case 's':
		  q[0][0] = 0;
                  q[0][1] = 2;
                  q[1][0] = 1;
                  q[1][1] = 1;
                  q[2][0] = 0;
                  q[2][1] = 2;
		  break;


    		// z軸
    		case 'z':
		  q[0][0] = 0;
                  q[0][1] = 2;
                  q[1][0] = 0;
                  q[1][1] = 2;
                  q[2][0] = 0;
                  q[2][1] = 0;
		  break;

    		case 'x':
		  q[0][0] = 0;
                  q[0][1] = 2;
                  q[1][0] = 0;
                  q[1][1] = 2;
                  q[2][0] = 1;
                  q[2][1] = 1;
		  break;


    		// Escキーでプログラム終了
     		case '\033':
      		  exit(0);

     		default:
      		  break;

  	}

  	glutPostRedisplay();

}


//特殊キーでの操作
void specialkeydown(int key, int x, int y)
{

  	switch (key) {
    		//視点回転
    		case GLUT_KEY_DOWN:
      		  r[0] = (r[0] + change) % 360;
      		  break;
    		case GLUT_KEY_UP:
      		  r[0] = (r[0] - change) % 360;
     		  break;
		case GLUT_KEY_RIGHT:
                  r[1] = (r[1] + change) % 360;
                  break;
                case GLUT_KEY_LEFT:
                  r[1] = (r[1] - change) % 360;
                  break;

	        case GLUT_KEY_F11:
                  r[2] = (r[2] - change) % 360;
                  break;
                case GLUT_KEY_F12:
                  r[2] = (r[2] + change) % 360;
                  break;



    		//パーツ回転
    		case GLUT_KEY_PAGE_UP:
      		  parts_rotate(90);
      		  break;

    		case GLUT_KEY_PAGE_DOWN:
      		  parts_rotate(-90);
      		  break;


		//隠面消去オフ 
    		case GLUT_KEY_F1:
      		  glDisable(GL_DEPTH_TEST);
      		  break;

		//隠面消去
    		case GLUT_KEY_F2:
         	  glEnable(GL_DEPTH_TEST);
      		  break;
		 
	}
   	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  	glutInitWindowSize(600,500);
  	glutCreateWindow("Rubik's cube");
  	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialkeydown);
	init();

	glutPostRedisplay();
	glutMainLoop();
}
