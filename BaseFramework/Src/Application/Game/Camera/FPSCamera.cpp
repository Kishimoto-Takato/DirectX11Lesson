#include "FPSCamera.h"
#include "../GameSystem.h"

const POINT FPSCamera::s_fixMousePos = { 640, 360 };

void FPSCamera::Init()
{
    SetCursorPos(s_fixMousePos.x, s_fixMousePos.y);
}

void FPSCamera::Update()
{// マウスでカメラを回転させる処理
    POINT nowPos;
    GetCursorPos(&nowPos);

    POINT moveMouse;
    moveMouse.x = nowPos.x - s_fixMousePos.x;
    moveMouse.y = nowPos.y - s_fixMousePos.y;

    SetCursorPos(s_fixMousePos.x, s_fixMousePos.y);


    // カメラを回転させる処理
    m_degAng.y += moveMouse.x * m_rotationSpd;
    m_degAng.x += moveMouse.y * m_rotationSpd;

    // 回転制御
    m_degAng.x = std::clamp(m_degAng.x, m_minAngleX, m_maxAngleX);
}

const Math::Matrix FPSCamera::GetRotationMatrix() const
{
    return Math::Matrix::CreateFromYawPitchRoll(
        DirectX::XMConvertToRadians(m_degAng.y), 
        DirectX::XMConvertToRadians(m_degAng.x),
        DirectX::XMConvertToRadians(m_degAng.z));
}

void FPSCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld)
{
    Math::Matrix localPos;
    localPos = Math::Matrix::CreateTranslation(m_localPos);

    Math::Matrix rotation;
    rotation = GetRotationMatrix();


    KdCamera::SetCameraMatrix(rotation * localPos  * mWorld);
}
