#include "mainwindow.h"
#include <time.h>
#include "ui_mainwindow.h"
#include <QProcess>
#include <bits/stdc++.h>
#include <QDebug>
#include <QThread>
#include <cctype>
#include <dirent.h>
#include <QObject>
#include <QMessageBox>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
using namespace std;
QProcess myProcess;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cout<<"Ok!"<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

string GetStdoutFromCommand(string cmd) {
    char *directory = "/home/tablin/proyectoGrafica/proyectoBuild/Linux-x86_64-RELEASE/";
    int ret;
    ret = chdir (directory);
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    //cout<<data<<endl;
    return data;
}

void MainWindow::on_cpm_btn_clicked()
{

        QString arg1 = ui->in_folder->text();
        QString arg2 = ui->out_folder->text();
        string dato = arg1.toStdString();
        string salida = arg2.toStdString();
        dato = "/home/tablin/proyectoGrafica/proyectoBuild/software/SfM/" + dato;  //url de la carpeta con las imagenes
        salida = "/home/tablin/proyectoGrafica/proyectoBuild/software/SfM/" + salida;  //url de la carpeta con las imagenes
        string emparejado= salida +"/matches";
        string reconstruccion= salida +"/reconstruction_sequential";
        GetStdoutFromCommand("mkdir " + salida);
        const char * c = dato.c_str();
        DIR* dir = opendir(c);
        if(dato=="" || salida=="")
        {
            QMessageBox::warning(this,tr("Warning!!"),tr("Llene los campos de los Archivos de Salida/Entrada"));
            return;
        }
        else{
            if(dir){
                dirent* ent = readdir(dir);
                string nombre;
                if(dirent* ent = readdir(dir))
                    nombre = ent->d_name;
                closedir(dir);
                QPixmap Image((dato + "/" + nombre).c_str());
                QMatrix rm;
                rm.rotate(90);
                Image = Image.transformed(rm);
                ui->img_source->setPixmap(Image);
                ui->Action->setText("1. Analisis Intrinseco");
                QThread::sleep(2);
                string command="./openMVG_main_SfMInit_ImageListing -i " + dato + " -o " + emparejado  + " -d /home/tablin/proyectoGrafica/openMVG/src/openMVG/exif/sensor_width_database/sensor_width_camera_database.txt";
                cout<<"openMVG_main_SfMInit_ImageListing"<<endl;
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(10);
                ui->Action->setText("2. Extraccion de caracteristicas");
                cout<<"openMVG_main_ComputeFeatures"<<endl;
                //QThread::sleep(2);
                command="./openMVG_main_ComputeFeatures -i " + emparejado +"/sfm_data.json" + " -o " + emparejado  + " -m SIFT";
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(30);
                ui->Action->setText("3. Emparejado");
                 cout<<"openMVG_main_ComputeMatches"<<endl;
                command="./openMVG_main_ComputeMatches -i " + emparejado +"/sfm_data.json" + " -o " + emparejado;
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(50);
                ui->Action->setText("4. Hacer reconstruccion incremental");
                cout<<"openMVG_main_ComputeMatches"<<endl;
                command="./openMVG_main_IncrementalSfM -i " + emparejado +"/sfm_data.json -m" + emparejado + " -o " + reconstruccion;
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(60);
                ui->Action->setText("5. Coloreado");
                command="./openMVG_main_ComputeSfM_DataColor -i " + reconstruccion + "/sfm_data.bin -o " + reconstruccion +"/colorized.ply";
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(74);
                ui->Action->setText("6. Triangulacion Robusta");
                QThread::sleep(3);
                command="./openMVG_main_ComputeStructureFromKnownPoses -i " + reconstruccion + "/sfm_data.bin -m "+ emparejado +" -f "+ emparejado+"/matches.f.bin" +" -o " + reconstruccion +"/robust.bin";
                cout<<GetStdoutFromCommand(command)<<endl;
                command="./openMVG_main_ComputeSfM_DataColor -i " + reconstruccion + "/robust.bin -o " + reconstruccion +"/robust_colorized.ply";
                cout<<GetStdoutFromCommand(command)<<endl;
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(86);
                ui->Action->setText("Escaneo Completado");
                ui->Barra1->setMaximum(100);
                ui->Barra1->setMinimum(0);
                ui->Barra1->setValue(100);
                myProcess.finished(0);
            }
            else{
                QMessageBox::warning(this,tr("Warning!!"),tr("El direcctorio de entrada\nNo Existe!!"));
                return;
            }
        }

}

void MainWindow::on_meshlab_btn_clicked()
{
    FILE* meshlab_file;
        string muestra = ui->itemize->currentText().remove(" ").toStdString();
        QString arg2 = ui->out_folder->text();
        string salida = arg2.toStdString();

        string path_salida = "/home/tablin/proyectoGrafica/proyectoBuild/software/SfM/";
        if(salida==""){
            QMessageBox::warning(this,tr("Warning!!"),tr("El directorio de Salida no existe."));
            return;
        }
        else{
            //salida = salida + "carpeta";
            if(muestra=="NubedePuntos"){
                ui->Action->setText("Meshlab Nube de Puntos");
                string comando = "cd " + path_salida + salida + "/reconstruction_sequential"+"; meshlab colorized.ply";
                if ((meshlab_file = popen(comando.c_str(), "r")) == NULL)
                    return;
            }
            else if(muestra=="Textura"){
                ui->Action->setText("Meshlab Textura");
                string comando = "cd /home/tablin/Downloads/; meshlab poison.ply";
                if ((meshlab_file = popen(comando.c_str(), "r")) == NULL)
                    return;
            }
            else return;
        }
}
