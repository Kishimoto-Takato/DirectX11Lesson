#pragma once

class StageMap;
class Player;

class GameSystem
{
public:
	GameSystem() {}		//コンストラクター
	~GameSystem() { Release(); }	//デストラクター

	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画


private:
	void Release();		//解放

	KdModelWork m_sky;	//スカイスフィア

	KdModelWork m_cube;	//キューブ

	//KdCamera m_camera;	//カメラ

	DirectX::SimpleMath::Matrix m_cubeMat;	//キューブのワールド行列

	DirectX::SimpleMath::Matrix m_skyMat;	//スカイスフィアの行列

	StageMap* m_pStage = nullptr;
	Player* m_pPlayer = nullptr;
};

