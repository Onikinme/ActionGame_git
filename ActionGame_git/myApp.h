/*
	myApp.h

	アプリケーションデータの管理
*/
#pragma once

#include "myBitmapFont.h"
#include "myTexture.h"
#include "myTimer.h"
#include "myPlayer.h"
#include "myBossTmp.h"
#include "myEnemyManager.h"
#include "myBulletBuffer.h"
#include "myExplosionBuffer.h"
#include "myFloorManager.h"

#define STAGE_COUNT 3

// ゲーム全体の状態遷移.
enum GameState
{
	GAME_STATE_TITLE, 	 // タイトル画面.
	GAME_STATE_LOAD, 	 // ステージ読み込み.
	GAME_STATE_WARNING,  // ゲーム開始待ち.
	GAME_STATE_TUTORIAL, // チュートリアル.
	GAME_STATE_PLAYING,  // ゲーム進行中.
	GAME_STATE_CLEAR, 	 // ステージクリア！.
	GAME_STATE_DEAD, 	 // プレイヤーが撃破される.

	GAME_STATE_COUNT,
	GAME_STATE_INVALID = -1,
};

enum BossState
{
	BOSS_0,
	BOSS_1,
	BOSS_2,
};

// プログラムに必要な変数をMyAppクラスのメンバー変数にまとめる.
// ゲームに必要なデータをひとまとめにして管理しやすくする.
class MyApp
{
private:
	static MyApp sm_myApp;			//このクラス自身のインスタンスをstaticで宣言.
	MyApp();						// コンストラクタをprivateに.

public:
	// ↓インスタンスのポインタを得るstaticメンバ関数.
	static MyApp* GetAppInst() { return &sm_myApp; }

	bool	InitApp();
	void	MainLoop();
	void	ReleaseData();			// リソースを解放する.
	void	ResetGameData();		// ゲームをリセット.

	IDirect3DDevice9* GetDevice() { return pDevice; }		// スプライトの取得.
	ID3DXSprite* GetSprite() { return pSprite; }		// スプライトの取得.
	Player* GetPlayer() { return pPlayer; }// プレイヤー管理クラスのポインタ取得.
	FloorManager* GetFloorMgr() { return pFloorMgr; }	// 床管理クラスのポインタ取得.
	EnemyManager* GetEnemyMgr() { return pEnemyMgr; }	// 敵管理クラスのポインタ取得.
	BossManager* GetBossMgr() { return pBossMgr; }	// ボス管理クラスのポインタ取得.
	BulletBuffer* GetPlaBltBuf() { return pPlayerBullet; }// プレイヤー弾丸バッファの取得.
	BulletBuffer* GetEneBltBuf() { return pBossBullet; }// 敵弾丸バッファの取得.
	ExplosionBuffer* GetExplMgr() { return pExplMgr; }	// 爆発のポインタ取得.
	MyTexture* GetEffectTex() { return pEffectTex; }	// エフェクトのテクスチャ.
	MyTexture* GetEnemyTexA() { return pEnemyTexA; }	// 敵Aのテクスチャ.
	MyTexture* GetEnemyTexB() { return pEnemyTexB; }	// 敵Bのテクスチャ.
	MyTexture* GetEnemyTexC() { return pEnemyTexC; }	// 敵Cのテクスチャ.
	GameState GetGameState() { return gameState; }	// ゲーム状態の取得.

	void	AddScore(int add) { score += add; }
	// プレイヤーの現在座標を取得
	void	GetPlayerPos(D3DXVECTOR2& pos)
	{
		pos = pPlayer->GetXY();
	}
	// プレイヤーのサイズを取得
	void	GetPlayerSize(float& size)
	{
		size = pPlayer->GetSize();
	}

	// 描画関数
	void Draw(ID3DXSprite* pSprite, IDirect3DTexture9* pTexture,
		D3DXVECTOR3 pos, RECT rc, float textureWidth, float textureHeight, bool flipHorizontal, bool flipVertical, bool damageflg, float size);
	// 当たり判定（円）
	bool Collision(D3DXVECTOR2 a, float a_r, D3DXVECTOR2 b, float b_r);

	// すりぬけ床を生成.
	void CreateFloorSlip(D3DXVECTOR2 pos, D3DXVECTOR2 v_pos, float w, float h);

	// 敵Ａを生成.
	void CreateEnemyA(D3DXVECTOR2 pos, D3DXVECTOR2 v_pos, float w, float h, int maxhp);

	// ボスＡを生成.
	void CreateBossA(float x, float y, float vx, float vy, float w, int maxhp);

	// ボスＢを生成.
	void CreateBossB(float x, float y, float vx, float vy, float w, int maxhp);

private:
	HRESULT	InitDirect3D();			// Direct3Dの初期化
	BOOL	UpdateData();			// 更新メイン.
	void	UpdatePlaying(bool);	// GAME_PLAYING状態の時に呼ぶUpdate
	HRESULT	DrawData();				// 描画メイン.
	void	DrawDataPlaying();		// 敵と弾丸の表示.

private:
	HINSTANCE hInstance;			// インスタンスハンドル.
	HWND hWnd;						// 表示ウィンドウ.

