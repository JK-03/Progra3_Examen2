#include "cframe.h"
#include "ui_cframe.h"
#include <QMessageBox>
#include <estudiantemaestria.h>
#include <EstudianteLicenciatura.h>
#include <automovil.h>
#include <camion.h>
#include <float.h>
#include <QDialog>
#include <QInputDialog>
#include <Vehiculo.h>
#include <empleadofijo.h>
#include <empleadocontratado.h>
#include "Libro.h"
#include "Revista.h"
#include "ArticuloCientifico.h"

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);

    cargarPublicacionesDesdeBaseDatos();
    cargarEstudiantesDesdeBaseDatos();
    cargarVehiculosDesdeBaseDatos();
    cargarEmpleadosDesdeBaseDatos();

    for (auto estudiante : estudiantes) delete estudiante;
    for (auto vehiculo : vehiculos) delete vehiculo;
    for (auto empleado : empleados) delete empleado;
    for (auto publicacion : publicaciones) delete publicacion;

    conectarBaseDatosEstudiantes();
    conectarBaseDatosVehiculos();
    conectarBaseDatosEmpleados();
    conectarBaseDatosLibros();

    this->ui->tabWidget->setCurrentIndex(0);
    ui->LE_Numero->setDisabled(true);
    connect(ui->cob_EstudianteTipo, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cob_EstudianteTipo_currentIndexChanged(int)));
}

cframe::~cframe()
{
    delete ui;
}

void cframe::on_cob_EstudianteTipo_currentIndexChanged(int index) {
    tipoSeleccionado = ui->cob_EstudianteTipo->currentText().toStdString();
    if (tipoSeleccionado == "Nuevo") {
        ui->LE_Numero->setDisabled(true);
    } else if (tipoSeleccionado == "Existente") {
        ui->LE_Numero->setEnabled(true);
    }
}

void cframe::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion4 = msgBox.addButton("Salir", QMessageBox::ActionRole);
    QPushButton *opcion5 = msgBox.addButton("Registro", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Ejercicio #3", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Ejercicio #2", QMessageBox::ActionRole);
    QPushButton *opcion1 = msgBox.addButton("Ejercicio #1", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion1) {
        ui->tabWidget->setCurrentIndex(1);
    } else if (msgBox.clickedButton() == opcion2) {
        ui->tabWidget->setCurrentIndex(2);
    } else if (msgBox.clickedButton() == opcion3) {
        ui->tabWidget->setCurrentIndex(3);
    } else if (msgBox.clickedButton() == opcion5) {
        QMessageBox submenu;
        submenu.setText("¿Qué tipo de registro desea cargar?");

        QPushButton *estudiantesBtn = submenu.addButton("Estudiantes", QMessageBox::ActionRole);
        QPushButton *vehiculosBtn = submenu.addButton("Vehículos de Flota", QMessageBox::ActionRole);
        QPushButton *empleadosBtn = submenu.addButton("Empleados", QMessageBox::ActionRole);
        QPushButton *bibliotecaBtn = submenu.addButton("Biblioteca", QMessageBox::ActionRole);
        QPushButton *cancelarBtn = submenu.addButton("Cancelar", QMessageBox::ActionRole);

        submenu.exec();

        if (submenu.clickedButton() == estudiantesBtn) {
            baseDatosOpcion = "Estudiantes";
            ui->tabWidget->setCurrentIndex(5);
            actualizarTablaEstudiantes();
        } else if (submenu.clickedButton() == vehiculosBtn) {
            baseDatosOpcion = "Vehículos de Flota";
            ui->tabWidget->setCurrentIndex(5);
            actualizarTablaVehiculos();
        } else if (submenu.clickedButton() == empleadosBtn) {
            baseDatosOpcion = "Empleados";
            ui->tabWidget->setCurrentIndex(5);
            actualizarTablaEmpleados();
        } else if (submenu.clickedButton() == bibliotecaBtn) {
            baseDatosOpcion = "Biblioteca";
            ui->tabWidget->setCurrentIndex(5);
            actualizarTablaPublicaciones();
        }

    } else if (msgBox.clickedButton() == opcion4) {
        this->close();
    }
}

