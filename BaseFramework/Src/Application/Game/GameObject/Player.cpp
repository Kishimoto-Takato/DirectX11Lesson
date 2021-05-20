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
	Math::Vector3 vMove;

	UpdateMove(vMove);
	
	
	if (m_pCamera)
	{
		m_pCamera->Update();

		//回転の更新
		UpdateRotate(vMove);

		Math::Matrix trans;
		trans = Math::Matrix::CreateTranslation(m_worldPos);

		Math::Matrix rotation;
		rotation = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_worldRot.y));

		m_mWorld = rotation * trans;

		// プレイヤーの絶対行列をセットする
		m_pCamera->SetCameraMatrix(trans);
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
	KdSafeDelete(m_pCamera);
}

void Player::UpdateMove(Math::Vector3& dstMove)
{
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

	m_worldPos.x += moveVec.x;
	m_worldPos.z += moveVec.z;

	dstMove = moveVec;
}

void Player::UpdateRotate(const Math::Vector3& srcMove)
{
	if (!m_pCamera) { return; }

	if (srcMove.LengthSquared() == 0.0f) { return; }

	// キャラの正面方向のベクトル：出発ベクトル
	Math::Vector3 nowDir = m_mWorld.Backward();

	// 移動方向のベクトル：目標ベクトル
	Math::Vector3 targetDir = srcMove;

	nowDir.Normalize();
	targetDir.Normalize();

	float nowAng = atan2(nowDir.x, nowDir.z);
	nowAng = DirectX::XMConvertToDegrees(nowAng);

	float targetAng = atan2(targetDir.x, targetDir.z);
	targetAng = DirectX::XMConvertToDegrees(targetAng);

	
	float rotateAng = targetAng - nowAng;

							//条件式 ? 真：偽　3項演算子
	rotateAng = (rotateAng > 0) ? 8.0f : -8.0f;

	m_worldRot.y += rotateAng;
	//m_worldRot = m_pCamera->GetRotationAngle();
	
}
