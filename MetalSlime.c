#include <stdio.h>
#include <GL/glut.h>

int previousX, previousY;  // マウス座標の変数
GLfloat rotationX = 0.0f;  // X軸回転角度
GLfloat rotationY = 0.0f;  // Y軸回転角度

GLfloat translationZ = 0.0f;  // Z軸平行移動量
GLfloat translationSpeed = 0.1f;  // 平行移動の速度


void myInit(char* progname)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);  // ディスプレイモードの初期化
    glutInitWindowSize(500, 500);  // ウィンドウサイズの初期化
    glutInitWindowPosition(0, 0);  // ウィンドウ位置の初期化
    glutCreateWindow(progname);  // ウィンドウの作成
    glClearColor(0.0, 0.0, 0.0, 1.0);  // 背景色の設定
    glShadeModel(GL_SMOOTH);  // シェーディングモデルの設定
    glEnable(GL_LIGHT0);  // ライト0の有効化
}

#define	imageWidth 256
#define	imageHeight 256

unsigned char texImage[imageHeight][imageWidth][3];

void drawFloor(void)
{
    // テクスチャマッピングの設定
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1); // テクスチャのバインド

    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex3d(-10.0, -2.0, -10.0);
    glTexCoord2d(0.0, 1.0); glVertex3d(-10.0, -2.0, 10.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(10.0, -2.0, 10.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(10.0, -2.0, -10.0);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void readPPMImage(char* filename)
{
    FILE* fp;
    int  ch, i;

    if (fopen_s(&fp, filename, "r") != 0) {
        fprintf(stderr, "Cannot open ppm file %s\n", filename);
        exit(1);
    }
    
    fread(texImage, 1, imageWidth * imageHeight * 3, fp);	// read RGB data
    fclose(fp);
}

void setUpTexture(void)
{
    readPPMImage("floor.ppm");
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
        0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
}

void myDisplay(void)
{
    
    float ambient[] = { 0.1, 0.1, 0.1, 0.1 };  // 環境光の設定
    float diffuse[] = { 0.3, 0.3, 0.3, 1.0 };  // 拡散反射の設定
    float specular[] = { 0.8, 0.8, 0.8, 1.0 };  // 鏡面反射の設定 (変更)
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // カラーバッファとデプスバッファのクリア

    glEnable(GL_DEPTH_TEST);  // デプステストの有効化
    glEnable(GL_LIGHTING);  // ライティングの有効化
    glEnable(GL_TEXTURE_2D);

    
    glPushMatrix();
    drawFloor();
    glPopMatrix();
    

    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);  // 球体の材質の環境光成分を設定
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);  // 球体の材質の拡散反射成分を設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);  // 球体の材質の鏡面反射成分を設定 (変更)
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);  // 球体の材質のシャイニング度を設定
    

    
    // 真ん中のメタルスライム
    glPushMatrix();  // 行列スタックに現在の変換行列を保存

        glRotatef(rotationX, 0.0f, 1.0f, 0.0f);  // X軸回転
        glRotatef(rotationY, 1.0f, 0.0f, 0.0f);  // Y軸回転
        glTranslated(0.0, 0.0, translationZ);  // 現在の座標系での平行移動を設定

        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glTranslated(0.0, 0.0, 0.0);  // 現在の座標系での平行移動を設定
        glScalef(1.2, 0.8, 1.0);  // 拡大縮小行列で球体の形状を変更
        glutSolidSphere(0.8, 20, 20);  // 球体の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

        // 三角錐の描画
        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // X軸周りに90度回転
        glTranslatef(0.0, 0.0, -0.53);  // 三角錐の座標変換
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // 三角錐を逆さまに回転
        glutSolidCone(0.2, 0.4, 10, 10);  // 三角錐の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

    glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元


    // 上のメタルスライム
    glPushMatrix();  // 行列スタックに現在の変換行列を保存

        glRotatef(rotationX, 0.0f, 1.0f, 0.0f);  // X軸回転
        glRotatef(rotationY, 1.0f, 0.0f, 0.0f);  // Y軸回転
        glTranslated(0.0, 1.2, translationZ);  // 現在の座標系での平行移動を設定

        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glTranslated(0.0, 0.0, 0.0);  // 現在の座標系での平行移動を設定
        glScalef(1.2, 0.8, 1.0);  // 拡大縮小行列で球体の形状を変更
        glutSolidSphere(0.8, 20, 20);  // 球体の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

        // 三角錐の描画
        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // X軸周りに90度回転
        glTranslatef(0.0, 0.0, -0.53);  // 三角錐の座標変換
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // 三角錐を逆さまに回転
        glutSolidCone(0.2, 0.4, 10, 10);  // 三角錐の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

    glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元


    // 下のメタルスライム
    glPushMatrix();  // 行列スタックに現在の変換行列を保存

        glRotatef(rotationX, 0.0f, 1.0f, 0.0f);  // X軸回転
        glRotatef(rotationY, 1.0f, 0.0f, 0.0f);  // Y軸回転
        glTranslated(0.0, -1.2, translationZ);  // 現在の座標系での平行移動を設定

        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glTranslated(0.0, 0.0, 0.0);  // 現在の座標系での平行移動を設定
        glScalef(1.2, 0.8, 1.0);  // 拡大縮小行列で球体の形状を変更
        glutSolidSphere(0.8, 20, 20);  // 球体の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

        // 三角錐の描画
        glPushMatrix();  // 行列スタックに現在の変換行列を保存
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // X軸周りに90度回転
        glTranslatef(0.0, 0.0, -0.53);  // 三角錐の座標変換
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  // 三角錐を逆さまに回転
        glutSolidCone(0.2, 0.4, 10, 10);  // 三角錐の描画
        glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元

    glPopMatrix();  // 行列スタックから最後の変換行列を取り出して復元
    



    glFlush();  // OpenGLのコマンドを実行
    glDisable(GL_LIGHTING);  // ライティングの無効化
    glDisable(GL_DEPTH_TEST);  // デプステストの無効化
}

