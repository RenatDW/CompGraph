#include "mainwindow.h"
#include "customview.h"
#include "../../cmake-build-debug/CompGraph_autogen/ui_MainWindow.h"
#include "../render_engine/headers/RenderEngine.h"
#include "../obj_utils/objreader/ObjReader.h"
#include "../obj_utils/objwriter/ObjWriter.h"
#include "../render_engine/headers/GraphicConveyor.h"
#include "../render_engine/headers/Scene.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QLabel>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  camera(Vector3D(0, 0, 100), Vector3D(0, 0, 0),
		  1.0f, 1, 0.01f, 100),
	  ui(new Ui::MainWindow), scene(std::make_unique<QGraphicsScene>(this)),
	  frameCount(0), fps(0.0f)
{

    ui->setupUi(this);
	ui->graphicsView->setScene(scene.get());
	ui->graphicsView->setBackgroundBrush(QColor(45,45,45));
	ui->graphicsView->set_main_window_pointer(this);
	QString x = "0", y = "0", z = "0";
	add_camera_to_list(x,y,z);

	fpsTimer.start(); // Start FPS timer
	frameTimer.setInterval(16); // Approx. 60 FPS (1000ms / 16ms ~ 60 FPS)
	connect(&frameTimer, &QTimer::timeout, this, &MainWindow::onFrameUpdate);
	frameTimer.start();
	on_pushButton_6_clicked();
}

void MainWindow::onFrameUpdate()
{
	// Update the scene
	update_scene();
	// Calculate FPS
	frameCount++;
	qint64 elapsed = fpsTimer.elapsed(); // Time since last reset
	if (elapsed > 1000) // Update FPS every second
	{
		fps = frameCount / (elapsed / 1000.0f); // Frames per second
		frameCount = 0;
		fpsTimer.restart();
		// Update FPS in UI (e.g., status bar or label)
		ui->statusbar->setStyleSheet("QStatusBar { color: green; }");
		ui->statusbar->showMessage(QString("FPS: %1").arg(fps, 0, 'f', 2));
	}
}

void MainWindow::update_scene()
{
        //При низких значениях rgb, перестает рабоать (цвете 0,0,0 все ломается)

	scene->clear();
	int width = ui->graphicsView->viewport()->width();
	int height = ui->graphicsView->viewport()->height();

	QPixmap pixmap(width, height);
	pixmap.fill(QColor(45, 45, 45));
	QPainter painter(&pixmap);
	DepthBuffer db(width,height);
	PixelBuffer pb;
	camera.set_aspect_ratio(static_cast<float>(width) / static_cast<float>(height));
	Point2D vertex;

	if(ui->pushButton_6->isEnabled())
	{
		for (std::pair<int, Model> model : models)
		{
			QColor basic_color = QColor(255, 255, 255);

			RenderEngine renderEngine(camera, model.second, width,
				height, db, pb, materials.at(model.first));
			renderEngine.render();
		}
	}else{
		for (std::pair<int, Model> model : models)
		{
			QColor basic_color = QColor(255, 255, 255);
			RenderEngine renderEngine(camera, model.second, width,
				height, db, pb, materials.at(model.first));
			QPoint globalPos = QCursor::pos();
			QPoint localPos = ui->graphicsView->mapFromGlobal(globalPos);
			int x = localPos.x();
			int y = localPos.y();
			vertex = renderEngine.render_with_selection(x, y);
		}
	}

	QColor oldval = QColor(1,1,1);
	for (auto [key, val] : pb.data)
	{
		if(oldval != val){
			painter.setPen(val);
			oldval = val;
		}
		painter.drawPoint(key.getX(),key.getY());
	}

	if(vertex != Point2D())
	{
		int radius = 10;
		painter.setPen(QColor(255, 215, 50));
		for (int x = 0; x <= radius; x++)
		{
			for (int y = 0; y <= radius; y++)
			{
				if ((x) * (x) + (y) * (y) < radius * radius)
				{
					painter.drawPoint(x + vertex.getX(), y + vertex.getY());
					painter.drawPoint(x + vertex.getX(), -y + vertex.getY());
					painter.drawPoint(-x + vertex.getX(), y + vertex.getY());
					painter.drawPoint(-x + vertex.getX(), -y + vertex.getY());
				}
			}
		}
	}


	auto item = std::make_unique<QGraphicsPixmapItem>(pixmap);
	scene->addItem(item.release());
	ui->graphicsView->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Model_triggered()
{
    std::string file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open Object"), ":/",
                                                         tr("Object Files (*.obj)")).toUtf8().constData();
	models.emplace(model_cnt, ObjReader::read(file_name));
	materials.emplace(model_cnt, Material(false, false, false));

	//value and number of loaded model
	std::map<int, int> m;
	std::string name =  "Model " + std::to_string(model_cnt);
	//TODO обработать эту утечку
	auto model_list_item = std::make_unique<QListWidgetItem>(QString::fromStdString(name));
	QVariant v;

	v.setValue(model_cnt);

	model_list_item->setData(Qt::UserRole,v);
	connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

	ui->listWidget->addItem(model_list_item.release());
	ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListClicked()));