//EJERCICIOS #1
void cframe::on_agregarClaseBoton_clicked() {
    QString numeroCuenta = ui->LE_Numero->text();
    QString materia = ui->LE_Materia->text();
    int calificacion = ui->spb_Cali->value();
    QString tipoSeleccionadoESTU = ui->cob_Estudiante->currentText();

    if (materia.isEmpty() || (tipoSeleccionado == "Existente" && numeroCuenta.isEmpty())) {
        QMessageBox::warning(this, "Error", "Por favor, introduce el número de cuenta y una materia con calificación.");
        return;
    }

    Estudiante* estudianteExistente = nullptr;

    qDebug() << tipoSeleccionado;
    if (tipoSeleccionado == "Existente") {
        for (const auto& estudiante : estudiantes) {
            if (estudiante->obtenerNumeroCuenta() == numeroCuenta.toStdString()) {
                estudianteExistente = estudiante;
                break;
            }
        }

        if (estudianteExistente) {
            estudianteExistente->agregarMateria(materia.toStdString(), calificacion);
            QMessageBox::information(this, "Éxito", "La materia y calificación han sido agregadas correctamente.");
        } else {
            QMessageBox::warning(this, "Error", "No se encontró un estudiante con ese número de cuenta.");
        }
    } else {
        QString nombre = ui->LE_Nombre->text();
        int edad = ui->spb_Edad->value();

        if (nombre.isEmpty()) {
            QMessageBox::warning(this, "Error", "Por favor, introduce el nombre del estudiante.");
            return;
        }

        Estudiante* nuevoEstudiante = nullptr;

        if (tipoSeleccionadoESTU == "Licenciatura") {
            nuevoEstudiante = new EstudianteLicenciatura(nombre.toStdString(), edad);
        } else if (tipoSeleccionadoESTU == "Maestría") {
            nuevoEstudiante = new EstudianteMaestria(nombre.toStdString(), edad);
        }

        nuevoEstudiante->agregarMateria(materia.toStdString(), calificacion);
        estudiantes.push_back(nuevoEstudiante);
        QMessageBox::information(this, "Éxito", "El estudiante ha sido agregado correctamente.");
    }

    ui->LE_Nombre->clear();
    ui->spb_Edad->setValue(0);
    ui->LE_Numero->clear();
    ui->LE_Materia->clear();
}

void cframe::actualizarTablaEstudiantes() {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    QStringList encabezados;
    encabezados << "Número de Cuenta" << "Nombre" << "Edad" << "Materias" << "Calificaciones" << "Promedio";
    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    for (const auto& estudiante : estudiantes) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(estudiante->obtenerNumeroCuenta())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(estudiante->obtenerNombre())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(estudiante->obtenerEdad())));

        QString materias;
        QString calificaciones;
        const auto& mat = estudiante->obtenerMaterias();
        const auto& calif = estudiante->obtenerCalificaciones();

        for (size_t i = 0; i < mat.size(); ++i) {
            materias += QString::fromStdString(mat[i]);
            calificaciones += QString::number(calif[i]);
            if (i < mat.size() - 1) {
                materias += ", ";
                calificaciones += ", ";
            }
        }

        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(materias));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(calificaciones));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(estudiante->promedio())));
    }
}

void cframe::conectarBaseDatosEstudiantes() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString rutaBaseDatos = QCoreApplication::applicationDirPath() + "/estudiantes.sqlite";
    db.setDatabaseName(rutaBaseDatos);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS estudiantes ("
                    "numero_cuenta TEXT PRIMARY KEY, "
                    "nombre TEXT, "
                    "edad INTEGER, "
                    "materia TEXT, "
                    "calificacion REAL)")) {
        QMessageBox::warning(this, "Error", "No se pudo crear la tabla: " + query.lastError().text());
    }
}

