#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <glm/glm.hpp>

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0);
    glm::mat4x4 MVPMat();
    glm::mat4x4 MVMat();
    glm::mat4x4 NormalMatrix();
    const glm::vec3& Eye() const { return eye; }
    const glm::vec3& Dir() const { return dir; }
    const glm::vec3& Up() const { return UP; }
    glm::vec3 Right() const;
    enum MotionMode { AroundEye, AroundCenter, Shift, Forward };
    void MouseMove(glm::vec2 delta);
    void SetViewDir(const glm::vec3& _eye, const glm::vec3& _dir);
    void LookAt(const glm::vec3& _eye, const glm::vec3& at);
    void LookAt(const glm::vec3& at);
    void SetPerspective(float _width, float _height, float _zNear, float _zFar);
    void SetMotionMode(MotionMode motionMode);
    MotionMode GetMotionMode() { return motionMode; }
    void Zoom(int howMuch);
signals:
    void CamChanged();

public slots:

protected:
    //model view
    glm::vec3 eye;
    glm::vec3 dir;
    float dist;    
    const glm::vec3 UP;

    //perspective
    float ratio, width, height, zNear, zFar;
    float fovy;
    glm::mat4x4 perspectiveMat;

    //others
    MotionMode motionMode;
};

#endif // CAMERA_H