//	QObject::connect(ui->listWidget, SIGNAL(activated()), this, SLOT());
	selected_model = model_cnt;
	model_cnt++;
	update_scene();
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
	if (ui->listWidget->count() == 0)
	{
		std::cout << "oshibka, net elementov, elki palki" << std::endl;
		return;
	}
	/* Создаем объект контекстного меню */
	auto menu = std::make_unique<QMenu>(this);
	/* Создаём действия для контекстного меню */
	auto editDevice = std::make_unique<QAction>(tr("Редактировать"), this);
	auto rotateDevice = std::make_unique<QAction>(tr("Преместить"), this);
	auto deleteDevice = std::make_unique<QAction>(tr("Удалить"), this);
	/* Подключаем СЛОТы обработчики для действий контекстного меню */
	connect(editDevice.release(), SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Обработчик вызова диалога редактирования
	connect(rotateDevice.release(), SIGNAL(triggered()), this, SLOT(slotRotateRecord())); // Обработчик удаления записи
	connect(deleteDevice.release(), SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи

	/* Устанавливаем действия в меню */
	menu->addAction(editDevice.release());
	menu->addAction(rotateDevice.release());
	menu->addAction(deleteDevice.release());
	/* Вызываем контекстное меню */
	menu->popup(ui->listWidget->viewport()->mapToGlobal(pos));
}
void MainWindow::slotRotateRecord()
{
	for (auto element : ui->listWidget->selectedItems())
	{
		QVariant v = element->data(Qt::UserRole);
		int id = v.value<int>();
		GraphicConveyor::rotate_scale_translate(models[id], 1, 1, 1, 1, 1, 1, 1, 1, 1);
	}
}
void MainWindow::slotRemoveRecord()
{
	int row = ui->listWidget->selectionModel()->currentIndex().row();
	int model_id = ui->listWidget->item(row)->data(Qt::UserRole).value<int>();
	models.erase(model_id);
	materials.erase(model_id);
	auto it = ui->listWidget->takeItem(ui->listWidget->currentRow());
	delete it;
}
void MainWindow::slotEditRecord()
{
	int row = ui->listWidget->selectionModel()->currentIndex().row();

	for (auto elem : ui->listWidget->findItems("*", Qt::MatchWildcard))
	{
		if (elem->text() == "eshyo ne gotove")
		{
			std::cout << "Уже есть модель с таким названием" << std::endl;
			return;
		}
	}
	ui->listWidget->item(row)->setText("eshyo ne gotove");

}
void MainWindow::on_actionSave_Model_triggered()
{
    if (models.empty()) {
        QMessageBox::information(this, "Save model", "You haven't selected a model");
        return;
    }
    std::string file_name = QFileDialog::getSaveFileName(this, tr("Save Object"),
                                                         ":/",
                                                         tr("Objects (*.obj)")).toUtf8().constData();
    ObjWriter::write(models[0], file_name);
}

//void MainWindow::on_actionUp_triggered()
//{
//	camera.move_position(Vector3D(0, static_cast<float>(TRANSLATION), 0));
//	std::string ans = "{" + std::to_string(camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//			camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);
//
//
//    update_scene();
//}

//void MainWindow::on_actionDown_triggered()
//{
//	camera.move_position(Vector3D(0, static_cast<float>(-TRANSLATION), 0));
//	std::string ans = "{" + std::to_string(camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//			camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);
//
//
//	update_scene();
//}

//void MainWindow::on_actionLeft_triggered()
//{
//	camera.move_position(Vector3D(static_cast<float>(TRANSLATION), 0, 0));
//	std::string ans = "{" + std::to_string(camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//			camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);
//
//	update_scene();
//}

//void MainWindow::on_actionRight_triggered()
//{
//	camera.move_position(Vector3D(static_cast<float>(-TRANSLATION), 0, 0));
//	std::string ans = "{" + std::to_string(camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//			camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);
//
//
//	update_scene();
//}

void MainWindow::on_actionLoad_Texture_triggered()
{
    std::string file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open Texture"), ":/",
                                                         tr("Object Image (*.png *.jpg *.bmp)")).toUtf8().constData();
    //TODO Переделать когда нужно будет делать сценку
	QImage texture = QImage(file_name.data());
	if(!texture.isNull())
	{
		materials[selected_model].set_texture(texture);
		ui->checkBox_show_texture->setChecked(true);
		show_texture = true;
	}else{
		QMessageBox::information(this, "Oops...", "The texture hasn't been loaded.");
	}
	update_scene();
}

