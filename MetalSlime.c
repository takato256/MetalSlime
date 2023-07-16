#include <stdio.h>
#include <GL/glut.h>

void myInit(char* progname)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);  // ディスプレイモードの初期化
    glutInitWindowSize(500, 500);  // ウィンドウサイズの初期化
    glutInitWindowPosition(0, 0);  // ウィンドウ位置の初期化
    glutCreateWindow(progname);  // ウィンドウの作成
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 背景色の設定
    glShadeModel(GL_SMOOTH);  // シェーディングモデルの設定
    glEnable(GL_LIGHT0);  // ライト0の有効化
}

void myDisplay(void)
{
    float ambient[] = { 0.1, 0.1, 0.1, 1.0 };  // より暗い環境光の設定
    float diffuse[] = { 0.3, 0.3, 0.3, 1.0 };  // より暗い拡散反射の設定
    float specular[] = { 0.9, 0.9, 0.9, 1.0 };   // 鏡面反射の設定

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // カラーバッファとデプスバッファのクリア

    glEnable(GL_DEPTH_TEST);  // デプステストの有効化
    glEnable(GL_LIGHTING);  // ライティングの有効化

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);  // 球体の材質の環境光成分を設定
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);  // 球体の材質の拡散反射成分を設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);  // 球体の材質の鏡面反射成分を設定
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);  // 球体の材質のシャイニング度を設定

    glPushMatrix();  // 行列スタックに現在の変換行列を保存
    glTranslated(0.0, 0.0, 0.0);  // 現在の座標系での平行移動を設定
    glutSolidSphere(0.8, 20, 20);  // 球体の描画
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
    glTranslated(0.0, 0.0, -3.6);  // 平行移動の設定
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
    glutKeyboardFunc(myKeyboard);  // キーボードイベントのコールバック関数を設定
    glutReshapeFunc(myReshape);  // ウィンドウリサイズイベントのコールバック関数を設定
    glutDisplayFunc(myDisplay);  // 描画イベントのコールバック関数を設定
    glutMainLoop();  // GLUTのメインループに入る
    return 0;
}
