#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QBitmap>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <stdint.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// ウィンドウの透過設定をする
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TranslucentBackground);
	setAutoFillBackground(true);

	// 背景画像を読み込む
	bg_image_.load(":/image/bg.png");
	bg_image_ = bg_image_.convertToFormat(QImage::Format_RGBA8888);
	int w = bg_image_.width();
	int h = bg_image_.height();
	setFixedSize(w, h);

	// 描画およびマウスイベントの受け取りを識別するビットマップを設定する。
	// Windowsでは背景の透過ピクセルが自動的にマスクになるため以下のコードは不要です。
#ifndef Q_OS_WIN
	{
		QImage maskimage(w, h, QImage::Format_Grayscale8);
		for (int y = 0; y < h; y++) {
			uint8_t const *src = bg_image_.scanLine(y);
			uint8_t *dst = maskimage.scanLine(y);
			for (int x = 0; x < w; x++) {
				dst[x] = src[x * 4 + 3] < 128 ? 255 : 0;
			}
		}
		setMask(QBitmap::fromImage(maskimage));
	}
#endif
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	// マウスボタンが押された場所を記憶しておく
	mouse_pos_ = mapToGlobal(e->pos());
	geometry_ = geometry();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	// ドラッグされたときはウィンドウを移動する
	if (e->buttons() & Qt::LeftButton) {
		QPoint pos = mapToGlobal(e->pos());
		int dx = pos.x() - mouse_pos_.x();
		int dy = pos.y() - mouse_pos_.y();
		setGeometry(geometry_.translated(dx, dy));
	}
}

void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter pr(this);
	pr.drawImage(0, 0, bg_image_);
}

void MainWindow::on_pushButton_option_clicked()
{
}

void MainWindow::on_pushButton_search_clicked()
{
	// WindowsでMSVCの場合、以下の日本語の部分は文字コードの問題によりコンパイルが通らないと思いますので、
	// Qt Linguistを用いた多言語対応を実装する必要があります。
	QString s = ui->plainTextEdit->toPlainText();
	if (ui->plainTextEdit->toPlainText() == "お前を消す方法") {
		QMessageBox::information(this, "カイル", "またどこかでお会いしましょう");
		close();
	}
}