void MainWindow::on_actionTriangulation_changed()
{
    triangulation = !triangulation;
	update_scene();
}

void MainWindow::on_actionRotate_Scale_Translate_triggered()
{
	for(auto element: ui->listWidget->selectedItems())
	{
		QVariant v = element->data(Qt::UserRole);
		int id = v.value<int>();
		GraphicConveyor::rotate_scale_translate(models[id], 1000, 1, 1, 1, 1, 1, 1, 1, 1);
	}
	update_scene();
}
//Кнопка +
void MainWindow::on_pushButton_2_clicked()
{
	auto dialog1 = new QDialog();
	dialog1->setWindowModality(Qt::WindowModality::NonModal);
	dialog1->setMinimumHeight(150);
	dialog1->setMinimumWidth(150);

	auto label_1 = new QLabel();
	label_1->setText("Enter vector variables\n(x, y, z):");
	label_1->setGeometry(10, 10, 150, 50);
	label_1->setParent(dialog1);

	auto x_var = new QTextEdit();
	x_var->setPlaceholderText("x:");
	x_var->setGeometry(10, 70, 30, 30);
	x_var->setParent(dialog1);

	auto y_var = new QTextEdit();
	y_var->setPlaceholderText("y:");
	y_var->setGeometry(80, 70, 30, 30);
	y_var->setParent(dialog1);

	auto z_var = new QTextEdit();
	z_var->setPlaceholderText("z:");
	z_var->setGeometry(150, 70, 30, 30);
	z_var->setParent(dialog1);

	auto accept = new QPushButton();
	accept->setGeometry(10, 100, 50, 30);
	accept->setText("Add");
	accept->setParent(dialog1);
	//TODO автозакрытие окна после добавления камеры
	connect(accept, &QPushButton::clicked, [x_var, y_var, z_var, dialog1, this]()
	{
		add_camera_to_list(x_var->toPlainText(), y_var->toPlainText(), z_var->toPlainText(), dialog1);
	});


//	QPushButton *cancel = new QPushButton();
//	cancel->setGeometry(100, 100, 30, 30);
//	accept->setText("Cancel");
//	cancel->setParent(dialog1);
//
	dialog1->show();
}

