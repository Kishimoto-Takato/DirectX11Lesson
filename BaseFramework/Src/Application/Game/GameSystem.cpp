#include "GameSystem.h"

void GameSystem::Init()
{
	//スカイモデルの読み込みが失敗したらエラー表示
	if (!m_sky.Load("Data/Models/Sky/Sky.gltf"))
	{
		assert(0 && "SkyModel読み込み失敗\n");	//読み込み失敗の表示
	}

	if (!m_cube.Load("Data/Models/Cube/Cube.gltf"))
	{
		assert(0 && "CubeModel読み込み失敗\n");	//読み込み失敗の表示
	}

	//カメラ視野角の設定
	m_camera.SetProjectionMatrix(60.0f);	//右側60度、左側60度計120度のカメラ
}

void GameSystem::Update()
{
	
}

void GameSystem::Draw()
{
	//カメラの行列をセット
	m_camera.SetToShader();

	//エフェクト用のシェーダー
	SHADER->m_effectShader.SetToDevice();

	//スカイのモデルを描画
	SHADER->m_effectShader.DrawModel(m_sky);

	//キューブのモデルを描画
	SHADER->m_effectShader.DrawModel(m_cube);
}

void GameSystem::Release()
{
	OutputDebugStringA("Release\n");
}
