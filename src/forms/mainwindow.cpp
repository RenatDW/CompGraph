#include "mainwindow.h"
#include "customview.h"
#include "../../cmake-build-debug/CompGraph_autogen/ui_MainWindow.h"
#include "../render_engine/headers/RenderEngine.h"
#include "../obj_utils/objreader/ObjReader.h"
#include "../obj_utils/objwriter/ObjWriter.h"
#include "../render_engine/headers/GraphicConveyor.h"

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
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
	std::vector<Light> lt;
	lt.emplace_back(QColor(255,255,255), camera.get_position());
	for(std::pair<int, Light> elem : light){
		lt.emplace_back(elem.second);
	}
	for (auto& elem : materials)
	{
		elem.second.set_lights(lt);
	}

	QPixmap pixmap(width, height);
	pixmap.fill(QColor(45, 45, 45));
	QPainter painter(&pixmap);
	DepthBuffer db(width,height);
	PixelBuffer pb;
	camera.set_aspect_ratio(static_cast<float>(width) / static_cast<float>(height));
	Point2D vertex;

	for (std::pair<int, Model> model : models)
	{
		RenderEngine renderEngine(camera, model.second, width,
			height, db, pb, materials.at(model.first));
		if (ui->pushButton_6->isEnabled() || selected_model != model.first)
		{
			renderEngine.render();
		}else{
			QPoint localPos = ui->graphicsView->mapFromGlobal(QCursor::pos());
			TriangleCoordinates ans = renderEngine.render_with_selection(localPos.x(), localPos.y());
			this->vertex_id = ans.vertex_id;
			this->triangle_id = ans.triangle_id;
			vertex = ans.vertex;
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

	if(vertex_id != -1)
	{
		painter.setPen(QColor(255, 215, 50));
		for (int x = 0; x <= VERTEX_RADIUS; x++)
		{
			for (int y = 0; y <= VERTEX_RADIUS; y++)
			{
				if ((x) * (x) + (y) * (y) < VERTEX_RADIUS * VERTEX_RADIUS)
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
	original_models.emplace(model_cnt, ObjReader::read(file_name));
	materials.emplace(model_cnt, Material(false, false, false));

	//value and number of loaded model
	std::map<int, int> m;
	std::string name =  "Model " + std::to_string(model_cnt);
	//TODO обработать эту утечку
	auto model_list_item = new QListWidgetItem(QString::fromStdString(name));
	QVariant v;

	v.setValue(model_cnt);

	model_list_item->setData(Qt::UserRole,v);
	connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

	ui->listWidget->addItem(model_list_item);
	ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(onListClicked()));
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
	auto menu = new QMenu(this);
	/* Создаём действия для контекстного меню */
	auto editDevice = new QAction(tr("Редактировать"), this);
	auto rotateDevice = new QAction(tr("Преместить"), this);
	auto deleteDevice = new QAction(tr("Удалить"), this);
	/* Подключаем СЛОТы обработчики для действий контекстного меню */
	connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));     // Обработчик вызова диалога редактирования
	connect(rotateDevice, SIGNAL(triggered()), this, SLOT(slotRotateRecord())); // Обработчик удаления записи
	connect(deleteDevice, SIGNAL(triggered()), this, SLOT(slotRemoveRecord())); // Обработчик удаления записи

	/* Устанавливаем действия в меню */
	menu->addAction(editDevice);
	menu->addAction(rotateDevice);
	menu->addAction(deleteDevice);
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

	QMessageBox msgBox;
	msgBox.setText("Выберите тип модели для сохранения:");
	msgBox.setInformativeText("Сохранить оригинальную модель или преобразованную?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
	QPushButton* saveOriginal = msgBox.addButton("Оригинальная", QMessageBox::ActionRole);
	QPushButton* saveTransformed = msgBox.addButton("Преобразованная", QMessageBox::ActionRole);
	msgBox.exec();

	std::string file_name = QFileDialog::getSaveFileName(this, tr("Save Object"),
			":/",
			tr("Objects (*.obj)")).toUtf8().constData();
	if (msgBox.clickedButton() == saveOriginal) {
		ObjWriter::write(original_models[selected_model], file_name);
	} else if (msgBox.clickedButton() == saveTransformed) {
		ObjWriter::write(models[selected_model], file_name);
	}
}

//void MainWindow::on_actionLoad_Texture_triggered()
//{
//    std::string file_name = QFileDialog::getOpenFileName(this,
//                                                         tr("Open Texture"), ":/",
//                                                         tr("Object Image (*.png *.jpg *.bmp)")).toUtf8().constData();
//    //TODO Переделать когда нужно будет делать сценку
//	QImage texture = QImage(file_name.data());
//	if(!texture.isNull())
//	{
//		materials[selected_model].set_texture(texture);
//		ui->checkBox_show_texture->setChecked(true);
//		show_texture = true;
//	}else{
//		QMessageBox::information(this, "Oops...", "The texture hasn't been loaded.");
//	}
//	update_scene();
//}

//Кнопка +
void MainWindow::on_addCamera_clicked()
{
	QDialog dialog;
	dialog.setWindowTitle("Добавление камеры");

	auto* main_layout = new QVBoxLayout(&dialog);

	auto* label_x = new QLabel("Координата камеры по X:");
	auto* x_input = new QLineEdit();
	main_layout->addWidget(label_x);
	main_layout->addWidget(x_input);

	auto* label_y = new QLabel("Координата камеры по Y:");
	auto* y_input = new QLineEdit();
	main_layout->addWidget(label_y);
	main_layout->addWidget(y_input);

	auto* label_z = new QLabel("Координата камеры по Z:");
	auto* z_input = new QLineEdit();
	main_layout->addWidget(label_z);
	main_layout->addWidget(z_input);

	auto* button_layout = new QHBoxLayout();
	auto* apply_button = new QPushButton("Применить");
	auto* cancel_button = new QPushButton("Отмена");
	button_layout->addWidget(apply_button);
	button_layout->addWidget(cancel_button);
	main_layout->addLayout(button_layout);

	connect(apply_button, &QPushButton::clicked, [&]()
	{
		bool okX, okY, okZ;
		float x = x_input->text().toFloat(&okX);
		float y = y_input->text().toFloat(&okY);
		float z = z_input->text().toFloat(&okZ);

		if (okX && okY && okZ)
		{
			add_camera_to_list(x, y, z);
			dialog.accept();
		} else {
			QMessageBox::warning(&dialog, "Ошибка", "Введите корректные значения!");
		}
	});

	connect(cancel_button, &QPushButton::clicked, [&]() {
		dialog.reject();
	});

	dialog.exec();
}

void MainWindow::add_camera_to_list(float x, float y, float z)
{
	std::string name = "{" + std::to_string(x) + ", " + std::to_string(y)  + " , " + std::to_string(z)  + "}\n";
	auto model_list_item = new QListWidgetItem(QString::fromStdString(name));
	QVariant v;
	std::array<float, 4> a{x, y, z, static_cast<float>(model_cnt)};
	v.setValue(a);
	model_list_item->setData(Qt::UserRole, v);
	ui->listWidget_2->addItem(model_list_item);
//todo Переделать
//	std::string file_name = (QCoreApplication::applicationDirPath() + "../../resources/camera_model.obj").toStdString();
	std::string file_name = "/Users/renat/CLionProjects/CompGraph/camera_model.obj";
	Model md = ObjReader::read(file_name);
	GraphicConveyor::rotate_scale_translate(md, 1,1,1,0,0,0,x,y,z);
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
	auto model_list_item = new QListWidgetItem(QString::fromStdString(name));
	QVariant v;
	std::array<float, 4> a{ x.toFloat(), y.toFloat(), z.toFloat(), static_cast<float>(model_cnt)};
	model_cnt++;
	v.setValue(a);
	model_list_item->setData(Qt::UserRole, v);
	ui->listWidget_2->addItem(model_list_item);
}


//Кнопка use
void MainWindow::on_useCamera_clicked()
{

	int row = ui->listWidget_2->selectionModel()->currentIndex().row();
	if (row == -1)
	{
		std::cout << "Камера не выбрана" << std::endl;
		return;
	}


//	// Удаление модели выбранной камеры
	models.erase(ui->listWidget_2->item(row)->data(Qt::UserRole).value<std::array<float,4>>()[3]);

	std::string file_name = "/Users/Пользователь/CLionProjects/CompGraph/resources/camera_model.obj";
	Model md = ObjReader::read(file_name);

	models.emplace(selected_camera_model_id, md);

	std::array<float, 4> arr = ui->listWidget_2->item(row)->data(Qt::UserRole).value<std::array<float, 4>>();
	Vector3D a(arr[0], arr[1], arr[2]);
	camera.set_position(a);
	selected_camera_model_id = arr[3];
	selected_camera_list_id = row;

}
//Кнопка -
void MainWindow::on_deleteCamera_clicked()
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
		materials[model_id].set_show_mesh(checked);
	}
	update_scene();
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
			materials[model_id].set_show_texture(checked);
		}
		update_scene();
	}

}

