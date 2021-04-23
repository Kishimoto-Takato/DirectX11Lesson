#include "StageMap.h"

StageMap::StageMap()
{
}

StageMap::~StageMap()
{
}

void StageMap::Draw()
{
	//エフェクト用のシェーダー
	SHADER->m_effectShader.SetToDevice();

	//スカイのモデルを描画
	SHADER->m_effectShader.DrawModel(m_modelWork, m_World);

	
}

void StageMap::Update()
{
}

void StageMap::Init()
{
	//スカイモデルの読み込みが失敗したらエラー表示
	if (!m_modelWork.Load("Data/Models/StageMap/StageMap.gltf"))
	{
		assert(0 && "StageMap読み込み失敗\n");	//読み込み失敗の表示
	}
}

void StageMap::Release()
{
}