void cframe::on_pushButton_2_clicked() {
    if (baseDatosOpcion == "Estudiantes") {
        guardarEstudiantesEnBaseDeDatos();
    } else if (baseDatosOpcion == "Vehículos de Flota") {
        guardarVehiculosEnBaseDeDatos();
    } else if (baseDatosOpcion == "Empleados") {
        guardarEmpleadosEnBaseDeDatos();
    } else if (baseDatosOpcion == "Biblioteca") {
        guardarPublicacionesEnBaseDeDatos();
    }

}

void cframe::guardarEstudiantesEnBaseDeDatos() {
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString numeroCuenta = ui->tableWidget->item(row, 0)->text();
        QString nombre = ui->tableWidget->item(row, 1)->text();
        int edad = ui->tableWidget->item(row, 2)->text().toInt();
        QString materia = ui->tableWidget->item(row, 3)->text();
        double calificacion = ui->tableWidget->item(row, 4)->text().toDouble();

        QSqlQuery query;
        query.prepare("INSERT OR REPLACE INTO estudiantes (numero_cuenta, nombre, edad, materia, calificacion) "
                      "VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(numeroCuenta);
        query.addBindValue(nombre);
        query.addBindValue(edad);
        query.addBindValue(materia);
        query.addBindValue(calificacion);

        if (!query.exec()) {
            QMessageBox::warning(this, "Error", "No se pudo guardar el estudiante: " + query.lastError().text());
        }
    }
}

void cframe::cargarEstudiantesDesdeBaseDatos() {
    QSqlQuery query("SELECT * FROM estudiantes");

    while (query.next()) {
        QString numeroCuenta = query.value("numero_cuenta").toString();
        QString nombre = query.value("nombre").toString();
        int edad = query.value("edad").toInt();
        QString materia = query.value("materia").toString();
        double calificacion = query.value("calificacion").toDouble();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(numeroCuenta));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nombre));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(edad)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(materia));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(calificacion)));
    }
}


//EJERCICIO #2
void cframe::on_agregarVehiculo_clicked() {
    QString modelo = ui->LE_Modelo->text();
    int año = ui->spb_Year->value();
    float kilometraje = ui->spb_Kilo->value();

    QString tipoSeleccionado = ui->cob_Vehiculo->currentText();

    Vehiculo* nuevoVehiculo = nullptr;

    if (tipoSeleccionado == "Camión") {
        bool ok;
        double capacidadCarga = QInputDialog::getDouble(this, "Capacidad de Carga", "Introduce la capacidad de carga (kg):", 0, 0, 100000, 1, &ok);

        if (ok) {
            nuevoVehiculo = new Camion(modelo.toStdString(), año, kilometraje, capacidadCarga);
        }
    } else if (tipoSeleccionado == "Automóvil") {
        nuevoVehiculo = new Automovil(modelo.toStdString(), año, kilometraje);
    }

    if (nuevoVehiculo) {
        flota.agregarVehiculo(nuevoVehiculo);
        QMessageBox::information(this, "Éxito", "Vehículo agregado correctamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo agregar el vehículo.");
    }

    ui->LE_Modelo->clear();
    ui->spb_Year->setValue(0);
    ui->spb_Kilo->setValue(0);
}

void cframe::actualizarTablaVehiculos() {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    QStringList encabezados;
    encabezados << "Modelo" << "Año" << "Kilometraje" << "Tipo" << "Costo de Mantenimiento";
    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    for (const auto& vehiculo : flota.obtenerVehiculos()) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(vehiculo->obtenerModelo())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(vehiculo->obtenerAño())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(vehiculo->obtenerKilometraje())));

        QString tipo;
        if (dynamic_cast<Camion*>(vehiculo)) {
            tipo = "Camión";
        } else if (dynamic_cast<Automovil*>(vehiculo)) {
            tipo = "Automóvil";
        } else {
            tipo = "Desconocido";
        }

        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(tipo));

        float costoMantenimiento = vehiculo->calcularMantenimiento();
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(costoMantenimiento)));
    }
}