void MainWindow::on_checkBox_show_illumination_toggled(bool checked)
{
	int model_id = selected_model;
//			std::cout << materials[model_id].is_show_mesh() <<", " << materials[model_id].is_show_texture() << ", " << materials[model_id].is_show_illumination() << std::endl;

	materials[model_id].set_show_illumination(checked);
	update_scene();

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

void MainWindow::on_rotate_clicked()
{
	QDialog dialog;
	dialog.setWindowTitle("Поворот модели");
	dialog.setWindowIcon(QIcon(":/toster.png"));

	auto* main_layout = new QVBoxLayout(&dialog);

	auto* label_x = new QLabel("Угол поворота вокруг оси X (в градусах):");
	auto* angle_x_input = new QLineEdit();
	main_layout->addWidget(label_x);
	main_layout->addWidget(angle_x_input);

	auto* label_y = new QLabel("Угол поворота вокруг оси Y (в градусах):");
	auto* angle_y_input = new QLineEdit();
	main_layout->addWidget(label_y);
	main_layout->addWidget(angle_y_input);

	auto* label_z = new QLabel("Угол поворота вокруг оси Z (в градусах):");
	auto* angle_z_input = new QLineEdit();
	main_layout->addWidget(label_z);
	main_layout->addWidget(angle_z_input);

	auto* button_layout = new QHBoxLayout();
	auto* applyButton = new QPushButton("Применить");
	auto* cancelButton = new QPushButton("Отмена");
	button_layout->addWidget(applyButton);
	button_layout->addWidget(cancelButton);
	main_layout->addLayout(button_layout);

	connect(applyButton, &QPushButton::clicked, [&]() {
		bool okX, okY, okZ;
		float angleX = angle_x_input->text().toFloat(&okX);
		float angleY = angle_y_input->text().toFloat(&okY);
		float angleZ = angle_z_input->text().toFloat(&okZ);

		if (okX && okY && okZ) {
			for (auto element : ui->listWidget->selectedItems()) {
				QVariant v = element->data(Qt::UserRole);
				int id = v.value<int>();
				GraphicConveyor::rotate(models[id], angleX, angleY, angleZ);
			}
			dialog.accept();
		} else {
			QMessageBox::warning(&dialog, "Ошибка", "Введите корректные значения!\nПример правильного ввода: 90\nПример неправильного: Гойда");
		}
	});

	connect(cancelButton, &QPushButton::clicked, [&]() {
		dialog.reject();
	});
	dialog.exec();

	update_scene();
}

void MainWindow::on_scale_clicked()
{
	QDialog dialog;
	dialog.setWindowTitle("Масштабирование модели");
	dialog.setWindowIcon(QIcon(":/toster.png"));

	auto* main_layout = new QVBoxLayout(&dialog);

	auto* label_x = new QLabel("Масштабирование модели вдоль оси X:");
	auto* sx_input = new QLineEdit();
	main_layout->addWidget(label_x);
	main_layout->addWidget(sx_input);

	auto* label_y = new QLabel("Масштабирование модели вдоль оси Y:");
	auto* sy_input = new QLineEdit();
	main_layout->addWidget(label_y);
	main_layout->addWidget(sy_input);

	auto* label_z = new QLabel("Масштабирование модели вдоль оси Z:");
	auto* sz_input = new QLineEdit();
	main_layout->addWidget(label_z);
	main_layout->addWidget(sz_input);

	auto* button_layout = new QHBoxLayout();
	auto* applyButton = new QPushButton("Применить");
	auto* cancelButton = new QPushButton("Отмена");
	button_layout->addWidget(applyButton);
	button_layout->addWidget(cancelButton);
	main_layout->addLayout(button_layout);

	connect(applyButton, &QPushButton::clicked, [&]() {
		bool okX, okY, okZ;
		float sx = sx_input->text().toFloat(&okX);
		float sy = sy_input->text().toFloat(&okY);
		float sz = sz_input->text().toFloat(&okZ);

		if (okX && okY && okZ) {
			for (auto element : ui->listWidget->selectedItems()) {
				QVariant v = element->data(Qt::UserRole);
				int id = v.value<int>();
				GraphicConveyor::scale(models[id], sx, sy, sz);
			}
			dialog.accept();
		} else {
			QMessageBox::warning(&dialog, "Ошибка", "Введите корректные значения!\nПример правильного ввода: 90\nПример неправильного: Гойда");
		}
	});

	connect(cancelButton, &QPushButton::clicked, [&]() {
		dialog.reject();
	});
	dialog.exec();

	update_scene();
}

void MainWindow::on_translate_clicked()
{
	QDialog dialog;
	dialog.setWindowTitle("Перемещение модели");
	dialog.setWindowIcon(QIcon(":/toster.png"));

	auto* main_layout = new QVBoxLayout(&dialog);

	auto* label_x = new QLabel("Перемещение модели вдоль оси X:");
	auto* tx_input = new QLineEdit();
	main_layout->addWidget(label_x);
	main_layout->addWidget(tx_input);

	auto* label_y = new QLabel("Перемещение модели вдоль оси Y:");
	auto* ty_input = new QLineEdit();
	main_layout->addWidget(label_y);
	main_layout->addWidget(ty_input);

	auto* label_z = new QLabel("Перемещение модели вдоль оси Z:");
	auto* tz_input = new QLineEdit();
	main_layout->addWidget(label_z);
	main_layout->addWidget(tz_input);

	auto* button_layout = new QHBoxLayout();
	auto* applyButton = new QPushButton("Применить");
	auto* cancelButton = new QPushButton("Отмена");
	button_layout->addWidget(applyButton);
	button_layout->addWidget(cancelButton);
	main_layout->addLayout(button_layout);

	connect(applyButton, &QPushButton::clicked, [&]() {
		bool okX, okY, okZ;
		float tx = tx_input->text().toFloat(&okX);
		float ty = ty_input->text().toFloat(&okY);
		float tz = tz_input->text().toFloat(&okZ);

		if (okX && okY && okZ) {
			for (auto element : ui->listWidget->selectedItems()) {
				QVariant v = element->data(Qt::UserRole);
				int id = v.value<int>();
				GraphicConveyor::translate(models[id], tx, ty, tz);
			}
			dialog.accept();
		} else {
			QMessageBox::warning(&dialog, "Ошибка", "Введите корректные значения!\nПример правильного ввода: 90\nПример неправильного: Гойда");
		}
	});

	connect(cancelButton, &QPushButton::clicked, [&]() {
		dialog.reject();
	});
	dialog.exec();

	update_scene();
}
void MainWindow::on_btnSelectColor_clicked()
{
	QColor color = QColorDialog::getColor(QColor(255,255,255,255));
	if (!color.isValid()) {
		QMessageBox::information(this, "Erroe", "Incorrect color");
	}
	materials[selected_model].set_basic_color(color);
	materials[selected_model].select_basic_color();
	update_scene();

}
void MainWindow::on_btnAddTexture_clicked()
{
	std::string file_name = QFileDialog::getOpenFileName(this,
		tr("Open Texture"), ":/",
		tr("Object Image (*.png *.jpg *.bmp)")).toUtf8().constData();
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
void MainWindow::on_btnAddLight_clicked()
{
	QColor color = QColorDialog::getColor(QColor(255,255,255,255));
	if (!color.isValid()) {
		QMessageBox::information(this, "Erroe", "Incorrect color");
	}
	QDialog dialog;
	dialog.setWindowTitle("Добавление камеры");

	auto* main_layout = new QVBoxLayout(&dialog);

	auto* label_x = new QLabel("Координата камеры по X:");
	auto* x_input = new QLineEdit();
	main_layout->addWidget(label_x);
	main_layout->addWidget(x_input);

	auto* label_y = new QLabel("Координата камеры по Y:");
	auto* y_input = new QLineEdit();
	main_layout->addWidget(label_y);
	main_layout->addWidget(y_input);

	auto* label_z = new QLabel("Координата камеры по Z:");
	auto* z_input = new QLineEdit();
	main_layout->addWidget(label_z);
	main_layout->addWidget(z_input);

	auto* button_layout = new QHBoxLayout();
	auto* apply_button = new QPushButton("Применить");
	auto* cancel_button = new QPushButton("Отмена");
	button_layout->addWidget(apply_button);
	button_layout->addWidget(cancel_button);
	main_layout->addLayout(button_layout);

	connect(apply_button, &QPushButton::clicked, [&]()
	{
		bool okX, okY, okZ;
		float x = x_input->text().toFloat(&okX);
		float y = y_input->text().toFloat(&okY);
		float z = z_input->text().toFloat(&okZ);

		if (okX && okY && okZ)
		{
			Vector3D pos(x, y, z);
			add_light_list(color, pos);

			dialog.accept();
		} else {
			QMessageBox::warning(&dialog, "Ошибка", "Введите корректные значения!");
		}
	});
	connect(cancel_button, &QPushButton::clicked, [&]() {
		dialog.reject();
	});

	dialog.exec();

}
void MainWindow::add_light_list(const QColor& color, Vector3D& pos)
{//Сюда диалоговое окно нужно;
	//И сюда нужно записать число
	std::string name = "{" + std::to_string(pos.getX()) + ", " + std::to_string(pos.getY()) + ", " + std::to_string(pos.getZ()) + "}";
	light[light_cnt] = Light(color, pos);
	auto light_list_item = new QListWidgetItem(QString::fromStdString(name));
	QVariant v;
	v.setValue(light_cnt);
	light_list_item->setData(Qt::UserRole,v);
	ui->listLightSource->addItem(light_list_item);
	light_cnt++;
}
void MainWindow::on_btnRemoveLight_clicked()
{
	int row = ui->listLightSource->selectionModel()->currentIndex().row();
	int light_id = ui->listLightSource->item(row)->data(Qt::UserRole).value<int>();
	models.erase(light_id);
	auto it = ui->listLightSource->takeItem(ui->listLightSource->currentRow());
	delete it;

}