void MainWindow::add_camera_to_list(QString x, QString y, QString z, QDialog *dialog1)
{
	dialog1->close();
	std::string name = "{" + std::to_string(x.toFloat()) + ", " + std::to_string(y.toFloat())  + " , " + std::to_string(z.toFloat())  + "}\n";
	auto model_list_item = std::make_unique<QListWidgetItem>(QString::fromStdString(name));
	QVariant v;
	std::array<float, 4> a{x.toFloat(), y.toFloat(), z.toFloat(), static_cast<float>(model_cnt)};
	v.setValue(a);
	model_list_item->setData(Qt::UserRole, v);
	ui->listWidget_2->addItem(model_list_item.release());

	std::string file_name = "/Users/renat/CLionProjects/3DModels/camera model.obj";
	Model md = ObjReader::read(file_name);
	GraphicConveyor::rotate_scale_translate(md, 1,1,1,0,0,0,x.toFloat(),y.toFloat(),z.toFloat());
	//TODO добавить перемещения на координаты
//	std::cout << model_cnt << std::endl;

	add_model(md);

}
void MainWindow::add_model(Model& md)
{
	models.emplace(model_cnt, md);
	materials[model_cnt] = { false, false, false };
	model_cnt++;
}
void MainWindow::add_camera_to_list(QString x, QString y, QString z)
{
	std::string name = "{" + std::to_string(x.toFloat()) + ", " + std::to_string(y.toFloat()) + " , " + std::to_string(z.toFloat()) + "}\n";
	auto model_list_item = std::make_unique<QListWidgetItem>(QString::fromStdString(name));
	QVariant v;
	std::array<float, 4> a{ x.toFloat(), y.toFloat(), z.toFloat(), static_cast<float>(model_cnt)};
//	std::cout << model_cnt << std::endl;
	model_cnt++;
	v.setValue(a);
	model_list_item->setData(Qt::UserRole, v);
	ui->listWidget_2->addItem(model_list_item.release());
}


//Кнопка use
void MainWindow::on_pushButton_3_clicked()
{

	int row = ui->listWidget_2->selectionModel()->currentIndex().row();
	if (row == -1)
	{
		std::cout << "Камера не выбрана" << std::endl;
		return;
	}


//	// Удаление модели выбранной камеры
	models.erase(ui->listWidget_2->item(row)->data(Qt::UserRole).value<std::array<float,4>>()[3]);
//
//	//Создание модели действующе камеры
	std::string file_name = "/Users/renat/CLionProjects/3DModels/camera model.obj";
	Model md = ObjReader::read(file_name);
	GraphicConveyor::rotate_scale_translate(md,1,1,1,0,0,0, camera.get_position().getX(), camera.get_position().getY(),
			camera.get_position().getZ());
	models.emplace(selected_camera_model_id, md);


	auto arr = ui->listWidget_2->item(row)->data(Qt::UserRole).value<std::array<float, 4>>();
	Vector3D a(arr[0], arr[1], arr[2]);
	camera.set_position(a);
	selected_camera_model_id = arr[3];
	selected_camera_list_id = row;

}
//Кнопка -
void MainWindow::on_pushButton_4_clicked()
{
	int row = ui->listWidget_2->selectionModel()->currentIndex().row();
//	std::cout << models.size() << std::endl;
	models.erase(ui->listWidget_2->item(row)->data(Qt::UserRole).value<std::array<float,4>>()[3]);
//	std::cout << models.size() << std::endl;
	auto it = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
	delete it;
}

void MainWindow::on_checkBox_show_mesh_toggled(bool checked)
{
	if (selected_model)
	{
		int model_id = selected_model;
		materials[model_id].set_show_mesh(!show_mesh);
//			std::cout << materials[model_id].is_show_mesh() <<", " << materials[model_id].is_show_texture() << ", " << materials[model_id].is_show_illumination() << std::endl;
		show_mesh = !show_mesh;
	}
	update_scene();

    // QMessageBox::information(this, "Save model", "Today is monday");
}

void MainWindow::on_checkBox_show_texture_toggled(bool checked)
{
	if (selected_model)
	{

		int model_id = selected_model;
		if (materials[model_id].get_texture().isNull())
		{
			ui->checkBox_show_texture->blockSignals(true);
			QMessageBox::information(this, "Oops...", "The texture hasn't been loaded.");
			show_texture = false;
			ui->checkBox_show_texture->setChecked(false);
			ui->checkBox_show_texture->blockSignals(false);

			return;
		}else
		{
			materials[model_id].set_show_texture(!show_texture);

			show_texture = !show_texture;
		}
		update_scene();
	}
	// QMessageBox::information(this, "Save model", "Today is monday");


}

