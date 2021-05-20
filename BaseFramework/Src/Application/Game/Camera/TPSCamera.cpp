#include "TPSCamera.h"

void TPSCamera::SetCameraMatrix(const Math::Matrix& mWorld)
{
    //キャラクターから注視点までのローカル座標
    Math::Matrix localGazePos;
    localGazePos = Math::Matrix::CreateTranslation(m_localGazePos);

    //注視点から実際のカメラまでのローカル座標
    Math::Matrix localPos;
    localPos = Math::Matrix::CreateTranslation(m_localPos);

    //カメラの回転
    Math::Matrix rotation;
    rotation = GetRotationMatrix();


    KdCamera::SetCameraMatrix( localPos * rotation * localGazePos * mWorld);
}
