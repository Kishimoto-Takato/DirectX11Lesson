#include "Player.h"



#include "../Camera/TPSCamera.h"

//const POINT Player::s_fixMousePos = { 640, 360 };

void Player::Draw()
{
	//キューブのモデルを描画
	SHADER->m_standardShader.DrawModel(m_robot, m_mWorld);
}

void Player::Update()
{
	//キューブ初期座標
	m_robotMat = m_robotMat.CreateTranslation({ 0.0f, 1.0f, 0.0f });

	// スピード変数
	float moveSpd = 0.05f;

	Math::Vector3 moveVec;

	if (GetAsyncKeyState('W')) { moveVec.z += 1.0f; }		// 前方向に移動
	if (GetAsyncKeyState('S')) { moveVec.z -= 1.0f; }		// 後ろ方向に移動
	if (GetAsyncKeyState('A')) { moveVec.x -= 1.0f; }		// 左方向に移動
	if (GetAsyncKeyState('D')) { moveVec.x += 1.0f; }		// 右方向に移動

	moveVec.Normalize();
	moveVec *= moveSpd;

	if (m_pCamera)
	{
		moveVec = moveVec.TransformNormal(moveVec, m_pCamera->GetRotationYMatrix());
	}

	m_mWorld._41 += moveVec.x;
	m_mWorld._43 += moveVec.z;



	//// マウスでカメラを回転させる処理
	//POINT nowPos;
	//GetCursorPos(&nowPos);

	//static POINT prevPos = nowPos;

	//POINT mouseMove;
	//mouseMove.x = nowPos.x - s_fixMousePos.x;
	//mouseMove.y = nowPos.y - s_fixMousePos.y;

	//prevPos = nowPos;

	//SetCursorPos(s_fixMousePos.x, s_fixMousePos.y);
	//
	////kamerawokaitensaserusyori
	//m_camAngle.x += mouseMove.y * 0.15f;
	//m_camAngle.y += mouseMove.x * 0.15f;

	////回転制御
	//m_camAngle.x = std::clamp(m_camAngle.x, -75.0f, 90.0f);

	// マウスの移動量の４分の１の角度(Degree)回転
	//Math::Matrix rotateY;
	//m_RotateCamera = m_RotateCamera.CreateRotationY
	//(DirectX::XMConvertToRadians(m_camAngle.y));

	//Math::Matrix rotateX;
	//m_RotateCamera *= m_RotateCamera.CreateFromAxisAngle
	//(m_RotateCamera.Right(), DirectX::XMConvertToRadians(m_camAngle.x));

	// m_mRotateCameraに毎フレームの回転を合成
	   //m_RotateCamera *= rotateX * rotateY;
	  // m_RotateCamera *= rotateX;

	//DirectX::SimpleMath::Matrix trans;
	//trans = trans.CreateTranslation({ 0.01f, 0.0f, 0.00f });

	////カメラ行列の合成
	//m_mWorld *= trans;

	if (m_pCamera)
	{
		m_pCamera->Update();

		// プレイヤーの絶対行列をセットする
		m_pCamera->SetCameraMatrix(m_mWorld);
	}
}

void Player::Init()
{
	//キューブモデルの読み込みが失敗したらエラー表示
	if (!m_robot.Load("Data/Models/Robot/Robot.gltf"))
	{
		assert(0 && "CubeModel読み込み失敗\n");	//読み込み失敗の表示
	}

	m_pCamera = new TPSCamera();

	m_pCamera->Init();

	//カメラ視野角の設定
	m_pCamera->SetProjectionMatrix(60.0f);	//右側60度、左側60度計120度のカメラ

	// カメラのローカル座標を1mにあげる
	//m_pCamera->SetLocalPos( 0.0f,1.0f,0.0f );

	// カメラの注視点からのLocal座標を5m後ろに下げる
	m_pCamera->SetLocalPos(Math::Vector3( 0.0f,0.0f,-5.0f ));

	//キャラクターから注視点へのローカル座標を3m上にあげる
	m_pCamera->SetLocalGazePos(Math::Vector3(0.0f, 3.0f, 0.0f));

	m_pCamera->SetClampAngle(-75.0f, 75.0f);

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
