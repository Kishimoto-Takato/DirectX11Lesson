#include "GameSystem.h"
#include "GameObject/StageMap.h"
#include "GameObject/Player.h"

void GameSystem::Init()
{
	//スカイモデルの読み込みが失敗したらエラー表示
	if (!m_sky.Load("Data/Models/Sky/Sky.gltf"))
	{
		assert(0 && "SkyModel読み込み失敗\n");	//読み込み失敗の表示
	}

	//キューブモデルの読み込みが失敗したらエラー表示
	if (!m_cube.Load("Data/Models/Cube/Cube2.gltf"))
	{
		assert(0 && "CubeModel読み込み失敗\n");	//読み込み失敗の表示
	}

	//カメラ視野角の設定
	m_camera.SetProjectionMatrix(60.0f,3000.0f);	//右側60度、左側60度計120度のカメラ

	//カメラ行列
	DirectX::SimpleMath::Matrix initPos;

	//カメラ初期座標
	initPos = initPos.CreateTranslation({ 0.0f, 1.0f, -3.0f });

	DirectX::SimpleMath::Matrix initRot;
	initRot = initRot.CreateRotationX(DirectX::XMConvertToRadians(30.0f));

	initPos = initRot * initPos;

	//カメラ初期座標セット
	m_camera.SetCameraMatrix(initPos);

	//キューブ初期座標
	m_cubeMat = m_cubeMat.CreateTranslation({ 0.0f, 0.0f, 0.75f });

	//スカイスフィア拡縮行列
	m_skyMat = m_skyMat.CreateScale(2200.0f);

	//インスタンス化
	m_pStage = new StageMap();
	m_pPlayer = new Player();

	//init呼び出し
	m_pStage->Init();
}

void GameSystem::Update()
{
	//回転行列
	DirectX::SimpleMath::Matrix rotation;
	rotation = rotation.CreateRotationY(DirectX::XMConvertToRadians(2.0f));

	//回転行列
	DirectX::SimpleMath::Matrix rotationSky;
	rotationSky = rotationSky.CreateRotationY(DirectX::XMConvertToRadians(2.0f * 0.05f ));

	//カメラ行列の取得
	//DirectX::SimpleMath::Matrix& camaraMat = m_camera.WorkCamera();

	//カメラ行列の合成
	//camaraMat = camaraMat * rotation;

	//スカイ行列の合成
	m_skyMat = rotationSky * m_skyMat;

	//キューブ行列の合成
	m_cubeMat = rotation * m_cubeMat * rotation;

	
}

void GameSystem::Draw()
{

	m_pPlayer->WorkGetCamera().SetToShader();

	//カメラの行列をセット
	//m_camera.SetToShader();

	//エフェクト用のシェーダー
	SHADER->m_effectShader.SetToDevice();

	//スカイのモデルを描画
	SHADER->m_effectShader.DrawModel(m_sky, m_skyMat);

	//エフェクト用のシェーダー
	SHADER->m_standardShader.SetToDevice();

	//キューブのモデルを描画
	SHADER->m_standardShader.DrawModel(m_cube, m_cubeMat);

	

	if (m_pStage)
	{
		m_pStage->Draw();
	}
}

void GameSystem::Release()
{
	//やってることは同じ
	if (m_pStage)
	{
		delete(m_pStage);
		m_pStage = nullptr;
	}

	//同じ
	//KdSafeRelease(m_pPlayer);

	if (m_pPlayer)
	{
		delete(m_pPlayer);
		m_pPlayer = nullptr;
	}
}