void cframe::conectarBaseDatosVehiculos() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString rutaBaseDatos = QCoreApplication::applicationDirPath() + "/vehiculos.sqlite";
    db.setDatabaseName(rutaBaseDatos);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS vehiculos ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "modelo TEXT, "
                    "año INTEGER, "
                    "kilometraje REAL, "
                    "tipo TEXT, "
                    "costo_mantenimiento REAL)")) {
        QMessageBox::warning(this, "Error", "No se pudo crear la tabla: " + query.lastError().text());
    }
}

void cframe::guardarVehiculosEnBaseDeDatos() {
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString modelo = ui->tableWidget->item(row, 0)->text();
        int año = ui->tableWidget->item(row, 1)->text().toInt();
        float kilometraje = ui->tableWidget->item(row, 2)->text().toFloat();
        QString tipo = ui->tableWidget->item(row, 3)->text();

        float costoMantenimiento = 0.0;

        for (const auto& vehiculo : flota.obtenerVehiculos()) {
            if (vehiculo->obtenerModelo() == modelo.toStdString() &&
                std::to_string(vehiculo->obtenerAño()) == std::to_string(año)) {

                if (dynamic_cast<Camion*>(vehiculo)) {
                    costoMantenimiento = static_cast<Camion*>(vehiculo)->calcularMantenimiento();
                } else if (dynamic_cast<Automovil*>(vehiculo)) {
                    costoMantenimiento = static_cast<Automovil*>(vehiculo)->calcularMantenimiento();
                }
                break;
            }
        }

        QSqlQuery query;
        query.prepare("INSERT OR REPLACE INTO vehiculos (modelo, año, kilometraje, tipo, costo_mantenimiento) "
                      "VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(modelo);
        query.addBindValue(año);
        query.addBindValue(kilometraje);
        query.addBindValue(tipo);
        query.addBindValue(costoMantenimiento);

        if (!query.exec()) {
            QMessageBox::warning(this, "Error", "No se pudo guardar el vehículo: " + query.lastError().text());
        }
    }
}

void cframe::cargarVehiculosDesdeBaseDatos() {
    QSqlQuery query("SELECT * FROM vehiculos");

    while (query.next()) {
        QString modelo = query.value("modelo").toString();
        int año = query.value("año").toInt();
        float kilometraje = query.value("kilometraje").toFloat();
        QString tipo = query.value("tipo").toString();
        float costoMantenimiento = query.value("costo_mantenimiento").toFloat();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(modelo));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(año)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(kilometraje)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(tipo));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(costoMantenimiento)));
    }
}


//EJERCICIO #3
void cframe::on_agregarEmpleado_clicked()
{
    QString nombre = ui->LE_NombreEmpleado->text();
    QString tipoEmpleado = ui->cob_Empleado->currentText();
    int edad = ui->spb_EdadEmpleado->value();
    double salario = ui->spb_Salario->value();
    int horasTrabajadas = 0;

    if (tipoEmpleado == "Contratado") {
        bool ok;
        horasTrabajadas = QInputDialog::getInt(this, "Horas Trabajadas", "Ingrese las horas trabajadas:", 0, 0, 168, 1, &ok);

        if (!ok) {
            return;
        }
    }

    if (nombre.isEmpty() || edad <= 0 || salario <= 0 || (tipoEmpleado == "Contratado" && horasTrabajadas <= 0)) {
        QMessageBox::warning(this, "Advertencia", "Por favor, complete todos los campos.");
        return;
    }

    Empleado* nuevoEmpleado = nullptr;

    if (tipoEmpleado == "Fijo") {
        nuevoEmpleado = new EmpleadoFijo(nombre.toStdString(), edad, salario);
    } else if (tipoEmpleado == "Contratado") {
        nuevoEmpleado = new EmpleadoContratado(nombre.toStdString(), edad, salario, horasTrabajadas);
    }

    if (nuevoEmpleado) {
        empleados.push_back(nuevoEmpleado);
        ui->LE_NombreEmpleado->clear();
        ui->spb_EdadEmpleado->setValue(0);
        ui->spb_Salario->setValue(0.0);
        QMessageBox::information(this, "Éxito", "Empleado agregado exitosamente.");
    }
}

