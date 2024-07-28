/*
    Definições básicas de câmera
*/

#include "camera.hpp"

// definições
double MAX_ZOOM = 3.f; // zoom máximo permitido
double MIN_ZOOM = 0.1f; // zoom mínimo permitido
double ZOOM_INITIAL = 1.f; // zoom inicial

double ZOOM_MOD = 0.08f; // alteração do zoom

// classe básica
Camera::Camera(int x, int y) : x(x), y(y), zoom(1.f) {}

// cálculo de coordenadas
void Camera::viewport(std::shared_ptr<Window> window, ObjectInfo info, double& x, double& y, double& width, double& height) {
    double cam_x = this->x;
    double cam_y = this->y;

    // cálculo baseado no mundo
    x = info.x - cam_x;
    y = info.y - cam_y;

    // transformações para amostragem na tela
    x *= this->zoom;
    y *= this->zoom;

    width = info.width * this->zoom;
    height = info.height * this->zoom;

    int w_width, w_height;
    window->getDimensions(w_width, w_height);

    x += w_width / 2;
    y += w_height / 2;
}

//

void Camera::zoom_in(void) {
    this->zoom += ZOOM_MOD;

    if (this->zoom > MAX_ZOOM) {
        this->zoom = MAX_ZOOM;
    }
}

void Camera::zoom_out(void) {
    this->zoom -= ZOOM_MOD;

    if (this->zoom < MIN_ZOOM) {
        this->zoom = MIN_ZOOM;
    }
}

void Camera::updateCameraPosition(Mouse mouse) {
    static int last_cam_x = this->x;
    static int last_cam_y = this->y;

    if (mouse.left.hold) {
        int x_diff = mouse.x - mouse.left.hold_x;
        int y_diff = mouse.y - mouse.left.hold_y;

        this->x = last_cam_x - x_diff * (1.f / this->zoom);
        this->y = last_cam_y - y_diff * (1.f / this->zoom);
    } else {
        last_cam_x = this->x;
        last_cam_y = this->y;
    }
}
