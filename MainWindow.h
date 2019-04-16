#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	Ui::MainWindow *ui;
	QImage bg_image_;
	QPoint mouse_pos_;
	QRect geometry_;
protected:
	void mouseMoveEvent(QMouseEvent *e);
protected:
	void mousePressEvent(QMouseEvent *e);
private slots:
	void on_pushButton_search_clicked();

	// QWidget interface
	void on_pushButton_option_clicked();

protected:
	void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
