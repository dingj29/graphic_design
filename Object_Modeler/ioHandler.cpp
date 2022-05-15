//
// Created by WILL on 2021/12/6.
//
#include "ioHandler.h"

std::vector<Object> ioHandler::loadGame() {
    printf("Please enter the file name:");
    std::string filename;
    std::cin >> filename;
    std::ifstream file(filename);
    if (!file.good()){
        printf("File not Exist");
        return std::vector<Object>{};
    }
    std::vector<Object> temp_vec;
    std::string temp_str = "";
    std::getline(file, temp_str);
    printf("%d Object detected\n",std::stoi(temp_str)/11);
    for (int i = 0; i < std::stoi(temp_str) / 11;i++)
    {
        std::string temp_float;
        Object temp = Object(EMERALD, CUBE);
        std::getline(file, temp_float);
        temp.position[0] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.orientation[0] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.scale[0] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.position[1] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.orientation[1] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.scale[1] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.position[2] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.orientation[2] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.scale[2] = std::stof(temp_float);
        std::getline(file, temp_float);
        temp.obj_shape = static_cast<Shape> (std::stoi(temp_float));
        std::getline(file, temp_float);
        temp.obj_material = static_cast<Material> (std::stoi(temp_float));
        temp_vec.push_back(temp);
    }
    return temp_vec;
}

void ioHandler::saveGame(std::vector<Object> objects) {
    printf("Please enter the file name:");
    std::string filename;
    std::cin >> filename;
    std::ofstream file(filename);
    file << objects.size()*11 << std::endl;
    for (auto o:objects){
        for (int i = 0; i < 3; ++i) {
            file << o.position[i] << std::fixed << std::setprecision(3) << std::endl;
            file << o.orientation[i] << std::fixed << std::setprecision(3) << std::endl;
            file << o.scale[i] << std::fixed << std::setprecision(3) << std::endl;
        }
        file << o.obj_shape << std::endl;
        file << o.obj_material << std::endl;
    }
    file.close();
    }