	IDirect3D9* pD3D;				// Direct3Dインスタンスオブジェクト.

	IDirect3DDevice9* pDevice;		// Direct3Dデバイスオブジェクト.
	ID3DXSprite* pSprite;			// スプライト.
	MyBitmapFont* pFont;			// ビットマップフォント.

	MyTexture* pPlayerTex;			// 自機.
	MyTexture* pPlayer_WeaponTex;	// プレイヤーの武器
	MyTexture* pMatoTex;			// 当たり判定チェック用の的.
	//MyTexture* pBulletTex;		// 自機弾丸.

	FloorManager* pFloorMgr;		// 床の配列.
	MyTexture* pFloorSlipTex;			// すりぬけ床.

	BulletBuffer* pPlayerBullet;	// プレイヤーの弾丸.
	MyTexture* pPlayerBltTex;		// プレイヤー弾丸テクスチャ.
	BulletBuffer* pBossBullet;		// ボスの弾丸.
	MyTexture* pEnemyBltTex;		// 敵弾丸テクスチャ.
	BossManager* pBossMgr;
	MyTexture* pBossTexA;			// ボスAのテクスチャ
	MyTexture* pBossTexB;			// ボスBのテクスチャ

	MyTexture* PlayerHPBar_Tex;		// プレイヤーのHPバー
	MyTexture* PlayerHPBarFrame_Tex;// プレイヤーのHPバーのフレーム
	MyTexture* PlayerMeter_Tex;		// プレイヤーの必殺技ゲージ
	MyTexture* PlayerMeterFrame_Tex;// プレイヤーの必殺技ゲージのフレーム
	MyTexture* PlayerMeterHatsu_Tex;// プレイヤーの必殺技ゲージの発動可能メッセージ
	MyTexture* PlayerMeterMetsu_Tex;// プレイヤーの必殺技ゲージの点滅
	MyTexture* BossHPBar_Tex;		// ボスのHPバー
	MyTexture* BossHPBarFrame_Tex;		// ボスのHPバーのフレーム

	MyTexture* earth_Tex;        // 地面のテクスチャ.
	MyTexture* kanban64_Tex;        // 看板のテクスチャ.
	MyTexture* redmaru_Tex;        // 看板のテクスチャ.
	int kanbanflg;                  // 看板を表示するフラグ

	int nextFireFrame;				// 自機が次に弾を撃てるまでの時間（フレーム）.
	UINT buttons;					// ボタンの情報.

	Player* pPlayer;

	EnemyManager* pEnemyMgr;		// 敵の配列.
	MyTexture* pEnemyTexA;			// 敵Aのテクスチャ.
	MyTexture* pEnemyTexB;			// 敵Bのテクスチャ.
	MyTexture* pEnemyTexC;			// 敵Cのテクスチャ.

	MyTexture* pEffectTex;			// エフェクトのテクスチャ.

	MyTexture* pBackGroundTex;		// 背景.
	float BackGroundY;			    // 背景の現在位置.

	ExplosionBuffer* pExplMgr;		// 爆発の配列.
	MyTexture* pExplosionTex;		// 爆発.

	int score;						// スコア.
	int playerPower;				// 自機の耐久力.
	int flash;                  // ボスを倒した瞬間のフラッシュ

	UINT joyID;						// ゲームコントローラのID.
	int gameTimer;					// 全体のタイマー.

	GameState gameState;			// ゲーム全体の状態.
	BossState bossState;			// ボスのラウンド.
	int stateTimer;					// 状態遷移用タイマー.
	int destroyTimer;               // ボスを倒した後のウェイトタイマー
	int warningTimer;               // WARNINGのウェイトタイマー
	MyTexture* pReadyTex;			// READY.
#if defined(Shiken7)
	MyTexture* pTitleTex;			// TITLE.
	MyTexture* pPushSpaceTex;			// PUSH_SPACE.
	MyTexture* pGameClearTex;			// GameClear.
	MyTexture* pPushBackSpaceTex;			// PUSH_BACKSPACE.
#endif
#if defined(Shiken8)
	MyTexture* pStageTex[STAGE_COUNT];		// STAGEテクスチャ.
	int currentStage;
#else
	MyTexture* pStage1Tex;			// STAGE1.
#endif
	MyTexture* pGameOverTex;		// GAMEOVER.

	MyTexture* ptitletextTex;

	CTimer timer;					// 時間管理オブジェクト(Update用).
	CTimer fps;						// 時間管理オブジェクト(FPS表示用).

	char text[256] = { 0 };
};

inline MyApp* GetApp() { return MyApp::GetAppInst(); }

/*
// プログラムに必要な変数を構造体として定義.
// （ゲームに必要なデータをメモリ上に、まとめて配置したいため）.
// ※後でシングルトンモデルのクラスに変更する予定.
struct DataSet
{
};

extern DataSet mydata;
*/