void cframe::actualizarTablaEmpleados() {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    QStringList encabezados;
    encabezados << "Nombre" << "Edad" << "Salario" << "Tipo de Empleado" << "Horas Trabajadas" << "Salario Calculado";
    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    for (const auto& empleado : empleados) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(empleado->getNombre())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(empleado->getEdad())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(empleado->getSalario())));

        QString tipo;
        int horasTrabajadas = 0;

        if (dynamic_cast<EmpleadoFijo*>(empleado)) {
            tipo = "Fijo";
        } else if (EmpleadoContratado* contratado = dynamic_cast<EmpleadoContratado*>(empleado)) {
            tipo = "Contratado";
            horasTrabajadas = contratado->getHorasTrabajadas();
        } else {
            tipo = "Desconocido";
        }

        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(tipo));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(horasTrabajadas)));

        float salarioCalculado = empleado->calcularSalario();
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(QString::number(salarioCalculado)));
    }
}

void cframe::conectarBaseDatosEmpleados() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString rutaBaseDatos = QCoreApplication::applicationDirPath() + "/empleados.sqlite";
    db.setDatabaseName(rutaBaseDatos);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS empleados ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nombre TEXT, "
                    "edad INTEGER, "
                    "salario REAL, "
                    "tipo TEXT, "
                    "horas_trabajadas INTEGER, "
                    "salario_calculado REAL)")) {
        QMessageBox::warning(this, "Error", "No se pudo crear la tabla: " + query.lastError().text());
    }
}

void cframe::guardarEmpleadosEnBaseDeDatos() {
    for (const auto& empleado : empleados) {
        QSqlQuery query;
        query.prepare("INSERT INTO empleados (nombre, edad, salario, tipo, horas_trabajadas, salario_calculado) "
                      "VALUES (?, ?, ?, ?, ?, ?)");

        query.addBindValue(QString::fromStdString(empleado->getNombre()));
        query.addBindValue(empleado->getEdad());

        if (dynamic_cast<EmpleadoFijo*>(empleado)) {
            query.addBindValue(empleado->getSalario());
            query.addBindValue("Fijo");
            query.addBindValue(0);
        } else if (EmpleadoContratado* contratado = dynamic_cast<EmpleadoContratado*>(empleado)) {
            query.addBindValue(contratado->getTarifaPorHora());
            query.addBindValue("Contratado");
            query.addBindValue(contratado->getHorasTrabajadas());
        }

        float salarioCalculado = empleado->calcularSalario();
        query.addBindValue(salarioCalculado);

        if (!query.exec()) {
            QMessageBox::warning(this, "Error", "No se pudo guardar el empleado: " + query.lastError().text());
        }
    }
}

