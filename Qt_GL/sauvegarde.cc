#include "sauvegarde.h"

Sauvegarde::Sauvegarde()
{

}



bool Sauvegarde::loadFile(){

    QString filename =  QFileDialog::getSaveFileName(
             this,
             "Select Document",
             QDir::currentPath(),
             "All files (*.*) ;; Text files (*.txt)");

       if( !filename.isNull() )
       {
           fileName =  filename.toUtf8().toStdString();
           return true;
       }
      fileName =  ":C";
      return false;

}

void Sauvegarde::sauvegarder(std::vector<std::vector<double>> data){
    if(loadFile()){
        std::ofstream file(fileName);

        if(file)
        {
            for (size_t i(0); i < data.size() ; i++) {
                file << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << " " << data[i][4] << " "
                     << data[i][5] << " " << data[i][6] << " " << data[i][7] << " " << data[i][8] << " " << data[i][9] << " "
                     << data[i][10] << " " << data[i][11] << " " << data[i][12] << " " << data[i][13] << " " << data[i][14] << std::endl;
            }
        }
        else
        {
            //GESTION DERREUR A AJOUTER
        }
    }
}

void Sauvegarde::charger(){
    if(loadFile()){
        std::ifstream file(fileName);
         int nbToupies(0);
         std::string line;
         while(std::getline(file, line)){nbToupies ++;}
        file.close();
        std::ifstream file2(fileName);
         for (int i(0); i < nbToupies; i++) {
             std::vector<double> data;
                for(int j(0) ; j < 15 ; j++){
                    double coord;
                    file2 >>  coord;
                    data.push_back(coord);
                }
            emit dataLoaded(data);
         }

    }
}
