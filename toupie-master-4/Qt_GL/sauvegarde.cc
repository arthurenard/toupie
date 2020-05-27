#include "sauvegarde.h"

Sauvegarde::Sauvegarde()
{

}



bool Sauvegarde::loadFile(){

    QString filename =  QFileDialog::getSaveFileName(
             this,
             "Select Document",
             QDir::currentPath(),
             "Text files (*.txt)");

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
            file << hashData(dataToString(data));
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
        std::vector<std::vector<double> > allData;
         for (int i(0); i < nbToupies - 1; i++) {
             std::vector<double> data;
                for(int j(0) ; j < 15 ; j++){
                    double coord;
                    file2 >> coord;
                    data.push_back(coord);
                }
            emit dataLoaded(data);
            allData.push_back(data);
         }

         size_t hash;
         file2 >> hash;
         if(hashData(dataToString(allData)) != hash){
             emit errorFile();
         }

    }
}


std::string Sauvegarde::dataToString(std::vector<std::vector<double> > data){
std::string phrase;
std::string mot;

    for (size_t i(0) ; i < data.size() ; i++) {
        for (size_t j(0) ; j < data[i].size() ; j++) {
            mot =std::to_string(data[i][j]);
            mot.pop_back();
            mot.pop_back();
            mot.pop_back();
            mot.pop_back();
            phrase += mot;
        }
    }
    return phrase;
}

size_t Sauvegarde::hashData(std::string data){
    std::hash<std::string> hasher;
    return hasher(data);
}