//EJERCICIO #4
void cframe::on_agregarEmpleado_3_clicked() {
    QString tipoPublicacion = ui->cob_Libro->currentText();
    QString titulo = ui->LE_Titulo->text();
    QString autor = ui->LE_Autor->text();
    int anioPublicacion = ui->spb_YearPubli->value();
    QString disponibilidadTexto = ui->cb_Disponible->currentText();
    bool disponible = (disponibilidadTexto == "Sí");

    if (titulo.isEmpty() || autor.isEmpty() || anioPublicacion <= 0) {
        QMessageBox::warning(this, "Advertencia", "Por favor, complete todos los campos.");
        return;
    }

    Publicacion* nuevaPublicacion = nullptr;

    if (tipoPublicacion == "Libro") {
        bool ok;
        int numeroPaginas = QInputDialog::getInt(this, "Número de Páginas", "Ingrese el número de páginas:", 0, 0, 10000, 1, &ok);
        if (!ok) return;
        nuevaPublicacion = new Libro(titulo.toStdString(), autor.toStdString(), anioPublicacion, disponible, numeroPaginas);
    } else if (tipoPublicacion == "Revista") {
        bool ok;
        int numeroEdicion = QInputDialog::getInt(this, "Número de Edición", "Ingrese el número de edición:", 0, 0, 10000, 1, &ok);
        if (!ok) return;
        nuevaPublicacion = new Revista(titulo.toStdString(), autor.toStdString(), anioPublicacion, disponible, numeroEdicion);
    } else if (tipoPublicacion == "Artículo Científico") {
        bool ok;
        int indiceImpacto = QInputDialog::getInt(this, "Índice de Impacto", "Ingrese el índice de impacto:", 0, 0, 10000, 1, &ok);
        if (!ok) return;
        nuevaPublicacion = new ArticuloCientifico(titulo.toStdString(), autor.toStdString(), anioPublicacion, disponible, indiceImpacto);
    }

    if (nuevaPublicacion) {
        publicaciones.push_back(nuevaPublicacion);
        QMessageBox::information(this, "Éxito", "Publicación agregada exitosamente.");
        ui->LE_Titulo->clear();
        ui->LE_Autor->clear();
        ui->spb_YearPubli->setValue(0);
        ui->cb_Disponible->setCurrentIndex(0);
    }
}

void cframe::on_agregarEmpleado_2_clicked() {
    QString titulo = ui->LE_Titulo->text();
    QString autor = ui->LE_Autor->text();
    int anioPublicacion = ui->spb_YearPubli->value();

    QString info = "No se encontró el libro.\n";

    for (const auto& publicacion : publicaciones) {
        if (auto libro = dynamic_cast<Libro*>(publicacion)) {
            if (libro->getTitulo() == titulo.toStdString() &&
                libro->getAutor() == autor.toStdString() &&
                libro->getAnioPublicacion() == anioPublicacion) {
                info = libro->getInformacion().c_str();
                break;
            }
        }
    }

    ui->plainTextEdit->setPlainText(info);
}

void cframe::actualizarTablaPublicaciones() {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    QStringList encabezados;
    encabezados << "Título" << "Autor" << "Año" << "Disponibilidad" << "Número de Páginas/Edición/Índice" << "Tipo";
    ui->tableWidget->setHorizontalHeaderLabels(encabezados);

    for (const auto& publicacion : publicaciones) {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);

        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(publicacion->getTitulo())));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::fromStdString(publicacion->getAutor())));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(QString::number(publicacion->getAnioPublicacion())));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(publicacion->isDisponible() ? "Sí" : "No"));

        if (Libro* libro = dynamic_cast<Libro*>(publicacion)) {
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(libro->getNumeroPaginas())));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem("Libro"));
        } else if (Revista* revista = dynamic_cast<Revista*>(publicacion)) {
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(revista->getNumeroEdicion())));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem("Revista"));
        } else if (ArticuloCientifico* articulo = dynamic_cast<ArticuloCientifico*>(publicacion)) {
            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(QString::number(articulo->getIndiceImpacto())));
            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem("Artículo Científico"));
        }
    }
}

void cframe::conectarBaseDatosLibros() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString rutaBaseDatos = QCoreApplication::applicationDirPath() + "/publicaciones.sqlite";
    db.setDatabaseName(rutaBaseDatos);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS publicaciones ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "titulo TEXT, "
                    "autor TEXT, "
                    "anio INTEGER, "
                    "tipo TEXT, "
                    "numero_paginas INTEGER, "
                    "indice_impacto INTEGER)")) {
        QMessageBox::warning(this, "Error", "No se pudo crear la tabla: " + query.lastError().text());
    }
}