void myReshape(int width, int height)
{
    glViewport(0, 0, width, height);  // ウィンドウのビューポートの設定
    glMatrixMode(GL_PROJECTION);  // 投影行列を指定
    glLoadIdentity();  // 単位行列で初期化
    gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);  // 透視投影の設定
    glMatrixMode(GL_MODELVIEW);  // モデルビュー行列を指定
    glLoadIdentity();  // 単位行列で初期化
    glTranslated(0.0, 0.0, -5.0);  // 平行移動の設定
}

void escapeMotion()
{
    if (translationZ <= -10.0f)
        return;  // 一定距離移動したらアニメーションを停止

    translationZ -= translationSpeed;
    glutPostRedisplay();
    glutTimerFunc(10, escapeMotion, 0);
}

void menuSelect(int value)
{
    if (value == 1)  // メニューの項目が選択されたら逃げ出すアニメーションを開始
    {
        glutTimerFunc(10, escapeMotion, 0);
    }
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        previousX = x;  // 現在のマウス座標を保存
        previousY = y;
    }
}

void myMotion(int x, int y)
{
    rotationX += (x - previousX);  // マウスの移動量に応じて回転角度を更新
    rotationY += (y - previousY);
    previousX = x;  // 現在のマウス座標を保存
    previousY = y;
    glutPostRedisplay();  // 描画を更新
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)  // ESCキーが押されたら終了
        exit(0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // GLUTの初期化
    myInit(argv[0]);  // プログラムの初期化

    setUpTexture();

     // メニューを作成
    glutCreateMenu(menuSelect);
    glutAddMenuEntry("nigeru", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 右クリック時にメニューを表示

    glutKeyboardFunc(myKeyboard);  // キーボードイベントのコールバック関数を設定
    glutReshapeFunc(myReshape);  // ウィンドウリサイズイベントのコールバック関数を設定
    glutDisplayFunc(myDisplay);  // 描画イベントのコールバック関数を設定
    glutMouseFunc(myMouse);  // マウスボタンイベントのコールバック関数を設定
    glutMotionFunc(myMotion);  // マウスモーションイベントのコールバック関数を設定
    glutMainLoop();  // GLUTのメインループに入る
    return 0;
}