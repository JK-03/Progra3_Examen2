#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include <Estudiante.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <flota.h>
#include <empleado.h>
#include <publicacion.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

    void actualizarTablaVehiculos();
    void on_cob_EstudianteTipo_currentIndexChanged(int index);
    void conectarBaseDatosEstudiantes();
    void actualizarTablaEstudiantes();
    void guardarEstudiantesEnBaseDeDatos();
    void guardarVehiculosEnBaseDeDatos();
    void conectarBaseDatosVehiculos();
    void actualizarTablaEmpleados();
    void conectarBaseDatosEmpleados();
    void guardarEmpleadosEnBaseDeDatos();
    void actualizarTablaPublicaciones();
    void conectarBaseDatosLibros();
    void guardarPublicacionesEnBaseDeDatos();

private slots:
    void on_pushButton_clicked();

    void on_agregarClaseBoton_clicked();

    void on_pushButton_2_clicked();

    void on_agregarVehiculo_clicked();


    void on_agregarEmpleado_clicked();

    void on_agregarEmpleado_3_clicked();

    void on_agregarEmpleado_2_clicked();

private:
    Ui::cframe *ui;

    QSqlDatabase db;

    std::string baseDatosOpcion;

    std::vector<Estudiante*> estudiantes;
    std::vector<Vehiculo*> vehiculos;
    std::vector<Empleado*> empleados;
    std::vector<Publicacion*> publicaciones;

    std::string opcionSeleccionada;
    std::string tipoSeleccionado;
    Flota flota;
};
#endif // CFRAME_H
