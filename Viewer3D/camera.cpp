#include "camera.h"
#include "matrix_transform.hpp"
#include "rotate_vector.hpp"
#include "Utils/utils.h"
#include <QMatrix4x4>

Camera::Camera(QObject *parent) :
    QObject(parent),
    dir(0, 1, 0),
    UP(0, 0, 1),
    fovy(45)
{}

glm::mat4x4 Camera::MVMat()
{
    return glm::lookAt(eye, eye + dir, UP);
}

glm::mat4x4 Camera::MVPMat()
{
    return perspectiveMat * MVMat();
}

glm::mat4x4 Camera::NormalMatrix()
{
    return glm::transpose(glm::inverse(MVMat()));
}

void Camera::MouseMove(glm::vec2 delta)
{
    glm::vec2 deltaDeg;
    deltaDeg.y = glm::radians(3.0f * fovy * delta.y / width);
    deltaDeg.x = glm::radians(3.0f * fovy / ratio * delta.x / height);
    glm::vec3 eyeToTarget, target = eye + dir * dist;
    switch (motionMode) {
    case AroundEye:
        dir = glm::rotate(dir, deltaDeg.x, UP);
        dir = glm::rotate(dir, deltaDeg.y, Right());
        break;
    case AroundCenter:
        eyeToTarget = glm::rotate(-dir, deltaDeg.x, UP);
        eyeToTarget = glm::rotate(eyeToTarget, deltaDeg.y, Right());
        eye = target + eyeToTarget * dist;
        dir = -eyeToTarget;
        break;
    case Shift:
        eye += Right() * delta.x + UP * delta.y;
        break;
    case Forward:
        eye -= delta.y * dir;
        break;
    }

    emit CamChanged();
}

void Camera::SetViewDir(const glm::vec3 &_eye, const glm::vec3 &_dir)
{
    eye = _eye;
    dir = _dir;
    dir = glm::normalize(dir);
    emit CamChanged();
}

void Camera::LookAt(const glm::vec3 &_eye, const glm::vec3 &at)
{
    eye = _eye;
    LookAt(at);
}

void Camera::LookAt(const glm::vec3 &at)
{
    dir = glm::normalize(at - eye);
    dist = glm::length(at - eye);
    emit CamChanged();
}

void Camera::SetPerspective(float _width, float _height, float _zNear, float _zFar)
{
    width = _width;
    height = _height;
    ratio = width / height;
    zNear = _zNear;
    zFar = _zFar;
    perspectiveMat = glm::perspective(glm::radians(fovy), ratio, zNear, zFar);
    emit CamChanged();
}

void Camera::SetMotionMode(Camera::MotionMode _motionMode)
{
    motionMode = _motionMode;
}

void Camera::Zoom(int howMuch)
{
    fovy -= howMuch / 120.0f;
    if (fovy < 10) fovy = 10;
    if (fovy > 60) fovy = 60;
    SetPerspective(width, height, zNear, zFar);
}

glm::vec3 Camera::Right() const
{
    return glm::cross(dir, UP);
}
