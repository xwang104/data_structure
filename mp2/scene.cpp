#include "scene.h"
#include <string>
#include <iostream>
using namespace std;

Scene::Scene(int max){
    _image_pointers = new Image*[max];
    for (int i = 0; i < max; i++)
        _image_pointers[i] = NULL;
    _coordinates = new int*[3];
    for (int i = 0; i < 3; i++)
        _coordinates[i] = new int[max];
    _max = max;
}

void Scene::_clear() {
    for (int i = 0; i < _max; i++) {
        if (_image_pointers[i] != NULL)
            delete _image_pointers[i];
    }
    delete [] _image_pointers;
    _image_pointers = NULL;
    for (int i = 0; i < 3; i++)
        delete [] _coordinates[i];
    delete [] _coordinates;
    _coordinates = NULL;
}

Scene::~Scene(){
    _clear();
}	

void Scene::_copy(const Scene &source) {
    _max = source._max;
    _image_pointers = new Image*[_max];
    for (int i = 0; i < _max; i++) {
        if (source._image_pointers[i] == NULL)
            _image_pointers[i] = NULL;
        else
            _image_pointers[i] = new Image(*source._image_pointers[i]);
    }
    _coordinates = new int*[3];
    for (int i = 0; i < 3; i++) {
        _coordinates[i] = new int [_max];
        for (int j = 0; j < _max; j++)
            _coordinates[i][j] = source._coordinates[i][j]; 
    }
}

Scene::Scene(const Scene & source) {
    _copy(source);
}

const Scene & Scene::operator=(const Scene & source) {
    if (this != &source) {
        _clear();
        _copy(source);
    }
    return *this;
}


void Scene::changemaxlayers(int newmax) {
    if (newmax == _max) 
        return;
    if (newmax < _max) {
        for (int i = newmax; i < _max; i++) {
            if (_image_pointers[i] != NULL) {
                cout << "invalid newmax" << endl;
                return;
            }
        } 
    }
    Image ** scene = _image_pointers;
    bool new_arr = newmax > _max;
    //make a new array if needed
    if (new_arr) {
        scene = new Image*[newmax];
        for (int i = 0; i < newmax; i++) 
            scene[i] = NULL;
    }
    for (int i = 0; i < _max; i++) 
        scene[i] = _image_pointers[i];
    if (new_arr) {
        delete [] _image_pointers;
        _image_pointers = scene;
    }
    _max = newmax;
}	

void Scene::addpicture(const char *FileName, int index, int x, int y) {
    if (index < 0 || _max > 1) {
        cout << "index out of bounds" << endl;
        return;
    }
    if (_image_pointers[index] != NULL) {
        delete _image_pointers[index];
        _image_pointers[index] = NULL;
    }
    _image_pointers[index] = new Image;
    string file_name(FileName);
    _image_pointers[index]->readFromFile(file_name);
    _coordinates[0][index] = index;
    _coordinates[1][index] = x;
    _coordinates[2][index] = y;
}

void Scene::changelayer(int index, int newindex) {
    if (index == newindex) 
        return;
    if (index < 0 || index > _max - 1 || newindex < 0 || newindex > _max - 1) {
        cout << "invalid index" << endl;
        return;
    }
    if (_image_pointers[newindex] != NULL)
        delete _image_pointers[newindex];
    _image_pointers[newindex] = _image_pointers[index] ; 
    if (_image_pointers[index] != NULL) {
        _coordinates[0][newindex] = newindex;
        _coordinates[1][newindex] = _coordinates[1][index];
        _coordinates[2][newindex] = _coordinates[2][index];
    }
    _image_pointers[index] = NULL;
}

void Scene::translate(int index, int xcoord, int ycoord) {
    if (index < 0 || index > _max- 1 || _image_pointers[index] == NULL) {
        cout << "invalid index" << endl;
        return;
    }
    _coordinates[1][index] = xcoord;
    _coordinates[2][index] = ycoord;   
}

void Scene::deletepicture(int index) {
    if (index < 0 || index > _max- 1 || _image_pointers[index] == NULL) {
        cout << "invalid index" << endl;
        return;
    }
    delete _image_pointers[index];
    _image_pointers[index] = NULL;
}

Image * Scene::getpicture(int index) const {
    if (index < 0 || index > _max- 1) {
        cout << "invalid index" << endl;
        return NULL;
    }
    return _image_pointers[index];
}

Image Scene::drawscene() const {
    size_t width = 0;
    size_t height = 0;
    for (int i = 0; i < _max; i++) {
        if (_image_pointers[i] != NULL) {
            width = max(width, (_coordinates[i][1] + _image_pointers[i]->width()));
            height = max(height, (_coordinates[i][2] + _image_pointers[i]->height()));
        }
    } 
    Image output = Image(width, height);
    for (int i = 0; i < _max; i++) {
        if (_image_pointers[i] != NULL) {
            for (int x = _coordinates[i][1]; x < _coordinates[i][1] + _image_pointers[i]->width(); x++) {
                for (int y = _coordinates[i][2]; x < _coordinates[i][2] + _image_pointers[i]->height(); y++) {
                    output(x, y)->red = (*_image_pointers[i])(x - _coordinates[i][1], y - _coordinates[i][2])->red;
                    output(x, y)->green = (*_image_pointers[i])(x - _coordinates[i][1], y - _coordinates[i][2])->green;
                    output(x, y)->blue = (*_image_pointers[i])(x - _coordinates[i][1], y - _coordinates[i][2])->blue;
                }
            }
        }
    }
    return output;
}




