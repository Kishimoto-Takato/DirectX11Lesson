#include "Player.h"

void Player::Draw()
{
}

void Player::Update()
{
	// スピード変数
	float moveSpd = 0.05f;

	if (GetAsyncKeyState('W')) { m_mWorld._43 += moveSpd; }		// 前方向に移動
	if (GetAsyncKeyState('S')) { m_mWorld._43 -= moveSpd; }		// 後ろ方向に移動
	if (GetAsyncKeyState('A')) { m_mWorld._41 -= moveSpd; }		// 左方向に移動
	if (GetAsyncKeyState('D')) { m_mWorld._41 += moveSpd; }		// 右方向に移動

	// マウスでカメラを回転させる処理
	POINT nowPos;
	GetCursorPos(&nowPos);

	static POINT prevPos = nowPos;

	POINT mouseMove;
	mouseMove.x = nowPos.x - prevPos.x;

	prevPos = nowPos;

	//DirectX::SimpleMath::Matrix trans;
	//trans = trans.CreateTranslation({ 0.01f, 0.0f, 0.00f });

	////カメラ行列の合成
	//m_mWorld *= trans;

	// カメラを構成する行列の合成結果をセットする
	m_camera.SetCameraMatrix(m_mLocalCamera * m_mWorld);
}

void Player::Init()
{
	//カメラ視野角の設定
	m_camera.SetProjectionMatrix(60.0f);	//右側60度、左側60度計120度のカメラ


	// カメラのLocal行列を1m上にあげる
	m_mLocalCamera = m_mLocalCamera.CreateTranslation({ 0.0f,1.0f,0.0f });


	////カメラ行列
	//DirectX::SimpleMath::Matrix initPos;

	////カメラ初期座標
	//initPos = initPos.CreateTranslation({ 1.0f, 1.0f, -3.0f });

	//DirectX::SimpleMath::Matrix initRot;
	//initRot = initRot.CreateRotationX(DirectX::XMConvertToRadians(30.0f));

	//initPos = initRot * initPos;

	//カメラ初期座標セット
	//m_camera.SetCameraMatrix(initPos);
}

void Player::Release()
{
}