void cframe::guardarPublicacionesEnBaseDeDatos() {
    for (const auto& publicacion : publicaciones) {
        QSqlQuery query;
        query.prepare("INSERT INTO publicaciones (titulo, autor, anio, tipo, numero_paginas, indice_impacto) "
                      "VALUES (?, ?, ?, ?, ?, ?)");

        query.addBindValue(QString::fromStdString(publicacion->getTitulo()));
        query.addBindValue(QString::fromStdString(publicacion->getAutor()));
        query.addBindValue(publicacion->getAnioPublicacion());

        if (dynamic_cast<Libro*>(publicacion)) {
            query.addBindValue("Libro");
            query.addBindValue(dynamic_cast<Libro*>(publicacion)->getNumeroPaginas());
            query.addBindValue(0);
        } else if (dynamic_cast<Revista*>(publicacion)) {
            query.addBindValue("Revista");
            query.addBindValue(0);
            query.addBindValue(dynamic_cast<Revista*>(publicacion)->getNumeroEdicion());
        } else if (dynamic_cast<ArticuloCientifico*>(publicacion)) {
            query.addBindValue("Artículo Científico");
            query.addBindValue(0);
            query.addBindValue(dynamic_cast<ArticuloCientifico*>(publicacion)->getIndiceImpacto());
        }

        if (!query.exec()) {
            QMessageBox::warning(this, "Error", "No se pudo guardar la publicación: " + query.lastError().text());
        }
    }
}

void cframe::cargarPublicacionesDesdeBaseDatos() {
    QSqlQuery query("SELECT * FROM publicaciones");

    while (query.next()) {
        std::string titulo = query.value("titulo").toString().toStdString();
        std::string autor = query.value("autor").toString().toStdString();
        int anioPublicacion = query.value("anio_publicacion").toInt();
        bool disponible = query.value("disponible").toBool();
        QString tipo = query.value("tipo").toString();

        Publicacion* nuevaPublicacion = nullptr;

        if (tipo == "Libro") {
            int numeroPaginas = query.value("numero_paginas").toInt();
            nuevaPublicacion = new Libro(titulo, autor, anioPublicacion, disponible, numeroPaginas);
        } else if (tipo == "Revista") {
            int numeroEdicion = query.value("numero_edicion").toInt();
            nuevaPublicacion = new Revista(titulo, autor, anioPublicacion, disponible, numeroEdicion);
        } else if (tipo == "Artículo Científico") {
            int indiceImpacto = query.value("indice_impacto").toInt();
            nuevaPublicacion = new ArticuloCientifico(titulo, autor, anioPublicacion, disponible, indiceImpacto);
        }

        if (nuevaPublicacion) {
            publicaciones.push_back(nuevaPublicacion);
        }
    }
}

void cframe::cargarEmpleadosDesdeBaseDatos() {
    QSqlQuery query("SELECT * FROM empleados");

    while (query.next()) {
        QString nombre = query.value("nombre").toString();
        int edad = query.value("edad").toInt();
        float salario = query.value("salario").toFloat();
        QString tipo = query.value("tipo").toString();
        int horasTrabajadas = query.value("horas_trabajadas").toInt();
        float salarioCalculado = query.value("salario_calculado").toFloat();

        if (tipo == "Fijo") {
            empleados.push_back(new EmpleadoFijo(nombre.toStdString(), edad, salario));
        } else if (tipo == "Contratado") {
            empleados.push_back(new EmpleadoContratado(nombre.toStdString(), edad, salario, horasTrabajadas));
        }

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(nombre));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(edad)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(salario)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(tipo));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(horasTrabajadas)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(salarioCalculado)));
    }
}