void MainWindow::on_checkBox_show_illumination_toggled(bool checked)
{
	if (selected_model)
	{

		int model_id = selected_model;
//			std::cout << materials[model_id].is_show_mesh() <<", " << materials[model_id].is_show_texture() << ", " << materials[model_id].is_show_illumination() << std::endl;

		materials[model_id].set_show_illumination(!show_illumination);
		show_illumination = !show_illumination;

		update_scene();
	}
    
    // QMessageBox::information(this, "Save model", "Today is tuesday");
}

void MainWindow::on_pushButton_5_clicked()
{
	if(ui->pushButton_5->isEnabled())
	{
		std::cout << "delete mode" << std::endl;
		ui->pushButton_5->setEnabled(false);
		ui->pushButton_6->setEnabled(true);

	}

}
void MainWindow::on_pushButton_6_clicked()
{
	if(ui->pushButton_6->isEnabled())
	{
		std::cout << "normal mode" << std::endl;
		ui->pushButton_6->setEnabled(false);
		ui->pushButton_5->setEnabled(true);
	}
}

//
//void MainWindow::on_pushButton_7_clicked()
//{
//	auto dialog1 = new QDialog(this); // Указываем родительский виджет
//	dialog1->setWindowModality(Qt::WindowModality::NonModal);
//	dialog1->setMinimumSize(200, 150); // Удобнее установить минимальный размер
//
//	// Создаём Layout для диалога
//	auto layout = new QVBoxLayout(dialog1);
//
//	// Добавляем описание
//	auto label_1 = new QLabel("phi, psi, theta:", dialog1);
//	layout->addWidget(label_1);
//
//	// Поля ввода
//	auto phi = new QLineEdit(dialog1);
//	phi->setPlaceholderText("phi (x):");
//	layout->addWidget(phi);
//
//	auto psi = new QLineEdit(dialog1);
//	psi->setPlaceholderText("psi (y):");
//	layout->addWidget(psi);
//
//	auto theta = new QLineEdit(dialog1);
//	theta->setPlaceholderText("theta (z):");
//	layout->addWidget(theta);
//
//	// Кнопка подтверждения
//	auto accept = new QPushButton("Add", dialog1);
//	layout->addWidget(accept);
//
//	// Обработка нажатия кнопки
//	connect(accept, &QPushButton::clicked, [phi, psi, theta, dialog1, this]() {
//		// Проверяем введённые значения
//		bool phiOk, psiOk, thetaOk;
//		float phiValue = phi->text().toFloat(&phiOk);
//		float psiValue = psi->text().toFloat(&psiOk);
//		float thetaValue = theta->text().toFloat(&thetaOk);
//
//		if (!phiOk || !psiOk || !thetaOk) {
//			QMessageBox::warning(dialog1, "Invalid Input", "Please enter valid numbers for phi, psi, and theta.");
//			return;
//		}
//
//		// Обрабатываем выбранные элементы
//		for (auto element : ui->listWidget->selectedItems()) {
//			QVariant v = element->data(Qt::UserRole);
//			int id = v.toInt();
//			GraphicConveyor::scale(models[id], phiValue, psiValue, thetaValue);
//		}
//		ui->graphicsView->update();
//		dialog1->accept(); // Закрываем диалог
//	});
//
//	dialog1->setLayout(layout);
//	dialog1->exec(); // Модальное окно
//	ui->graphicsView->update();
//}


void MainWindow::onListClicked()
{
	ui->checkBox_show_illumination->blockSignals(true);
	ui->checkBox_show_texture->blockSignals(true);
	ui->checkBox_show_mesh->blockSignals(true);
	for (auto elem : ui->listWidget->selectedItems())
	{
		auto model_id = elem->data(Qt::UserRole).value<int>();
		selected_model = model_id;
		ui->checkBox_show_illumination->setChecked(materials[model_id].is_show_illumination());
		ui->checkBox_show_texture->setChecked(materials[model_id].is_show_texture());
		ui->checkBox_show_mesh->setChecked(materials[model_id].is_show_mesh());
	}
	ui->checkBox_show_illumination->blockSignals(false);
	ui->checkBox_show_texture->blockSignals(false);
	ui->checkBox_show_mesh->blockSignals(false);
	update_scene();
}

