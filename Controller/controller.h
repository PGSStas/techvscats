#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<Model/model.h>
#include<View/view.h>

class Controller
{
public:
    Controller();
private:
    Model* model_;
    View* view_;
    ~Controller();
};

#endif // CONTROLLER_H
